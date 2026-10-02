#ifndef MAX_HEAP_HPP
#define MAX_HEAP_HPP

#include <vector>
#include <string>
#include <utility>
#include <stdexcept>
#include <unordered_map>

class MaxHeap
{
private:
    std::vector<std::pair<std::string, int>> heap;

    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    MaxHeap() = default;

    void push(const std::pair<std::string, int>& kmerFrequency);
    std::pair<std::string, int> pop();
    std::pair<std::string, int> top() const;
    bool empty() const;
    int size() const;
    void clear();
};

// Function using MinHeap to find top-k kmers in O(N log K) time
std::vector<std::pair<std::string, int>> topKFrequentKmers(
    const std::unordered_map<std::string, int>& kmerCount,
    int k
);

#endif // MAX_HEAP_HPP
