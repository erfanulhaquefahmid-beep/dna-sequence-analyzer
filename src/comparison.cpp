#include "comparison.h"

namespace Comparison {

ComparisonResult compareSequences(const std::string& first,
                                  const std::string& second) {
    const std::size_t overlappingLength =
        (first.size() < second.size()) ? first.size() : second.size();

    std::size_t matches = 0;
    std::size_t mismatches = 0;
    for (std::size_t i = 0; i < overlappingLength; ++i) {
        if (first[i] == second[i]) {
            ++matches;
        } else {
            ++mismatches;
        }
    }

    const std::size_t lengthDifference =
        (first.size() > second.size()) ? first.size() - second.size()
                                       : second.size() - first.size();
    const std::size_t totalCompared = overlappingLength + lengthDifference;

    ComparisonResult result;
    result.equal = first == second;
    result.matchingPositions = matches;
    result.mismatches = mismatches + lengthDifference;
    result.similarityPercentage =
        (totalCompared == 0)
            ? 100.0
            : (100.0 * static_cast<double>(matches) /
               static_cast<double>(totalCompared));
    result.hammingDefined = (first.size() == second.size());
    result.hammingDistance = result.hammingDefined ? result.mismatches : 0;
    return result;
}

} // namespace Comparison
