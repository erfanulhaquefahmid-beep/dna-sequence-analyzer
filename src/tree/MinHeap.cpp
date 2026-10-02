#include "../../include/tree/MinHeap.hpp"
#include <algorithm>

void MinHeap::heapifyUp(int index)
{
    while (index > 0)
    {
        int parent = (index - 1) / 2;
        if (heap[index].second < heap[parent].second)
        {
            std::swap(heap[index], heap[parent]);
            index = parent;
        }
        else
        {
            break;
        }
    }
}

void MinHeap::heapifyDown(int index)
{
    int n = static_cast<int>(heap.size());
    while (true)
    {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < n && heap[left].second < heap[smallest].second)
        {
            smallest = left;
        }
        if (right < n && heap[right].second < heap[smallest].second)
        {
            smallest = right;
        }

        if (smallest != index)
        {
            std::swap(heap[index], heap[smallest]);
            index = smallest;
        }
        else
        {
            break;
        }
    }
}

void MinHeap::push(const std::pair<std::string, int>& kmerFrequency)
{
    heap.push_back(kmerFrequency);
    heapifyUp(static_cast<int>(heap.size()) - 1);
}

std::pair<std::string, int> MinHeap::pop()
{
    if (empty())
    {
        throw std::out_of_range("MinHeap is empty");
    }
    std::pair<std::string, int> minVal = heap.front();
    heap.front() = heap.back();
    heap.pop_back();
    if (!empty())
    {
        heapifyDown(0);
    }
    return minVal;
}

std::pair<std::string, int> MinHeap::top() const
{
    if (empty())
    {
        throw std::out_of_range("MinHeap is empty");
    }
    return heap.front();
}

bool MinHeap::empty() const
{
    return heap.empty();
}

int MinHeap::size() const
{
    return static_cast<int>(heap.size());
}

void MinHeap::clear()
{
    heap.clear();
}
