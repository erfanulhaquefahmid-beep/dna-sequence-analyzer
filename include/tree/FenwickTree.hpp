#ifndef FENWICK_TREE_HPP
#define FENWICK_TREE_HPP

#include <vector>

/**
 * @brief Binary Indexed Tree (Fenwick Tree)
 * Supports prefix sum queries and point updates in O(log n) time.
 * Uses 1-based indexing internally.
 */
class FenwickTree
{
private:
    int n;
    std::vector<int> bit;

public:
    explicit FenwickTree(int size = 0);

    // Initialize/resize tree for array of length size
    void init(int size);

    // Add delta to element at 1-based index: O(log n)
    void update(int index, int delta);

    // Prefix sum from index 1 to index: O(log n)
    int query(int index) const;

    // Range sum from left to right [left, right] (1-based, inclusive): O(log n)
    int rangeQuery(int left, int right) const;

    int size() const { return n; }
    void clear();
};

#endif // FENWICK_TREE_HPP
