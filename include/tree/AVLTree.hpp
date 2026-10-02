#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include "../common/SequenceRecord.hpp"
#include <vector>
#include <functional>

struct AVLNode
{
    SequenceRecord record;
    AVLNode* left{nullptr};
    AVLNode* right{nullptr};
    int height{1};

    explicit AVLNode(const SequenceRecord& rec)
        : record(rec), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree
{
private:
    AVLNode* root{nullptr};
    int nodeCount{0};

    int getNodeHeight(AVLNode* node) const;
    int updateHeight(AVLNode* node);
    AVLNode* rotateLeft(AVLNode* node);
    AVLNode* rotateRight(AVLNode* node);
    AVLNode* rotateLeftRight(AVLNode* node);
    AVLNode* rotateRightLeft(AVLNode* node);
    AVLNode* balance(AVLNode* node);

    AVLNode* insertHelper(AVLNode* node, const SequenceRecord& record);
    AVLNode* removeHelper(AVLNode* node, int id, bool& removed);
    AVLNode* findMin(AVLNode* node) const;
    AVLNode* searchHelper(AVLNode* node, int id) const;

    void inorderHelper(AVLNode* node, const std::function<void(const SequenceRecord&)>& visitor) const;
    void rangeLengthHelper(AVLNode* node, int minL, int maxL, std::vector<SequenceRecord>& result) const;
    void rangeGCHelper(AVLNode* node, double minGC, double maxGC, std::vector<SequenceRecord>& result) const;
    void clearHelper(AVLNode* node);
    void printTreeHelper(AVLNode* node, int indent) const;

public:
    AVLTree();
    ~AVLTree();

    AVLTree(const AVLTree& other) = delete;
    AVLTree& operator=(const AVLTree& other) = delete;

    void insert(const SequenceRecord& record);
    bool removeById(int id);
    SequenceRecord* searchById(int id);
    std::vector<SequenceRecord> rangeSearchByLength(int minLength, int maxLength);
    std::vector<SequenceRecord> rangeSearchByGC(double minGC, double maxGC);

    void inorderTraversal() const;
    std::vector<SequenceRecord> toInorderVector() const;
    void printTreeStructure() const;
    int height() const;
    int balanceFactor(AVLNode* node) const;
    bool isEmpty() const;
    int size() const;
    void clear();

    AVLNode* getRoot() const { return root; }
};

#endif // AVL_TREE_HPP
