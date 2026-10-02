#ifndef DNA_GENERATOR_H
#define DNA_GENERATOR_H

#include <cstddef>
#include <string>
#include <vector>

namespace DNAGenerator {

// A seed of 0 requests a non-deterministic seed from std::random_device.
std::string generateSequence(std::size_t length, unsigned int seed = 0);
std::vector<std::string> generateSequences(std::size_t count,
                                           std::size_t length,
                                           unsigned int seed = 0);

} // namespace DNAGenerator

#endif
