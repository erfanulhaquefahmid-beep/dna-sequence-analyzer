#include "transformation.h"

#include <cctype>
#include <stdexcept>

namespace Transformation {

namespace {

char normalizeBase(char base) {
    const char normalized = static_cast<char>(std::toupper(static_cast<unsigned char>(base)));
    if (normalized != 'A' && normalized != 'T' && normalized != 'G' && normalized != 'C') {
        throw std::invalid_argument("Invalid DNA base: expected A, T, G, or C.");
    }
    return normalized;
}

void validateBases(const std::string& bases) {
    for (const char base : bases) {
        (void)normalizeBase(base);
    }
}

} // namespace

char complementBase(char base) {
    switch (normalizeBase(base)) {
        case 'A': return 'T';
        case 'T': return 'A';
        case 'C': return 'G';
        case 'G': return 'C';
        default: throw std::invalid_argument("Invalid DNA base.");
    }
}

std::string complement(const std::string& dna) {
    std::string result;
    result.reserve(dna.size());
    for (const char base : dna) {
        result.push_back(complementBase(base));
    }
    return result;
}

std::string reverse(const std::string& dna) {
    std::string result;
    result.reserve(dna.size());
    for (std::size_t i = dna.size(); i > 0; --i) {
        result.push_back(dna[i - 1]);
    }
    return result;
}

std::string reverseComplement(const std::string& dna) {
    std::string result;
    result.reserve(dna.size());
    for (std::size_t i = dna.size(); i > 0; --i) {
        result.push_back(complementBase(dna[i - 1]));
    }
    return result;
}

std::string substitute(const std::string& dna, std::size_t index, char newBase) {
    if (index >= dna.size()) {
        throw std::out_of_range("Substitution index is outside the sequence.");
    }

    std::string result = dna;
    result[index] = normalizeBase(newBase);
    return result;
}

std::string insert(const std::string& dna, std::size_t index, const std::string& bases) {
    if (index > dna.size()) {
        throw std::out_of_range("Insertion index is outside the sequence.");
    }
    validateBases(bases);

    std::string result;
    result.reserve(dna.size() + bases.size());
    for (std::size_t i = 0; i < index; ++i) {
        result.push_back(dna[i]);
    }
    result += bases;
    for (std::size_t i = index; i < dna.size(); ++i) {
        result.push_back(dna[i]);
    }
    return result;
}

std::string erase(const std::string& dna, std::size_t index, std::size_t count) {
    if (index > dna.size() || index + count > dna.size()) {
        throw std::out_of_range("Deletion range is outside the sequence.");
    }

    std::string result;
    result.reserve(dna.size() - count);
    for (std::size_t i = 0; i < dna.size(); ++i) {
        if (i < index || i >= index + count) {
            result.push_back(dna[i]);
        }
    }
    return result;
}

} // namespace Transformation
