#include "graph.h"

#include <iostream>
#include <queue>

DeBruijnGraph::DeBruijnGraph(std::size_t k) : k_(k), vertices_(), kmers_() {}

void DeBruijnGraph::setK(std::size_t k) {
    k_ = k;
    vertices_.clear();
    kmers_.clear();
}

std::size_t DeBruijnGraph::getK() const {
    return k_;
}

std::vector<std::string> DeBruijnGraph::generateKmers(const std::string& sequence) const {
    std::vector<std::string> result;
    if (k_ == 0 || sequence.size() < k_) {
        return result;
    }

    result.reserve(sequence.size() - k_ + 1);
    for (std::size_t i = 0; i + k_ <= sequence.size(); ++i) {
        result.push_back(sequence.substr(i, k_));
    }
    return result;
}

std::size_t DeBruijnGraph::findVertex(const std::string& label) const {
    for (std::size_t i = 0; i < vertices_.size(); ++i) {
        if (vertices_[i].label == label) {
            return i;
        }
    }
    return vertices_.size();
}

std::size_t DeBruijnGraph::addVertex(const std::string& label) {
    const std::size_t existing = findVertex(label);
    if (existing != vertices_.size()) {
        return existing;
    }

    Vertex vertex;
    vertex.label = label;
    vertices_.push_back(vertex);
    return vertices_.size() - 1;
}

bool DeBruijnGraph::build(const std::string& sequence) {
    vertices_.clear();
    kmers_.clear();

    if (k_ < 2 || sequence.size() < k_) {
        return false;
    }

    kmers_ = generateKmers(sequence);
    for (const std::string& kmer : kmers_) {
        const std::string prefix = kmer.substr(0, k_ - 1);
        const std::string suffix = kmer.substr(1, k_ - 1);
        const std::size_t from = addVertex(prefix);
        const std::size_t to = addVertex(suffix);
        // Parallel edges are intentionally retained because repeated k-mers
        // represent repeated observations in a De Bruijn multigraph.
        vertices_[from].neighbors.push_back(to);
    }

    return true;
}

void DeBruijnGraph::display(std::ostream& out) const {
    if (vertices_.empty()) {
        out << "Graph is empty.\n";
        return;
    }

    out << "De Bruijn Graph (k = " << k_ << ")\n";
    for (std::size_t i = 0; i < vertices_.size(); ++i) {
        out << vertices_[i].label << " -> ";
        if (vertices_[i].neighbors.empty()) {
            out << "(none)";
        } else {
            for (std::size_t j = 0; j < vertices_[i].neighbors.size(); ++j) {
                if (j > 0) {
                    out << ", ";
                }
                out << vertices_[vertices_[i].neighbors[j]].label;
            }
        }
        out << '\n';
    }
}

std::vector<std::string> DeBruijnGraph::bfs(const std::string& start) const {
    std::vector<std::string> order;
    const std::size_t startIndex = findVertex(start);
    if (startIndex == vertices_.size()) {
        return order;
    }

    std::vector<bool> visited(vertices_.size(), false);
    std::queue<std::size_t> queue;
    visited[startIndex] = true;
    queue.push(startIndex);

    while (!queue.empty()) {
        const std::size_t current = queue.front();
        queue.pop();
        order.push_back(vertices_[current].label);

        for (const std::size_t neighbor : vertices_[current].neighbors) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                queue.push(neighbor);
            }
        }
    }

    return order;
}

void DeBruijnGraph::dfsRecursive(std::size_t index,
                                 std::vector<bool>& visited,
                                 std::vector<std::string>& order) const {
    visited[index] = true;
    order.push_back(vertices_[index].label);

    for (const std::size_t neighbor : vertices_[index].neighbors) {
        if (!visited[neighbor]) {
            dfsRecursive(neighbor, visited, order);
        }
    }
}

std::vector<std::string> DeBruijnGraph::dfs(const std::string& start) const {
    std::vector<std::string> order;
    const std::size_t startIndex = findVertex(start);
    if (startIndex == vertices_.size()) {
        return order;
    }

    std::vector<bool> visited(vertices_.size(), false);
    dfsRecursive(startIndex, visited, order);
    return order;
}

const std::vector<DeBruijnGraph::Vertex>& DeBruijnGraph::getVertices() const {
    return vertices_;
}
