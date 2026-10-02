#include "translation.h"

#include <cctype>
#include <unordered_map>

namespace Translation {

std::string transcribeTemplateDNA(const std::string& dnaTemplate) {
    std::string rna;
    rna.reserve(dnaTemplate.size());

    for (const char rawBase : dnaTemplate) {
        const char base = static_cast<char>(std::toupper(static_cast<unsigned char>(rawBase)));
        switch (base) {
            case 'A': rna.push_back('U'); break;
            case 'T': rna.push_back('A'); break;
            case 'C': rna.push_back('G'); break;
            case 'G': rna.push_back('C'); break;
            default: rna.push_back('N'); break;
        }
    }
    return rna;
}

std::string aminoAcidForCodon(const std::string& codon) {
    if (codon.size() != 3) {
        return "?";
    }

    // Standard genetic code. '*' denotes a stop codon.
    static const std::unordered_map<std::string, std::string> table = {
        {"UUU", "F"}, {"UUC", "F"}, {"UUA", "L"}, {"UUG", "L"},
        {"UCU", "S"}, {"UCC", "S"}, {"UCA", "S"}, {"UCG", "S"},
        {"UAU", "Y"}, {"UAC", "Y"}, {"UAA", "*"}, {"UAG", "*"},
        {"UGU", "C"}, {"UGC", "C"}, {"UGA", "*"}, {"UGG", "W"},
        {"CUU", "L"}, {"CUC", "L"}, {"CUA", "L"}, {"CUG", "L"},
        {"CCU", "P"}, {"CCC", "P"}, {"CCA", "P"}, {"CCG", "P"},
        {"CAU", "H"}, {"CAC", "H"}, {"CAA", "Q"}, {"CAG", "Q"},
        {"CGU", "R"}, {"CGC", "R"}, {"CGA", "R"}, {"CGG", "R"},
        {"AUU", "I"}, {"AUC", "I"}, {"AUA", "I"}, {"AUG", "M"},
        {"ACU", "T"}, {"ACC", "T"}, {"ACA", "T"}, {"ACG", "T"},
        {"AAU", "N"}, {"AAC", "N"}, {"AAA", "K"}, {"AAG", "K"},
        {"AGU", "S"}, {"AGC", "S"}, {"AGA", "R"}, {"AGG", "R"},
        {"GUU", "V"}, {"GUC", "V"}, {"GUA", "V"}, {"GUG", "V"},
        {"GCU", "A"}, {"GCC", "A"}, {"GCA", "A"}, {"GCG", "A"},
        {"GAU", "D"}, {"GAC", "D"}, {"GAA", "E"}, {"GAG", "E"},
        {"GGU", "G"}, {"GGC", "G"}, {"GGA", "G"}, {"GGG", "G"}
    };

    std::string normalized;
    normalized.reserve(3);
    for (const char raw : codon) {
        normalized.push_back(static_cast<char>(std::toupper(static_cast<unsigned char>(raw))));
    }

    const auto it = table.find(normalized);
    if (it == table.end()) {
        return "?";
    }
    return it->second;
}

std::string translateRNA(const std::string& rna) {
    std::string normalized;
    normalized.reserve(rna.size());
    for (const char raw : rna) {
        normalized.push_back(static_cast<char>(std::toupper(static_cast<unsigned char>(raw))));
    }

    const std::size_t start = normalized.find("AUG");
    if (start == std::string::npos) {
        return "";
    }

    std::string protein;
    for (std::size_t i = start; i + 3 <= normalized.size(); i += 3) {
        const std::string codon = normalized.substr(i, 3);
        const std::string aminoAcid = aminoAcidForCodon(codon);

        if (aminoAcid == "*") {
            break;
        }
        if (aminoAcid == "?") {
            break;
        }
        protein += aminoAcid;
    }

    return protein;
}

std::string translateDNA(const std::string& dnaTemplate) {
    return translateRNA(transcribeTemplateDNA(dnaTemplate));
}

} // namespace Translation
