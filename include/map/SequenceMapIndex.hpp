#ifndef SEQUENCE_MAP_INDEX_HPP
#define SEQUENCE_MAP_INDEX_HPP

#include "../common/SequenceRecord.hpp"
#include <unordered_map>
#include <map>
#include <vector>
#include <string>

class SequenceMapIndex
{
private:
    std::unordered_map<int, SequenceRecord> idIndex;
    std::map<std::string, std::vector<int>> nameIndex;
    std::multimap<double, int> gcIndex;
    std::multimap<std::string, int> dateIndex;

public:
    SequenceMapIndex() = default;

    void addRecord(const SequenceRecord& record);
    bool removeRecordById(int id);

    SequenceRecord* findById(int id);
    std::vector<int> findIdsByName(const std::string& name);
    std::vector<int> findIdsByNamePrefix(const std::string& prefix);

    std::vector<int> findByGCRange(double minGC, double maxGC);
    std::vector<int> findByDateRange(const std::string& startDate, const std::string& endDate);

    void displayAllIndexes() const;
    void printHashTableStats() const;
    void compareMapVsUnorderedMap() const;
    void clear();

    int size() const { return static_cast<int>(idIndex.size()); }
    const std::unordered_map<int, SequenceRecord>& getIdIndex() const { return idIndex; }
};

std::unordered_map<std::string, int> countKmers(
    const std::string& dnaSequence,
    int k
);

std::vector<std::pair<std::string, int>> getTopKmers(
    const std::unordered_map<std::string, int>& kmerMap,
    int k
);

#endif // SEQUENCE_MAP_INDEX_HPP
