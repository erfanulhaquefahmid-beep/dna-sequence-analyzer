#include "replication.h"

#include <cctype>
#include <stdexcept>
#include <sstream>

namespace Replication {

char complementBase(char base) {
    switch (static_cast<char>(std::toupper(static_cast<unsigned char>(base)))) {
        case 'A': return 'T';
        case 'T': return 'A';
        case 'C': return 'G';
        case 'G': return 'C';
        default: throw std::invalid_argument("Invalid DNA base.");
    }
}

std::string complementaryStrand(const std::string& dna) {
    std::string result;
    result.reserve(dna.size());

    for (const char base : dna) {
        result.push_back(complementBase(base));
    }
    return result;
}

DoubleStrand replicate(const std::string& dna) {
    return DoubleStrand{dna, complementaryStrand(dna)};
}

std::string formattedDoubleStrand(const std::string& dna) {
    const DoubleStrand strand = replicate(dna);
    std::ostringstream out;
    out << "5' " << strand.original << " 3'\n";
    out << "3' " << strand.complementary << " 5'";
    return out.str();
}

} // namespace Replication
