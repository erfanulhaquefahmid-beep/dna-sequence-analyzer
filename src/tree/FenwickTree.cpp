#include "../../include/tree/FenwickTree.hpp"
#include <algorithm>

FenwickTree::FenwickTree(int size) : n(size), bit(size + 1, 0)
{
}

void FenwickTree::init(int size)
{
    n = size;
    bit.assign(size + 1, 0);
}

void FenwickTree::clear()
{
    std::fill(bit.begin(), bit.end(), 0);
}

void FenwickTree::update(int index, int delta)
{
    if (index < 1 || index > n) return;
    for (; index <= n; index += (index & -index))
    {
        bit[index] += delta;
    }
}

int FenwickTree::query(int index) const
{
    if (index > n) index = n;
    if (index < 1) return 0;

    int sum = 0;
    for (; index > 0; index -= (index & -index))
    {
        sum += bit[index];
    }
    return sum;
}

int FenwickTree::rangeQuery(int left, int right) const
{
    if (left > right || right < 1 || left > n) return 0;
    left = std::max(1, left);
    right = std::min(n, right);
    return query(right) - query(left - 1);
}
