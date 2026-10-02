#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <cstddef>
#include <string>

namespace Transformation {

char complementBase(char base);
std::string complement(const std::string& dna);
std::string reverse(const std::string& dna);
std::string reverseComplement(const std::string& dna);

// index is zero-based; newBase must be A/T/G/C.
std::string substitute(const std::string& dna, std::size_t index, char newBase);
std::string insert(const std::string& dna, std::size_t index, const std::string& bases);
std::string erase(const std::string& dna, std::size_t index, std::size_t count = 1);

} // namespace Transformation

#endif
