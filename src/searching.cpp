#include "searching.h"

namespace Searching {

std::vector<int> buildLPS(const std::string& pattern) {
    std::vector<int> lps(pattern.size(), 0);
    int length = 0;
    std::size_t i = 1;

    while (i < pattern.size()) {
        if (pattern[i] == pattern[static_cast<std::size_t>(length)]) {
            ++length;
            lps[i] = length;
            ++i;
        } else if (length > 0) {
            length = lps[static_cast<std::size_t>(length - 1)];
        } else {
            lps[i] = 0;
            ++i;
        }
    }

    return lps;
}

SearchResult kmpSearch(const std::string& text, const std::string& pattern) {
    SearchResult result{false, {}};

    if (pattern.empty() || text.empty() || pattern.size() > text.size()) {
        return result;
    }

    const std::vector<int> lps = buildLPS(pattern);
    std::size_t textIndex = 0;
    std::size_t patternIndex = 0;

    while (textIndex < text.size()) {
        if (text[textIndex] == pattern[patternIndex]) {
            ++textIndex;
            ++patternIndex;

            if (patternIndex == pattern.size()) {
                result.positions.push_back(textIndex - pattern.size());
                result.found = true;
                patternIndex = static_cast<std::size_t>(lps[patternIndex - 1]);
            }
        } else if (patternIndex > 0) {
            patternIndex = static_cast<std::size_t>(lps[patternIndex - 1]);
        } else {
            ++textIndex;
        }
    }

    return result;
}

} // namespace Searching
