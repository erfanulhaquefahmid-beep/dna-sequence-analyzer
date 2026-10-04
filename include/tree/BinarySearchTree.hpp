#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include "../common/SequenceRecord.hpp"
#include <vector>
#include <string>
#include <functional>

struct BSTNode
{
    SequenceRecord record;
    BSTNode* left{nullptr};
    BSTNode* right{nullptr};

    explicit BSTNode(const SequenceRecord& rec)
        : record(rec), left(nullptr), right(nullptr) {}
};

class BinarySearchTree
{
private:
    BSTNode* root{nullptr};
    int nodeCount{0};

    BSTNode* insertHelper(BSTNode* node, const SequenceRecord& record);
    BSTNode* removeHelper(BSTNode* node, int id, bool& removed);
    BSTNode* findMin(BSTNode* node) const;
    void inorderHelper(BSTNode* node, const std::function<void(const SequenceRecord&)>& visitor) const;
    void preorderHelper(BSTNode* node, const std::function<void(const SequenceRecord&)>& visitor) const;
    void postorderHelper(BSTNode* node, const std::function<void(const SequenceRecord&)>& visitor) const;
    int heightHelper(BSTNode* node) const;
    void clearHelper(BSTNode* node);
    BSTNode* searchHelper(BSTNode* node, int id) const;
    void searchByNameHelper(BSTNode* node, const std::string& name, std::vector<SequenceRecord>& result) const;

public:
    BinarySearchTree();
    ~BinarySearchTree();

    BinarySearchTree(const BinarySearchTree& other) = delete;
    BinarySearchTree& operator=(const BinarySearchTree& other) = delete;

    void insert(const SequenceRecord& record);
    bool removeById(int id);
    SequenceRecord* searchById(int id);
    std::vector<SequenceRecord> searchByName(const std::string& name);

    void inorderTraversal() const;
    void preorderTraversal() const;
    void postorderTraversal() const;
    std::vector<SequenceRecord> toInorderVector() const;

    int height() const;
    bool isEmpty() const;
    int size() const;
    void clear();

    BSTNode* getRoot() const { return root; }
};

#endif // BINARY_SEARCH_TREE_HPP
