#include "../../include/tree/AVLTree.hpp"
#include <iostream>
#include <algorithm>
#include <iomanip>

AVLTree::AVLTree() : root(nullptr), nodeCount(0) {}

AVLTree::~AVLTree()
{
    clear();
}

void AVLTree::clearHelper(AVLNode* node)
{
    if (node != nullptr)
    {
        clearHelper(node->left);
        clearHelper(node->right);
        delete node;
    }
}

void AVLTree::clear()
{
    clearHelper(root);
    root = nullptr;
    nodeCount = 0;
}

int AVLTree::getNodeHeight(AVLNode* node) const
{
    return node != nullptr ? node->height : 0;
}

int AVLTree::updateHeight(AVLNode* node)
{
    if (node == nullptr) return 0;
    node->height = 1 + std::max(getNodeHeight(node->left), getNodeHeight(node->right));
    return node->height;
}

int AVLTree::balanceFactor(AVLNode* node) const
{
    return node != nullptr ? getNodeHeight(node->left) - getNodeHeight(node->right) : 0;
}

AVLNode* AVLTree::rotateRight(AVLNode* y)
{
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    updateHeight(y);
    updateHeight(x);

    return x;
}

AVLNode* AVLTree::rotateLeft(AVLNode* x)
{
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    updateHeight(x);
    updateHeight(y);

    return y;
}

