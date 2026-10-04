#ifndef BTREE_DEMO_HPP
#define BTREE_DEMO_HPP

#include <iostream>
#include <vector>

/**
 * @brief Educational 2-3 / B-Tree Demonstration
 * Shows multi-way search tree where every internal node can have 1 or 2 keys (2 or 3 children).
 * Used to demonstrate disk-friendly and multi-key indexing in the DSA syllabus.
 */
class BTreeDemo
{
public:
    struct Node
    {
        bool isLeaf{true};
        std::vector<int> keys;
        std::vector<Node*> children;

        explicit Node(bool leaf) : isLeaf(leaf) {}

        ~Node()
        {
            for (Node* child : children)
            {
                delete child;
            }
        }
    };

private:
    Node* root{nullptr};
    int minDegree{2}; // B-Tree of order 3 (2-3 tree behavior)

    void splitChild(Node* parent, int i, Node* child)
    {
        Node* sibling = new Node(child->isLeaf);
        int midKey = child->keys[minDegree - 1];

        // Give half keys to sibling
        for (size_t j = minDegree; j < child->keys.size(); ++j)
        {
            sibling->keys.push_back(child->keys[j]);
        }

        if (!child->isLeaf)
        {
            for (size_t j = minDegree; j < child->children.size(); ++j)
            {
                sibling->children.push_back(child->children[j]);
            }
            child->children.resize(minDegree);
        }

        child->keys.resize(minDegree - 1);

        parent->children.insert(parent->children.begin() + i + 1, sibling);
        parent->keys.insert(parent->keys.begin() + i, midKey);
    }

    void insertNonFull(Node* node, int key)
    {
        int i = static_cast<int>(node->keys.size()) - 1;

        if (node->isLeaf)
        {
            node->keys.push_back(0);
            while (i >= 0 && node->keys[i] > key)
            {
                node->keys[i + 1] = node->keys[i];
                i--;
            }
            node->keys[i + 1] = key;
        }
        else
        {
            while (i >= 0 && node->keys[i] > key)
            {
                i--;
            }
            i++;

            if (static_cast<int>(node->children[i]->keys.size()) == 2 * minDegree - 1)
            {
                splitChild(node, i, node->children[i]);
                if (node->keys[i] < key)
                {
                    i++;
                }
            }
            insertNonFull(node->children[i], key);
        }
    }

    void printHelper(Node* node, int level) const
    {
        if (node == nullptr) return;

        std::cout << "Level " << level << ": [ ";
        for (int k : node->keys)
        {
            std::cout << k << " ";
        }
        std::cout << "]\n";

        for (Node* child : node->children)
        {
            printHelper(child, level + 1);
        }
    }

public:
    explicit BTreeDemo(int t = 2) : root(nullptr), minDegree(t) {}

    ~BTreeDemo()
    {
        delete root;
    }

    void insert(int key)
    {
        if (root == nullptr)
        {
            root = new Node(true);
            root->keys.push_back(key);
            return;
        }

        if (static_cast<int>(root->keys.size()) == 2 * minDegree - 1)
        {
            Node* newRoot = new Node(false);
            newRoot->children.push_back(root);
            splitChild(newRoot, 0, root);

            int i = (newRoot->keys[0] < key) ? 1 : 0;
            insertNonFull(newRoot->children[i], key);
            root = newRoot;
        }
        else
        {
            insertNonFull(root, key);
        }
    }

    void display() const
    {
        if (root == nullptr)
        {
            std::cout << "[B-Tree: Empty]\n";
            return;
        }
        std::cout << "\n--- B-Tree / 2-3 Tree Multi-Way Hierarchy ---\n";
        printHelper(root, 0);
        std::cout << "---------------------------------------------\n";
    }
};

#endif // BTREE_DEMO_HPP
