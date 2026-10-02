#ifndef I_SEQUENCE_INDEX_HPP
#define I_SEQUENCE_INDEX_HPP

#include "SequenceRecord.hpp"
#include "../tree/AVLTree.hpp"
#include "../map/SequenceMapIndex.hpp"
#include <vector>
#include <string>
#include <memory>

/**
 * @brief Common Interface for Indexing Sequences in the Full Project.
 * Allows the team to switch seamlessly between a Tree-based Index and a Map-based Index.
 */
class ISequenceIndex
{
public:
    virtual ~ISequenceIndex() = default;
    virtual void addSequence(const SequenceRecord& record) = 0;
    virtual bool removeSequenceById(int id) = 0;
    virtual SequenceRecord* findSequenceById(int id) = 0;
    virtual std::vector<SequenceRecord> searchByName(const std::string& name) = 0;
    virtual std::string getIndexType() const = 0;
};

/**
 * @brief TreeSequenceIndex implements ISequenceIndex using a self-balancing AVL Tree.
 * Worst-case lookup and insertion is guaranteed O(log N).
 */
class TreeSequenceIndex : public ISequenceIndex
{
private:
    AVLTree avl;

public:
    TreeSequenceIndex() = default;

    void addSequence(const SequenceRecord& record) override;
    bool removeSequenceById(int id) override;
    SequenceRecord* findSequenceById(int id) override;
    std::vector<SequenceRecord> searchByName(const std::string& name) override;
    std::string getIndexType() const override { return "TreeSequenceIndex (AVL Tree)"; }

    AVLTree& getAVL() { return avl; }
};

/**
 * @brief MapSequenceIndex implements ISequenceIndex using STL unordered_map and map.
 * Average lookup by ID is O(1).
 */
class MapSequenceIndex : public ISequenceIndex
{
private:
    SequenceMapIndex mapIndex;

public:
    MapSequenceIndex() = default;

    void addSequence(const SequenceRecord& record) override;
    bool removeSequenceById(int id) override;
    SequenceRecord* findSequenceById(int id) override;
    std::vector<SequenceRecord> searchByName(const std::string& name) override;
    std::string getIndexType() const override { return "MapSequenceIndex (STL Map / Hash)"; }

    SequenceMapIndex& getMapIndex() { return mapIndex; }
};

#endif // I_SEQUENCE_INDEX_HPP
