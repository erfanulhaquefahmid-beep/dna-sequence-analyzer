#ifndef SEARCHING_H
#define SEARCHING_H

#include <cstddef>
#include <string>
#include <vector>

namespace Searching {

struct SearchResult {
    bool found;
    std::vector<std::size_t> positions;
};

// Builds the KMP longest-prefix-suffix table in O(m) time.
std::vector<int> buildLPS(const std::string& pattern);

// Searches for all (including overlapping) occurrences of pattern in text.
// Returns zero-based starting positions.
SearchResult kmpSearch(const std::string& text, const std::string& pattern);

} // namespace Searching

#endif
