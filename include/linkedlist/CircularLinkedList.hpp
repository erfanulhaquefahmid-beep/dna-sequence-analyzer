#ifndef CIRCULAR_LINKED_LIST_HPP
#define CIRCULAR_LINKED_LIST_HPP

#include <iostream>
#include <vector>

template <typename T>
class CircularLinkedList
{
public:
    struct Node
    {
        T data;
        Node* next{nullptr};
        explicit Node(const T& val) : data(val), next(nullptr) {}
    };

private:
    Node* tail{nullptr}; // Pointing to tail gives O(1) access to both tail and head (tail->next)
    int nodeCount{0};

public:
    CircularLinkedList() = default;

    ~CircularLinkedList()
    {
        clear();
    }

    CircularLinkedList(const CircularLinkedList& other)
    {
        if (other.tail == nullptr) return;
        Node* curr = other.tail->next;
        do
        {
            insertLast(curr->data);
            curr = curr->next;
        } while (curr != other.tail->next);
    }

    CircularLinkedList& operator=(const CircularLinkedList& other)
    {
        if (this != &other)
        {
            clear();
            if (other.tail != nullptr)
            {
                Node* curr = other.tail->next;
                do
                {
                    insertLast(curr->data);
                    curr = curr->next;
                } while (curr != other.tail->next);
            }
        }
        return *this;
    }

    CircularLinkedList(CircularLinkedList&& other) noexcept
        : tail(other.tail), nodeCount(other.nodeCount)
    {
        other.tail = nullptr;
        other.nodeCount = 0;
    }

    CircularLinkedList& operator=(CircularLinkedList&& other) noexcept
    {
        if (this != &other)
        {
            clear();
            tail = other.tail;
            nodeCount = other.nodeCount;
            other.tail = nullptr;
            other.nodeCount = 0;
        }
        return *this;
    }

    void clear()
    {
        if (tail == nullptr) return;

        Node* head = tail->next;
        Node* curr = head;
        while (curr != tail)
        {
            Node* nxt = curr->next;
            delete curr;
            curr = nxt;
        }
        delete tail;
        tail = nullptr;
        nodeCount = 0;
    }

    // Insert at beginning: O(1)
    void insertFirst(const T& value)
    {
        Node* newNode = new Node(value);
        if (isEmpty())
        {
            tail = newNode;
            tail->next = tail;
        }
        else
        {
            newNode->next = tail->next;
            tail->next = newNode;
        }
        nodeCount++;
    }

    // Insert at end: O(1)
    void insertLast(const T& value)
    {
        insertFirst(value);
        tail = tail->next; // The newly inserted node is now the tail
    }

    // Insert at specified 0-based position: O(n)
    void insertAtPosition(int position, const T& value)
    {
        if (position <= 0)
        {
            insertFirst(value);
            return;
        }
        if (position >= nodeCount)
        {
            insertLast(value);
            return;
        }

        Node* curr = tail->next; // head
        for (int i = 0; i < position - 1; ++i)
        {
            curr = curr->next;
        }
        Node* newNode = new Node(value);
        newNode->next = curr->next;
        curr->next = newNode;
        nodeCount++;
    }

    // Delete first node: O(1)
    bool deleteFirst()
    {
        if (isEmpty()) return false;

        Node* head = tail->next;
        if (tail == head) // single element
        {
            delete head;
            tail = nullptr;
        }
        else
        {
            tail->next = head->next;
            delete head;
        }
        nodeCount--;
        return true;
    }

    // Delete last node: O(n)
    bool deleteLast()
    {
        if (isEmpty()) return false;

        Node* head = tail->next;
        if (tail == head)
        {
            delete tail;
            tail = nullptr;
        }
        else
        {
            Node* curr = head;
            while (curr->next != tail)
            {
                curr = curr->next;
            }
            curr->next = tail->next;
            delete tail;
            tail = curr;
        }
        nodeCount--;
        return true;
    }

    // Delete at specified 0-based position: O(n)
    bool deleteAtPosition(int position)
    {
        if (position < 0 || position >= nodeCount || isEmpty())
        {
            return false;
        }
        if (position == 0)
        {
            return deleteFirst();
        }
        if (position == nodeCount - 1)
        {
            return deleteLast();
        }

        Node* curr = tail->next; // head
        for (int i = 0; i < position - 1; ++i)
        {
            curr = curr->next;
        }
        Node* target = curr->next;
        curr->next = target->next;
        delete target;
        nodeCount--;
        return true;
    }

    void display() const
    {
        if (isEmpty())
        {
            std::cout << "[CircularLinkedList: Empty]\n";
            return;
        }
        Node* curr = tail->next; // head
        int idx = 0;
        do
        {
            std::cout << "[Circ " << idx++ << "] ";
            std::cout << curr->data << "\n";
            curr = curr->next;
        } while (curr != tail->next);
    }

    int size() const
    {
        return nodeCount;
    }

    bool isEmpty() const
    {
        return nodeCount == 0;
    }

    std::vector<T> toVector() const
    {
        std::vector<T> vec;
        if (isEmpty()) return vec;
        vec.reserve(nodeCount);
        Node* curr = tail->next;
        do
        {
            vec.push_back(curr->data);
            curr = curr->next;
        } while (curr != tail->next);
        return vec;
    }
};

#endif // CIRCULAR_LINKED_LIST_HPP
