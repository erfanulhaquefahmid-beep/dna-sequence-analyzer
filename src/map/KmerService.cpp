#include "../../include/map/KmerService.hpp"
#include "../../include/tree/MaxHeap.hpp"

std::unordered_map<std::string, int> KmerService::buildKmerCount(const std::string& dna, int k)
{
    std::unordered_map<std::string, int> counts;
    if (k <= 0 || static_cast<size_t>(k) > dna.length())
    {
        return counts;
    }

    for (size_t i = 0; i + k <= dna.length(); ++i)
    {
        counts[dna.substr(i, k)]++;
    }
    return counts;
}

std::vector<std::pair<std::string, int>> KmerService::topKmers(
    const std::unordered_map<std::string, int>& counts,
    int k)
{
    return topKFrequentKmers(counts, k);
}

std::vector<std::pair<std::string, std::string>> KmerService::generateDeBruijnEdges(
    const std::string& dna,
    int k)
{
    std::vector<std::pair<std::string, std::string>> edges;
    if (k <= 1 || static_cast<size_t>(k) > dna.length())
    {
        return edges;
    }

    // A k-mer represents a directed edge from prefix (k-1)-mer to suffix (k-1)-mer
    for (size_t i = 0; i + k <= dna.length(); ++i)
    {
        std::string kmer = dna.substr(i, k);
        std::string prefix = kmer.substr(0, k - 1);
        std::string suffix = kmer.substr(1, k - 1);
        edges.push_back({prefix, suffix});
    }
    return edges;
}
