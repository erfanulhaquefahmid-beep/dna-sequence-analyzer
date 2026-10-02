#include "../../include/map/SequenceMapIndex.hpp"
#include "../../include/tree/MaxHeap.hpp"
#include <iostream>
#include <algorithm>
#include <iomanip>

void SequenceMapIndex::addRecord(const SequenceRecord& record)
{
    // If updating an existing record, clean old entries first
    if (idIndex.find(record.id) != idIndex.end())
    {
        removeRecordById(record.id);
    }

    idIndex[record.id] = record;
    nameIndex[record.sequenceName].push_back(record.id);
    gcIndex.insert({record.gcContent, record.id});
    dateIndex.insert({record.uploadDate, record.id});
}

bool SequenceMapIndex::removeRecordById(int id)
{
    auto it = idIndex.find(id);
    if (it == idIndex.end())
    {
        return false;
    }

    const SequenceRecord& rec = it->second;

    // 1. Remove from nameIndex
    auto nameIt = nameIndex.find(rec.sequenceName);
    if (nameIt != nameIndex.end())
    {
        auto& ids = nameIt->second;
        ids.erase(std::remove(ids.begin(), ids.end(), id), ids.end());
        if (ids.empty())
        {
            nameIndex.erase(nameIt);
        }
    }

    // 2. Remove from gcIndex
    auto gcRange = gcIndex.equal_range(rec.gcContent);
    for (auto git = gcRange.first; git != gcRange.second; )
    {
        if (git->second == id)
        {
            git = gcIndex.erase(git);
        }
        else
        {
            ++git;
        }
    }

    // 3. Remove from dateIndex
    auto dateRange = dateIndex.equal_range(rec.uploadDate);
    for (auto dit = dateRange.first; dit != dateRange.second; )
    {
        if (dit->second == id)
        {
            dit = dateIndex.erase(dit);
        }
        else
        {
            ++dit;
        }
    }

    // 4. Remove from idIndex
    idIndex.erase(it);
    return true;
}

SequenceRecord* SequenceMapIndex::findById(int id)
{
    auto it = idIndex.find(id);
    if (it != idIndex.end())
    {
        return &(it->second);
    }
    return nullptr;
}

std::vector<int> SequenceMapIndex::findIdsByName(const std::string& name)
{
    auto it = nameIndex.find(name);
    if (it != nameIndex.end())
    {
        return it->second;
    }
    return {};
}

std::vector<int> SequenceMapIndex::findIdsByNamePrefix(const std::string& prefix)
{
    std::vector<int> results;
    // std::map is lexicographically ordered, so lower_bound finds the first key >= prefix
    for (auto it = nameIndex.lower_bound(prefix); it != nameIndex.end(); ++it)
    {
        if (it->first.rfind(prefix, 0) == 0) // starts with prefix
        {
            results.insert(results.end(), it->second.begin(), it->second.end());
        }
        else
        {
            break; // Past prefix range
        }
    }
    return results;
}

std::vector<int> SequenceMapIndex::findByGCRange(double minGC, double maxGC)
{
    std::vector<int> results;
    auto low = gcIndex.lower_bound(minGC);
    auto high = gcIndex.upper_bound(maxGC);
    for (auto it = low; it != high; ++it)
    {
        results.push_back(it->second);
    }
    return results;
}

std::vector<int> SequenceMapIndex::findByDateRange(const std::string& startDate, const std::string& endDate)
{
    std::vector<int> results;
    auto low = dateIndex.lower_bound(startDate);
    auto high = dateIndex.upper_bound(endDate);
    for (auto it = low; it != high; ++it)
    {
        results.push_back(it->second);
    }
    return results;
}

