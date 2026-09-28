#ifndef REPLICATION_H
#define REPLICATION_H

#include <string>

namespace Replication {

struct DoubleStrand {
    // original is stored 5' -> 3'
    // complementary is stored 3' -> 5' relative to original.
    std::string original;
    std::string complementary;
};

char complementBase(char base);
std::string complementaryStrand(const std::string& dna);
DoubleStrand replicate(const std::string& dna);
std::string formattedDoubleStrand(const std::string& dna);

} // namespace Replication

#endif
