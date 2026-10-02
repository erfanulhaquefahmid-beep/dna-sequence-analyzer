#include "../../include/tree/BinarySearchTree.hpp"
#include <iostream>
#include <algorithm>
#include <functional>

BinarySearchTree::BinarySearchTree() : root(nullptr), nodeCount(0) {}

BinarySearchTree::~BinarySearchTree()
{
    clear();
}

void BinarySearchTree::clearHelper(BSTNode* node)
{
    if (node != nullptr)
    {
        clearHelper(node->left);
        clearHelper(node->right);
        delete node;
    }
}

void BinarySearchTree::clear()
{
    clearHelper(root);
    root = nullptr;
    nodeCount = 0;
}

BSTNode* BinarySearchTree::insertHelper(BSTNode* node, const SequenceRecord& record)
{
    if (node == nullptr)
    {
        nodeCount++;
        return new BSTNode(record);
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
        // Duplicate ID: update existing record in place
        node->record = record;
    }
    return node;
}

void BinarySearchTree::insert(const SequenceRecord& record)
{
    root = insertHelper(root, record);
}

BSTNode* BinarySearchTree::findMin(BSTNode* node) const
{
    while (node != nullptr && node->left != nullptr)
    {
        node = node->left;
    }
    return node;
}

BSTNode* BinarySearchTree::removeHelper(BSTNode* node, int id, bool& removed)
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
        // Node found
        removed = true;
        nodeCount--;

        // Case 1 & 2: Leaf node or one child
        if (node->left == nullptr)
        {
            BSTNode* rightChild = node->right;
            delete node;
            return rightChild;
        }
        else if (node->right == nullptr)
        {
            BSTNode* leftChild = node->left;
            delete node;
            return leftChild;
        }

        // Case 3: Node with two children
        // Find inorder successor (smallest node in the right subtree)
        BSTNode* successor = findMin(node->right);
        node->record = successor->record;
        nodeCount++; // compensate because removeHelper will decrement nodeCount
        node->right = removeHelper(node->right, successor->record.id, removed);
    }
    return node;
}

bool BinarySearchTree::removeById(int id)
{
    bool removed = false;
    root = removeHelper(root, id, removed);
    return removed;
}

BSTNode* BinarySearchTree::searchHelper(BSTNode* node, int id) const
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

SequenceRecord* BinarySearchTree::searchById(int id)
{
    BSTNode* res = searchHelper(root, id);
    return res != nullptr ? &(res->record) : nullptr;
}

void BinarySearchTree::searchByNameHelper(BSTNode* node, const std::string& name, std::vector<SequenceRecord>& result) const
{
    if (node == nullptr) return;
    searchByNameHelper(node->left, name, result);
    if (node->record.sequenceName == name)
    {
        result.push_back(node->record);
    }
    searchByNameHelper(node->right, name, result);
}

std::vector<SequenceRecord> BinarySearchTree::searchByName(const std::string& name)
{
    std::vector<SequenceRecord> results;
    searchByNameHelper(root, name, results);
    return results;
}

void BinarySearchTree::inorderHelper(BSTNode* node, const std::function<void(const SequenceRecord&)>& visitor) const
{
    if (node == nullptr) return;
    inorderHelper(node->left, visitor);
    visitor(node->record);
    inorderHelper(node->right, visitor);
}

void BinarySearchTree::preorderHelper(BSTNode* node, const std::function<void(const SequenceRecord&)>& visitor) const
{
    if (node == nullptr) return;
    visitor(node->record);
    preorderHelper(node->left, visitor);
    preorderHelper(node->right, visitor);
}

void BinarySearchTree::postorderHelper(BSTNode* node, const std::function<void(const SequenceRecord&)>& visitor) const
{
    if (node == nullptr) return;
    postorderHelper(node->left, visitor);
    postorderHelper(node->right, visitor);
    visitor(node->record);
}

void BinarySearchTree::inorderTraversal() const
{
    if (isEmpty())
    {
        std::cout << "[BST: Empty]\n";
        return;
    }
    std::cout << "\n--- BST Inorder Traversal (Sorted by ID) ---\n";
    SequenceRecord::printHeader();
    inorderHelper(root, [](const SequenceRecord& r) { r.display(); });
    std::cout << "\n";
}

void BinarySearchTree::preorderTraversal() const
{
    if (isEmpty())
    {
        std::cout << "[BST: Empty]\n";
        return;
    }
    std::cout << "\n--- BST Preorder Traversal (Root, Left, Right) ---\n";
    SequenceRecord::printHeader();
    preorderHelper(root, [](const SequenceRecord& r) { r.display(); });
    std::cout << "\n";
}

void BinarySearchTree::postorderTraversal() const
{
    if (isEmpty())
    {
        std::cout << "[BST: Empty]\n";
        return;
    }
    std::cout << "\n--- BST Postorder Traversal (Left, Right, Root) ---\n";
    SequenceRecord::printHeader();
    postorderHelper(root, [](const SequenceRecord& r) { r.display(); });
    std::cout << "\n";
}

int BinarySearchTree::heightHelper(BSTNode* node) const
{
    if (node == nullptr) return 0;
    return 1 + std::max(heightHelper(node->left), heightHelper(node->right));
}

int BinarySearchTree::height() const
{
    return heightHelper(root);
}

bool BinarySearchTree::isEmpty() const
{
    return root == nullptr;
}

int BinarySearchTree::size() const
{
    return nodeCount;
}

std::vector<SequenceRecord> BinarySearchTree::toInorderVector() const
{
    std::vector<SequenceRecord> vec;
    inorderHelper(root, [&vec](const SequenceRecord& r) {
        vec.push_back(r);
    });
    return vec;
}
