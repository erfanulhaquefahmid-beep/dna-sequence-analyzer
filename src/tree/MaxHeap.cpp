#include "../../include/tree/MaxHeap.hpp"
#include "../../include/tree/MinHeap.hpp"
#include <algorithm>

void MaxHeap::heapifyUp(int index)
{
    while (index > 0)
    {
        int parent = (index - 1) / 2;
        if (heap[index].second > heap[parent].second)
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

void MaxHeap::heapifyDown(int index)
{
    int n = static_cast<int>(heap.size());
    while (true)
    {
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < n && heap[left].second > heap[largest].second)
        {
            largest = left;
        }
        if (right < n && heap[right].second > heap[largest].second)
        {
            largest = right;
        }

        if (largest != index)
        {
            std::swap(heap[index], heap[largest]);
            index = largest;
        }
        else
        {
            break;
        }
    }
}

void MaxHeap::push(const std::pair<std::string, int>& kmerFrequency)
{
    heap.push_back(kmerFrequency);
    heapifyUp(static_cast<int>(heap.size()) - 1);
}

std::pair<std::string, int> MaxHeap::pop()
{
    if (empty())
    {
        throw std::out_of_range("MaxHeap is empty");
    }
    std::pair<std::string, int> maxVal = heap.front();
    heap.front() = heap.back();
    heap.pop_back();
    if (!empty())
    {
        heapifyDown(0);
    }
    return maxVal;
}

std::pair<std::string, int> MaxHeap::top() const
{
    if (empty())
    {
        throw std::out_of_range("MaxHeap is empty");
    }
    return heap.front();
}

bool MaxHeap::empty() const
{
    return heap.empty();
}

int MaxHeap::size() const
{
    return static_cast<int>(heap.size());
}

void MaxHeap::clear()
{
    heap.clear();
}

std::vector<std::pair<std::string, int>> topKFrequentKmers(
    const std::unordered_map<std::string, int>& kmerCount,
    int k)
{
    std::vector<std::pair<std::string, int>> result;
    if (k <= 0 || kmerCount.empty())
    {
        return result;
    }

    // Optimal top-k using Min-Heap of capacity k: O(N log k) time, O(k) space
    MinHeap minHeap;
    for (const auto& entry : kmerCount)
    {
        if (minHeap.size() < k)
        {
            minHeap.push(entry);
        }
        else if (entry.second > minHeap.top().second)
        {
            minHeap.pop();
            minHeap.push(entry);
        }
    }

    while (!minHeap.empty())
    {
        result.push_back(minHeap.pop());
    }

    // MinHeap pops in ascending order of frequency; reverse to get descending
    std::reverse(result.begin(), result.end());
    return result;
}
