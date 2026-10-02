#include "dna_generator.h"

#include <random>

namespace DNAGenerator {

std::string generateSequence(std::size_t length, unsigned int seed) {
    std::mt19937 generator;
    if (seed == 0) {
        std::random_device device;
        generator.seed(device());
    } else {
        generator.seed(seed);
    }

    static const char bases[] = {'A', 'T', 'G', 'C'};
    std::uniform_int_distribution<int> distribution(0, 3);

    std::string sequence;
    sequence.reserve(length);
    for (std::size_t i = 0; i < length; ++i) {
        sequence.push_back(bases[distribution(generator)]);
    }
    return sequence;
}

std::vector<std::string> generateSequences(std::size_t count,
                                           std::size_t length,
                                           unsigned int seed) {
    std::vector<std::string> sequences;
    sequences.reserve(count);

    std::mt19937 generator;
    if (seed == 0) {
        std::random_device device;
        generator.seed(device());
    } else {
        generator.seed(seed);
    }

    static const char bases[] = {'A', 'T', 'G', 'C'};
    std::uniform_int_distribution<int> distribution(0, 3);

    for (std::size_t sequenceIndex = 0; sequenceIndex < count; ++sequenceIndex) {
        std::string sequence;
        sequence.reserve(length);
        for (std::size_t i = 0; i < length; ++i) {
            sequence.push_back(bases[distribution(generator)]);
        }
        sequences.push_back(sequence);
    }

    return sequences;
}

} // namespace DNAGenerator