void SequenceMapIndex::displayAllIndexes() const
{
    std::cout << "\n================ MAP INDEX SUMMARY ================\n";
    std::cout << "1. Primary ID Index (std::unordered_map - Hash Table):\n";
    std::cout << "   Total records: " << idIndex.size() << "\n";
    for (const auto& pair : idIndex)
    {
        std::cout << "   [ID: " << pair.first << "] -> " << pair.second.sequenceName 
                  << " (Len: " << pair.second.length << ", GC: " << pair.second.gcContent << "%)\n";
    }

    std::cout << "\n2. Name Secondary Index (std::map - Red-Black Tree):\n";
    for (const auto& pair : nameIndex)
    {
        std::cout << "   \"" << pair.first << "\" -> IDs: [ ";
        for (int id : pair.second) std::cout << id << " ";
        std::cout << "]\n";
    }

    std::cout << "\n3. GC Content Multimap Index (std::multimap):\n";
    for (const auto& pair : gcIndex)
    {
        std::cout << "   " << std::fixed << std::setprecision(1) << pair.first << "% -> Record ID: " << pair.second << "\n";
    }

    std::cout << "\n4. Upload Date Multimap Index (std::multimap):\n";
    for (const auto& pair : dateIndex)
    {
        std::cout << "   " << pair.first << " -> Record ID: " << pair.second << "\n";
    }
    std::cout << "====================================================\n\n";
}

void SequenceMapIndex::printHashTableStats() const
{
    std::cout << "\n--- std::unordered_map Internal Hash Table Diagnostics ---\n";
    std::cout << "Total Elements (size) : " << idIndex.size() << "\n";
    std::cout << "Bucket Count          : " << idIndex.bucket_count() << "\n";
    std::cout << "Load Factor           : " << idIndex.load_factor() << "\n";
    std::cout << "Max Load Factor       : " << idIndex.max_load_factor() << "\n";
    for (size_t b = 0; b < idIndex.bucket_count(); ++b)
    {
        if (idIndex.bucket_size(b) > 0)
        {
            std::cout << "  Bucket [" << b << "] contains " << idIndex.bucket_size(b) << " elements\n";
        }
    }
    std::cout << "----------------------------------------------------------\n";
}

void SequenceMapIndex::compareMapVsUnorderedMap() const
{
    std::cout << "\n=========================================================================\n";
    std::cout << "          COMPARISON: std::map VS std::unordered_map (DSA Concept)\n";
    std::cout << "=========================================================================\n";
    std::cout << "Feature               | std::map                    | std::unordered_map\n";
    std::cout << "-------------------------------------------------------------------------\n";
    std::cout << "Internal Structure    | Self-balancing BST (Red-Black)| Hash Table (Buckets/Chains)\n";
    std::cout << "Average Search Time   | O(log N)                    | O(1)\n";
    std::cout << "Worst-case Search     | O(log N)                    | O(N) (Hash collisions)\n";
    std::cout << "Average Insert Time   | O(log N)                    | O(1)\n";
    std::cout << "Average Delete Time   | O(log N)                    | O(1)\n";
    std::cout << "Key Ordering          | Strictly Sorted (Inorder)   | Unordered / Arbitrary\n";
    std::cout << "Range Queries Support | Yes (lower_bound, upper_bd) | No (Requires full scan)\n";
    std::cout << "Memory Overhead       | 3 pointers/node (Left/Right/P)| Array of buckets + chains\n";
    std::cout << "Key Requirements      | Requires operator<          | Requires std::hash & operator==\n";
    std::cout << "Best Use Case         | Sorted reports, Prefix/Range| Fast exact key lookup by ID\n";
    std::cout << "=========================================================================\n\n";
}

void SequenceMapIndex::clear()
{
    idIndex.clear();
    nameIndex.clear();
    gcIndex.clear();
    dateIndex.clear();
}

std::unordered_map<std::string, int> countKmers(const std::string& dnaSequence, int k)
{
    std::unordered_map<std::string, int> freqMap;
    if (k <= 0 || static_cast<size_t>(k) > dnaSequence.length())
    {
        return freqMap;
    }

    for (size_t i = 0; i + k <= dnaSequence.length(); ++i)
    {
        std::string kmer = dnaSequence.substr(i, k);
        freqMap[kmer]++;
    }
    return freqMap;
}

std::vector<std::pair<std::string, int>> getTopKmers(
    const std::unordered_map<std::string, int>& kmerMap,
    int k)
{
    return topKFrequentKmers(kmerMap, k);
}
