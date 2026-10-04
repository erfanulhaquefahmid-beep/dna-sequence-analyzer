#include "../../include/tree/DNARangeIndex.hpp"
#include <cctype>
#include <iostream>

void DNARangeIndex::build(const std::string& dnaSequence)
{
    sequence = dnaSequence;
    length = static_cast<int>(sequence.length());

    bitA.init(length);
    bitC.init(length);
    bitG.init(length);
    bitT.init(length);

    for (int i = 0; i < length; ++i)
    {
        char ch = static_cast<char>(std::toupper(static_cast<unsigned char>(sequence[i])));
        int pos = i + 1; // 1-based index

        switch (ch)
        {
            case 'A': bitA.update(pos, 1); break;
            case 'C': bitC.update(pos, 1); break;
            case 'G': bitG.update(pos, 1); break;
            case 'T': bitT.update(pos, 1); break;
            default: break;
        }
    }
}

void DNARangeIndex::updateBase(int position, char newBase)
{
    if (position < 1 || position > length) return;

    char oldBase = static_cast<char>(std::toupper(static_cast<unsigned char>(sequence[position - 1])));
    char upNew = static_cast<char>(std::toupper(static_cast<unsigned char>(newBase)));

    if (oldBase == upNew) return;

    // Decrement old
    switch (oldBase)
    {
        case 'A': bitA.update(position, -1); break;
        case 'C': bitC.update(position, -1); break;
        case 'G': bitG.update(position, -1); break;
        case 'T': bitT.update(position, -1); break;
        default: break;
    }

    // Increment new
    switch (upNew)
    {
        case 'A': bitA.update(position, 1); break;
        case 'C': bitC.update(position, 1); break;
        case 'G': bitG.update(position, 1); break;
        case 'T': bitT.update(position, 1); break;
        default: break;
    }

    sequence[position - 1] = upNew;
}

int DNARangeIndex::countA(int left, int right) const
{
    return bitA.rangeQuery(left, right);
}

int DNARangeIndex::countC(int left, int right) const
{
    return bitC.rangeQuery(left, right);
}

int DNARangeIndex::countG(int left, int right) const
{
    return bitG.rangeQuery(left, right);
}

int DNARangeIndex::countT(int left, int right) const
{
    return bitT.rangeQuery(left, right);
}

double DNARangeIndex::gcContent(int left, int right) const
{
    if (left < 1) left = 1;
    if (right > length) right = length;
    if (left > right) return 0.0;

    int g = countG(left, right);
    int c = countC(left, right);
    int totalSpan = (right - left + 1);

    if (totalSpan <= 0) return 0.0;
    return (static_cast<double>(g + c) / totalSpan) * 100.0;
}
