#include "../../include/common/DNAUtils.hpp"
#include <fstream>
#include <algorithm>
#include <cctype>
#include <iostream>

std::string DNAUtils::readDNAFromFile(const std::string& filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        // Fallback for execution from build/ directory
        file.open("../" + filePath);
    }
    if (!file.is_open())
    {
        std::cerr << "[DNAUtils] Error: Could not open file: " << filePath << "\n";
        return "";
    }

    std::string line;
    std::string sequence;
    while (std::getline(file, line))
    {
        // Trim leading and trailing whitespace
        size_t start = line.find_first_not_of(" \t\r\n");
        if (start == std::string::npos) continue;

        // Skip FASTA headers starting with '>' or comment lines starting with ';'
        if (line[start] == '>' || line[start] == ';')
        {
            continue;
        }

        for (size_t i = start; i < line.size(); ++i)
        {
            char c = line[i];
            if (std::isalpha(static_cast<unsigned char>(c)))
            {
                sequence.push_back(static_cast<char>(std::toupper(static_cast<unsigned char>(c))));
            }
        }
    }
    return sequence;
}

DNABaseCount DNAUtils::computeBaseCounts(const std::string& dna)
{
    DNABaseCount counts;
    for (char ch : dna)
    {
        char upper = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
        switch (upper)
        {
            case 'A': counts.aCount++; break;
            case 'C': counts.cCount++; break;
            case 'G': counts.gCount++; break;
            case 'T': counts.tCount++; break;
            default: break;
        }
    }
    return counts;
}

double DNAUtils::calculateGCContent(const std::string& dna)
{
    DNABaseCount counts = computeBaseCounts(dna);
    return counts.gcContent();
}

bool DNAUtils::isValidDNA(const std::string& dna)
{
    if (dna.empty()) return false;
    for (char ch : dna)
    {
        char upper = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
        if (upper != 'A' && upper != 'C' && upper != 'G' && upper != 'T' && upper != 'N')
        {
            return false;
        }
    }
    return true;
}

std::string DNAUtils::toUppercase(const std::string& dna)
{
    std::string result = dna;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::toupper(c); });
    return result;
}

std::string DNAUtils::reverseSequence(const std::string& dna)
{
    std::string result = dna;
    std::reverse(result.begin(), result.end());
    return result;
}

std::string DNAUtils::reverseComplement(const std::string& dna)
{
    std::string rev = reverseSequence(dna);
    std::string comp;
    comp.reserve(rev.size());
    for (char c : rev)
    {
        char up = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
        switch (up)
        {
            case 'A': comp.push_back('T'); break;
            case 'T': comp.push_back('A'); break;
            case 'C': comp.push_back('G'); break;
            case 'G': comp.push_back('C'); break;
            default:  comp.push_back('N'); break;
        }
    }
    return comp;
}

std::vector<std::string> DNAUtils::extractKmers(const std::string& dna, int k)
{
    std::vector<std::string> kmers;
    if (k <= 0 || static_cast<size_t>(k) > dna.length())
    {
        return kmers;
    }
    kmers.reserve(dna.length() - k + 1);
    for (size_t i = 0; i + k <= dna.length(); ++i)
    {
        kmers.push_back(dna.substr(i, k));
    }
    return kmers;
}
