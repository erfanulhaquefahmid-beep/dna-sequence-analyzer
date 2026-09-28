#ifndef GRAPH_H
#define GRAPH_H

#include <cstddef>
#include <iosfwd>
#include <string>
#include <vector>

class DeBruijnGraph {
public:
    struct Vertex {
        std::string label;
        std::vector<std::size_t> neighbors;
    };

    explicit DeBruijnGraph(std::size_t k = 3);

    void setK(std::size_t k);
    std::size_t getK() const;

    std::vector<std::string> generateKmers(const std::string& sequence) const;
    bool build(const std::string& sequence);

    void display(std::ostream& out) const;

    std::vector<std::string> bfs(const std::string& start) const;
    std::vector<std::string> dfs(const std::string& start) const;

    const std::vector<Vertex>& getVertices() const;

private:
    std::size_t k_;
    std::vector<Vertex> vertices_;
    std::vector<std::string> kmers_;

    std::size_t findVertex(const std::string& label) const;
    std::size_t addVertex(const std::string& label);
    void dfsRecursive(std::size_t index,
                      std::vector<bool>& visited,
                      std::vector<std::string>& order) const;
};

#endif
