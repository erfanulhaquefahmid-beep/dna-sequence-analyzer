#ifndef KMER_SERVICE_HPP
#define KMER_SERVICE_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

class KmerService
{
public:
    static std::unordered_map<std::string, int> buildKmerCount(
        const std::string& dna,
        int k
    );

    static std::vector<std::pair<std::string, int>> topKmers(
        const std::unordered_map<std::string, int>& counts,
        int k
    );

    // Export k-mers to adjacency format for graph module integration
    static std::vector<std::pair<std::string, std::string>> generateDeBruijnEdges(
        const std::string& dna,
        int k
    );
};

#endif // KMER_SERVICE_HPP
