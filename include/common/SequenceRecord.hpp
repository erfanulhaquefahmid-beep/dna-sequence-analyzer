#ifndef SEQUENCE_RECORD_HPP
#define SEQUENCE_RECORD_HPP

#include <string>
#include <iostream>
#include <iomanip>

struct SequenceRecord
{
    int id{0};
    std::string ownerUsername;
    std::string sequenceName;
    std::string filePath;
    int length{0};
    double gcContent{0.0};
    std::string uploadDate;

    // Operator overloads for comparison and display
    bool operator==(const SequenceRecord& other) const {
        return id == other.id;
    }

    bool operator!=(const SequenceRecord& other) const {
        return !(*this == other);
    }

    bool operator<(const SequenceRecord& other) const {
        return id < other.id;
    }

    void display() const;
    static void printHeader();
};

struct DNABaseCount
{
    int aCount{0};
    int cCount{0};
    int gCount{0};
    int tCount{0};

    int total() const {
        return aCount + cCount + gCount + tCount;
    }

    double gcContent() const {
        int tot = total();
        if (tot == 0) return 0.0;
        return (static_cast<double>(gCount + cCount) / tot) * 100.0;
    }
};

#endif // SEQUENCE_RECORD_HPP
