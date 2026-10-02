#include "../../include/common/ISequenceIndex.hpp"

// TreeSequenceIndex implementation
void TreeSequenceIndex::addSequence(const SequenceRecord& record)
{
    avl.insert(record);
}

bool TreeSequenceIndex::removeSequenceById(int id)
{
    return avl.removeById(id);
}

SequenceRecord* TreeSequenceIndex::findSequenceById(int id)
{
    return avl.searchById(id);
}

std::vector<SequenceRecord> TreeSequenceIndex::searchByName(const std::string& name)
{
    std::vector<SequenceRecord> results;
    // Helper lambda to collect matching records
    std::function<void(AVLNode*)> dfs = [&](AVLNode* node) {
        if (!node) return;
        dfs(node->left);
        if (node->record.sequenceName == name)
        {
            results.push_back(node->record);
        }
        dfs(node->right);
    };
    dfs(avl.getRoot());
    return results;
}

// MapSequenceIndex implementation
void MapSequenceIndex::addSequence(const SequenceRecord& record)
{
    mapIndex.addRecord(record);
}

bool MapSequenceIndex::removeSequenceById(int id)
{
    return mapIndex.removeRecordById(id);
}

SequenceRecord* MapSequenceIndex::findSequenceById(int id)
{
    return mapIndex.findById(id);
}

std::vector<SequenceRecord> MapSequenceIndex::searchByName(const std::string& name)
{
    std::vector<SequenceRecord> results;
    std::vector<int> ids = mapIndex.findIdsByName(name);
    for (int id : ids)
    {
        SequenceRecord* r = mapIndex.findById(id);
        if (r)
        {
            results.push_back(*r);
        }
    }
    return results;
}
