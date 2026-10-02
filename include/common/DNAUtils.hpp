#ifndef DNA_UTILS_HPP
#define DNA_UTILS_HPP

#include "SequenceRecord.hpp"
#include <string>
#include <vector>

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

    // Normalize DNA string to uppercase
    static std::string toUppercase(const std::string& dna);

    // Reverse DNA sequence
    static std::string reverseSequence(const std::string& dna);

    // Reverse complement of DNA sequence
    static std::string reverseComplement(const std::string& dna);

    // Split DNA sequence into k-mers
    static std::vector<std::string> extractKmers(const std::string& dna, int k);
};

#endif // DNA_UTILS_HPP
