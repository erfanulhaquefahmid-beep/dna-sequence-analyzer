#ifndef DNA_RANGE_INDEX_HPP
#define DNA_RANGE_INDEX_HPP

#include "FenwickTree.hpp"
#include <string>

/**
 * @brief DNARangeIndex leverages 4 Fenwick Trees to achieve O(log N) prefix/range
 * nucleotide frequency queries and dynamic GC content evaluation.
 * Positions are 1-based [1..N], consistent with genomic coordinate conventions.
 */
class DNARangeIndex
{
private:
    std::string sequence;
    int length{0};
    FenwickTree bitA;
    FenwickTree bitC;
    FenwickTree bitG;
    FenwickTree bitT;

public:
    DNARangeIndex() = default;

    void build(const std::string& dnaSequence);
    void updateBase(int position, char newBase); // Support dynamic point updates!

    int countA(int left, int right) const;
    int countC(int left, int right) const;
    int countG(int left, int right) const;
    int countT(int left, int right) const;

    double gcContent(int left, int right) const;
    int getLength() const { return length; }
    const std::string& getSequence() const { return sequence; }
};

#endif // DNA_RANGE_INDEX_HPP
