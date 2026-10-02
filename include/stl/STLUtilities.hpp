#ifndef STL_UTILITIES_HPP
#define STL_UTILITIES_HPP

#include "../common/SequenceRecord.hpp"
#include <vector>
#include <string>
#include <functional>

class STLUtilities
{
public:
    // STL sorting algorithms using std::sort with custom lambda comparators
    static void sortBySequenceName(std::vector<SequenceRecord>& records);
    static void sortByLengthAscending(std::vector<SequenceRecord>& records);
    static void sortByLengthDescending(std::vector<SequenceRecord>& records);
    static void sortByGCContent(std::vector<SequenceRecord>& records);
    static void sortByUploadDate(std::vector<SequenceRecord>& records);

    // STL filtering using std::copy_if and lambda predicates
    static std::vector<SequenceRecord> filterByLength(
        const std::vector<SequenceRecord>& records,
        int minLength,
        int maxLength
    );

    static std::vector<SequenceRecord> filterByGC(
        const std::vector<SequenceRecord>& records,
        double minGC,
        double maxGC
    );

    // STL searching using std::find_if
    static std::vector<SequenceRecord> searchByNameContains(
        const std::vector<SequenceRecord>& records,
        const std::string& keyword
    );

    // STL counting using std::count_if
    static int countIfGCGreaterThan(const std::vector<SequenceRecord>& records, double threshold);

    // String manipulation via STL algorithms
    static std::string transformToUppercase(const std::string& dna);
    static std::string reverseString(const std::string& dna);

    // Binary search lower_bound demo on sorted vector by length
    static int findFirstWithLengthAtLeast(const std::vector<SequenceRecord>& sortedRecords, int minLength);

    // Display formatted table of records
    static void printRecords(const std::vector<SequenceRecord>& records);
};

#endif // STL_UTILITIES_HPP
