#include "sorting.h"

#include <utility>

namespace Sorting {
namespace {

// Returns true when left should appear after right in the requested order.
bool comesAfter(const std::string& left,
                const std::string& right,
                bool ascending) {
    if (ascending) {
        return left.size() > right.size();
    }
    return left.size() < right.size();
}

void merge(std::vector<std::string>& values,
           std::vector<std::string>& temp,
           std::size_t left,
           std::size_t middle,
           std::size_t right,
           bool ascending) {
    std::size_t i = left;
    std::size_t j = middle + 1;
    std::size_t k = left;

    while (i <= middle && j <= right) {
        // Use <= style stability: when lengths are equal, keep the left item first.
        if (!comesAfter(values[i], values[j], ascending)) {
            temp[k++] = values[i++];
        } else {
            temp[k++] = values[j++];
        }
    }

    while (i <= middle) {
        temp[k++] = values[i++];
    }

    while (j <= right) {
        temp[k++] = values[j++];
    }

    for (std::size_t index = left; index <= right; ++index) {
        values[index] = temp[index];
    }
}

void mergeSortRecursive(std::vector<std::string>& values,
                        std::vector<std::string>& temp,
                        std::size_t left,
                        std::size_t right,
                        bool ascending) {
    if (left >= right) {
        return;
    }

    const std::size_t middle = left + (right - left) / 2;
    mergeSortRecursive(values, temp, left, middle, ascending);
    mergeSortRecursive(values, temp, middle + 1, right, ascending);
    merge(values, temp, left, middle, right, ascending);
}

std::size_t partition(std::vector<std::string>& values,
                      std::size_t low,
                      std::size_t high,
                      bool ascending) {
    // Last element is the pivot.
    const std::string pivot = values[high];
    std::size_t smallerEnd = low;

    for (std::size_t j = low; j < high; ++j) {
        if (comesAfter(pivot, values[j], ascending)) {
            std::swap(values[smallerEnd], values[j]);
            ++smallerEnd;
        }
    }

    std::swap(values[smallerEnd], values[high]);
    return smallerEnd;
}

void quickSortRecursive(std::vector<std::string>& values,
                        std::size_t low,
                        std::size_t high,
                        bool ascending) {
    if (low >= high) {
        return;
    }

    const std::size_t pivotIndex = partition(values, low, high, ascending);

    if (pivotIndex > low) {
        quickSortRecursive(values, low, pivotIndex - 1, ascending);
    }
    if (pivotIndex < high) {
        quickSortRecursive(values, pivotIndex + 1, high, ascending);
    }
}

} // namespace

std::vector<std::string> bubbleSortByLength(
    const std::vector<std::string>& sequences, bool ascending) {
    std::vector<std::string> result = sequences;

    // Repeatedly compare adjacent lengths and swap out-of-order sequences.
    for (std::size_t pass = 0; pass < result.size(); ++pass) {
        bool swapped = false;
        for (std::size_t j = 0; j + 1 < result.size() - pass; ++j) {
            if (comesAfter(result[j], result[j + 1], ascending)) {
                std::swap(result[j], result[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }

    return result;
}

std::vector<std::string> selectionSortByLength(
    const std::vector<std::string>& sequences, bool ascending) {
    std::vector<std::string> result = sequences;

    for (std::size_t i = 0; i < result.size(); ++i) {
        std::size_t selected = i;

        for (std::size_t j = i + 1; j < result.size(); ++j) {
            if (comesAfter(result[selected], result[j], ascending)) {
                selected = j;
            }
        }

        if (selected != i) {
            std::swap(result[i], result[selected]);
        }
    }

    return result;
}

std::vector<std::string> insertionSortByLength(
    const std::vector<std::string>& sequences, bool ascending) {
    std::vector<std::string> result = sequences;

    for (std::size_t i = 1; i < result.size(); ++i) {
        std::string current = result[i];
        std::size_t j = i;

        // Shift longer/shorter entries right until the current item fits.
        while (j > 0 && comesAfter(result[j - 1], current, ascending)) {
            result[j] = result[j - 1];
            --j;
        }
        result[j] = current;
    }

    return result;
}

std::vector<std::string> mergeSortByLength(
    const std::vector<std::string>& sequences, bool ascending) {
    std::vector<std::string> result = sequences;
    if (result.empty()) {
        return result;
    }

    std::vector<std::string> temp(result.size());
    mergeSortRecursive(result, temp, 0, result.size() - 1, ascending);
    return result;
}

std::vector<std::string> quickSortByLength(
    const std::vector<std::string>& sequences, bool ascending) {
    std::vector<std::string> result = sequences;
    if (result.empty()) {
        return result;
    }

    quickSortRecursive(result, 0, result.size() - 1, ascending);
    return result;
}

bool isSortedByLength(const std::vector<std::string>& sequences,
                      bool ascending) {
    for (std::size_t i = 1; i < sequences.size(); ++i) {
        if (comesAfter(sequences[i - 1], sequences[i], ascending)) {
            return false;
        }
    }
    return true;
}

} // namespace Sorting
