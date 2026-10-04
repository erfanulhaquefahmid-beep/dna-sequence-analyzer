#include "../../include/common/DNAUtils.hpp"
#include <fstream>
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
