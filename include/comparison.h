#ifndef COMPARISON_H
#define COMPARISON_H

#include <cstddef>
#include <string>

namespace Comparison {

struct ComparisonResult {
    bool equal;
    std::size_t matchingPositions;
    std::size_t mismatches;
    double similarityPercentage;
    bool hammingDefined;
    std::size_t hammingDistance;
};

ComparisonResult compareSequences(const std::string& first,
                                  const std::string& second);

} // namespace Comparison

#endif
