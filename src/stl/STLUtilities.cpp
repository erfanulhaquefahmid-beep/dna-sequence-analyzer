#include "../../include/stl/STLUtilities.hpp"
#include <algorithm>
#include <iostream>
#include <cctype>

void STLUtilities::sortBySequenceName(std::vector<SequenceRecord>& records)
{
    std::sort(records.begin(), records.end(), [](const SequenceRecord& a, const SequenceRecord& b) {
        return a.sequenceName < b.sequenceName;
    });
}

void STLUtilities::sortByLengthAscending(std::vector<SequenceRecord>& records)
{
    std::sort(records.begin(), records.end(), [](const SequenceRecord& a, const SequenceRecord& b) {
        return a.length < b.length;
    });
}

void STLUtilities::sortByLengthDescending(std::vector<SequenceRecord>& records)
{
    std::sort(records.begin(), records.end(), [](const SequenceRecord& a, const SequenceRecord& b) {
        return a.length > b.length;
    });
}

void STLUtilities::sortByGCContent(std::vector<SequenceRecord>& records)
{
    std::sort(records.begin(), records.end(), [](const SequenceRecord& a, const SequenceRecord& b) {
        return a.gcContent < b.gcContent;
    });
}

void STLUtilities::sortByUploadDate(std::vector<SequenceRecord>& records)
{
    std::sort(records.begin(), records.end(), [](const SequenceRecord& a, const SequenceRecord& b) {
        return a.uploadDate < b.uploadDate;
    });
}

std::vector<SequenceRecord> STLUtilities::filterByLength(
    const std::vector<SequenceRecord>& records,
    int minLength,
    int maxLength)
{
    std::vector<SequenceRecord> result;
    std::copy_if(records.begin(), records.end(), std::back_inserter(result),
        [minLength, maxLength](const SequenceRecord& r) {
            return r.length >= minLength && r.length <= maxLength;
        });
    return result;
}

std::vector<SequenceRecord> STLUtilities::filterByGC(
    const std::vector<SequenceRecord>& records,
    double minGC,
    double maxGC)
{
    std::vector<SequenceRecord> result;
    std::copy_if(records.begin(), records.end(), std::back_inserter(result),
        [minGC, maxGC](const SequenceRecord& r) {
            return r.gcContent >= minGC && r.gcContent <= maxGC;
        });
    return result;
}

std::vector<SequenceRecord> STLUtilities::searchByNameContains(
    const std::vector<SequenceRecord>& records,
    const std::string& keyword)
{
    std::vector<SequenceRecord> result;
    for (const auto& r : records)
    {
        if (r.sequenceName.find(keyword) != std::string::npos)
        {
            result.push_back(r);
        }
    }
    return result;
}

int STLUtilities::countIfGCGreaterThan(const std::vector<SequenceRecord>& records, double threshold)
{
    return static_cast<int>(std::count_if(records.begin(), records.end(),
        [threshold](const SequenceRecord& r) {
            return r.gcContent > threshold;
        }));
}

std::string STLUtilities::transformToUppercase(const std::string& dna)
{
    std::string copy = dna;
    std::transform(copy.begin(), copy.end(), copy.begin(),
        [](unsigned char c) { return std::toupper(c); });
    return copy;
}

std::string STLUtilities::reverseString(const std::string& dna)
{
    std::string copy = dna;
    std::reverse(copy.begin(), copy.end());
    return copy;
}

int STLUtilities::findFirstWithLengthAtLeast(const std::vector<SequenceRecord>& sortedRecords, int minLength)
{
    auto it = std::lower_bound(sortedRecords.begin(), sortedRecords.end(), minLength,
        [](const SequenceRecord& r, int val) {
            return r.length < val;
        });

    if (it != sortedRecords.end())
    {
        return static_cast<int>(std::distance(sortedRecords.begin(), it));
    }
    return -1;
}

void STLUtilities::printRecords(const std::vector<SequenceRecord>& records)
{
    if (records.empty())
    {
        std::cout << "[No records found matching criteria]\n";
        return;
    }
    SequenceRecord::printHeader();
    for (const auto& r : records)
    {
        r.display();
    }
    std::cout << "Total count: " << records.size() << "\n\n";
}