AVLNode* AVLTree::rotateLeftRight(AVLNode* node)
{
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

AVLNode* AVLTree::rotateRightLeft(AVLNode* node)
{
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}

AVLNode* AVLTree::balance(AVLNode* node)
{
    if (node == nullptr) return nullptr;

    updateHeight(node);
    int bf = balanceFactor(node);

    // Left heavy
    if (bf > 1)
    {
        if (balanceFactor(node->left) >= 0)
        {
            // Left-Left (LL)
            return rotateRight(node);
        }
        else
        {
            // Left-Right (LR)
            return rotateLeftRight(node);
        }
    }

    // Right heavy
    if (bf < -1)
    {
        if (balanceFactor(node->right) <= 0)
        {
            // Right-Right (RR)
            return rotateLeft(node);
        }
        else
        {
            // Right-Left (RL)
            return rotateRightLeft(node);
        }
    }

    return node;
}

AVLNode* AVLTree::insertHelper(AVLNode* node, const SequenceRecord& record)
{
    if (node == nullptr)
    {
        nodeCount++;
        return new AVLNode(record);
    }

    if (record.id < node->record.id)
    {
        node->left = insertHelper(node->left, record);
    }
    else if (record.id > node->record.id)
    {
        node->right = insertHelper(node->right, record);
    }
    else
    {
        // Update duplicate
        node->record = record;
        return node;
    }

    return balance(node);
}

void AVLTree::insert(const SequenceRecord& record)
{
    root = insertHelper(root, record);
}

AVLNode* AVLTree::findMin(AVLNode* node) const
{
    while (node != nullptr && node->left != nullptr)
    {
        node = node->left;
    }
    return node;
}

AVLNode* AVLTree::removeHelper(AVLNode* node, int id, bool& removed)
{
    if (node == nullptr)
    {
        removed = false;
        return nullptr;
    }

    if (id < node->record.id)
    {
        node->left = removeHelper(node->left, id, removed);
    }
    else if (id > node->record.id)
    {
        node->right = removeHelper(node->right, id, removed);
    }
    else
    {
        removed = true;
        nodeCount--;

        if (node->left == nullptr || node->right == nullptr)
        {
            AVLNode* temp = node->left ? node->left : node->right;
            if (temp == nullptr)
            {
                // No child
                temp = node;
                node = nullptr;
            }
            else
            {
                // One child
                *node = *temp;
            }
            delete temp;
        }
        else
        {
            // Two children
            AVLNode* temp = findMin(node->right);
            node->record = temp->record;
            nodeCount++; // compensate for next call
            node->right = removeHelper(node->right, temp->record.id, removed);
        }
    }

    if (node == nullptr) return nullptr;

    return balance(node);
}

bool AVLTree::removeById(int id)
{
    bool removed = false;
    root = removeHelper(root, id, removed);
    return removed;
}

AVLNode* AVLTree::searchHelper(AVLNode* node, int id) const
{
    if (node == nullptr || node->record.id == id)
    {
        return node;
    }
    if (id < node->record.id)
    {
        return searchHelper(node->left, id);
    }
    return searchHelper(node->right, id);
}

SequenceRecord* AVLTree::searchById(int id)
{
    AVLNode* res = searchHelper(root, id);
    return res != nullptr ? &(res->record) : nullptr;
}

void AVLTree::rangeLengthHelper(AVLNode* node, int minL, int maxL, std::vector<SequenceRecord>& result) const
{
    if (node == nullptr) return;
    rangeLengthHelper(node->left, minL, maxL, result);
    if (node->record.length >= minL && node->record.length <= maxL)
    {
        result.push_back(node->record);
    }
    rangeLengthHelper(node->right, minL, maxL, result);
}

std::vector<SequenceRecord> AVLTree::rangeSearchByLength(int minLength, int maxLength)
{
    std::vector<SequenceRecord> results;
    rangeLengthHelper(root, minLength, maxLength, results);
    return results;
}

void AVLTree::rangeGCHelper(AVLNode* node, double minGC, double maxGC, std::vector<SequenceRecord>& result) const
{
    if (node == nullptr) return;
    rangeGCHelper(node->left, minGC, maxGC, result);
    if (node->record.gcContent >= minGC && node->record.gcContent <= maxGC)
    {
        result.push_back(node->record);
    }
    rangeGCHelper(node->right, minGC, maxGC, result);
}

std::vector<SequenceRecord> AVLTree::rangeSearchByGC(double minGC, double maxGC)
{
    std::vector<SequenceRecord> results;
    rangeGCHelper(root, minGC, maxGC, results);
    return results;
}

void AVLTree::inorderHelper(AVLNode* node, const std::function<void(const SequenceRecord&)>& visitor) const
{
    if (node == nullptr) return;
    inorderHelper(node->left, visitor);
    visitor(node->record);
    inorderHelper(node->right, visitor);
}

void AVLTree::inorderTraversal() const
{
    if (isEmpty())
    {
        std::cout << "[AVL Tree: Empty]\n";
        return;
    }
    std::cout << "\n--- AVL Tree Inorder Traversal (Sorted by ID) ---\n";
    SequenceRecord::printHeader();
    inorderHelper(root, [](const SequenceRecord& r) { r.display(); });
    std::cout << "\n";
}

std::vector<SequenceRecord> AVLTree::toInorderVector() const
{
    std::vector<SequenceRecord> vec;
    inorderHelper(root, [&vec](const SequenceRecord& r) {
        vec.push_back(r);
    });
    return vec;
}

void AVLTree::printTreeHelper(AVLNode* node, int indent) const
{
    if (node != nullptr)
    {
        if (node->right)
        {
            printTreeHelper(node->right, indent + 8);
        }
        if (indent)
        {
            std::cout << std::setw(indent) << ' ';
        }
        std::cout << "[ID:" << node->record.id << " H:" << node->height << " BF:" << balanceFactor(node) << "]\n";
        if (node->left)
        {
            printTreeHelper(node->left, indent + 8);
        }
    }
}

void AVLTree::printTreeStructure() const
{
    if (isEmpty())
    {
        std::cout << "[AVL Tree: Empty]\n";
        return;
    }
    std::cout << "\n--- AVL Visual Structure (Rotated 90 deg clockwise) ---\n";
    printTreeHelper(root, 0);
    std::cout << "---------------------------------------------------------\n";
}

int AVLTree::height() const
{
    return getNodeHeight(root);
}

bool AVLTree::isEmpty() const
{
    return root == nullptr;
}

int AVLTree::size() const
{
    return nodeCount;
}
