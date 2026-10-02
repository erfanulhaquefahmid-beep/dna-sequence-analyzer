#ifndef MIN_HEAP_HPP
#define MIN_HEAP_HPP

#include <vector>
#include <string>
#include <utility>
#include <stdexcept>

class MinHeap
{
private:
    std::vector<std::pair<std::string, int>> heap;

    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    MinHeap() = default;

    void push(const std::pair<std::string, int>& kmerFrequency);
    std::pair<std::string, int> pop();
    std::pair<std::string, int> top() const;
    bool empty() const;
    int size() const;
    void clear();
};

#endif // MIN_HEAP_HPP
