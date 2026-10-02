#ifndef SORTING_H
#define SORTING_H

#include <cstddef>
#include <string>
#include <vector>

namespace Sorting {

// All functions return a sorted copy and leave the original vector unchanged.
// When ascending is true, shorter sequences come first.
// When ascending is false, longer sequences come first.
std::vector<std::string> bubbleSortByLength(
    const std::vector<std::string>& sequences, bool ascending = true);

std::vector<std::string> selectionSortByLength(
    const std::vector<std::string>& sequences, bool ascending = true);

std::vector<std::string> insertionSortByLength(
    const std::vector<std::string>& sequences, bool ascending = true);

std::vector<std::string> mergeSortByLength(
    const std::vector<std::string>& sequences, bool ascending = true);

std::vector<std::string> quickSortByLength(
    const std::vector<std::string>& sequences, bool ascending = true);

// Utility used by tests and the menu to verify the result.
bool isSortedByLength(const std::vector<std::string>& sequences,
                      bool ascending = true);

} // namespace Sorting

#endif
