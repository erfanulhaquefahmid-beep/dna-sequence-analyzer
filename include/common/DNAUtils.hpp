#ifndef DNA_UTILS_HPP
#define DNA_UTILS_HPP

#include "SequenceRecord.hpp"
#include <string>

class DNAUtils
{
public:
    // Read raw DNA string from file (skipping FASTA header lines starting with '>')
    static std::string readDNAFromFile(const std::string& filePath);

    // Compute base counts (A, C, G, T)
    static DNABaseCount computeBaseCounts(const std::string& dna);

    // Compute GC percentage (0.0 to 100.0)
    static double calculateGCContent(const std::string& dna);

    // Validate whether string contains only valid DNA nucleotides (A, C, G, T, N, etc.)
    static bool isValidDNA(const std::string& dna);
};

#endif // DNA_UTILS_HPP
