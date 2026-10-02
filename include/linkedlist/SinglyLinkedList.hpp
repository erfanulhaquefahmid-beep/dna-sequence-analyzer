#ifndef SINGLY_LINKED_LIST_HPP
#define SINGLY_LINKED_LIST_HPP

#include <iostream>
#include <vector>
#include <functional>

template <typename T>
class SinglyLinkedList
{
public:
    struct Node
    {
        T data;
        Node* next{nullptr};
        explicit Node(const T& val) : data(val), next(nullptr) {}
    };

private:
    Node* head{nullptr};
    Node* tail{nullptr};
    int nodeCount{0};

public:
    SinglyLinkedList() = default;

    // Destructor to free dynamically allocated nodes
    ~SinglyLinkedList()
    {
        clear();
    }

    // Copy constructor
    SinglyLinkedList(const SinglyLinkedList& other)
    {
        Node* curr = other.head;
        while (curr != nullptr)
        {
            insertLast(curr->data);
            curr = curr->next;
        }
    }

    // Copy assignment
    SinglyLinkedList& operator=(const SinglyLinkedList& other)
    {
        if (this != &other)
        {
            clear();
            Node* curr = other.head;
            while (curr != nullptr)
            {
                insertLast(curr->data);
                curr = curr->next;
            }
        }
        return *this;
    }

    // Move constructor
    SinglyLinkedList(SinglyLinkedList&& other) noexcept
        : head(other.head), tail(other.tail), nodeCount(other.nodeCount)
    {
        other.head = nullptr;
        other.tail = nullptr;
        other.nodeCount = 0;
    }

    // Move assignment
    SinglyLinkedList& operator=(SinglyLinkedList&& other) noexcept
    {
        if (this != &other)
        {
            clear();
            head = other.head;
            tail = other.tail;
            nodeCount = other.nodeCount;
            other.head = nullptr;
            other.tail = nullptr;
            other.nodeCount = 0;
        }
        return *this;
    }

    void clear()
    {
        Node* curr = head;
        while (curr != nullptr)
        {
            Node* nextNode = curr->next;
            delete curr;
            curr = nextNode;
        }
        head = nullptr;
        tail = nullptr;
        nodeCount = 0;
    }

    // Insert at beginning: O(1)
    void insertFirst(const T& value)
    {
        Node* newNode = new Node(value);
        if (isEmpty())
        {
            head = tail = newNode;
        }
        else
        {
            newNode->next = head;
            head = newNode;
        }
        nodeCount++;
    }

    // Insert at end: O(1) with tail pointer
    void insertLast(const T& value)
    {
        Node* newNode = new Node(value);
        if (isEmpty())
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        nodeCount++;
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

        Node* newNode = new Node(value);
        Node* curr = head;
        for (int i = 0; i < position - 1; ++i)
        {
            curr = curr->next;
        }
        newNode->next = curr->next;
        curr->next = newNode;
        nodeCount++;
    }

    // Delete first node: O(1)
    bool deleteFirst()
    {
        if (isEmpty()) return false;

        Node* temp = head;
        head = head->next;
        delete temp;
        nodeCount--;

        if (nodeCount == 0)
        {
            tail = nullptr;
        }
        return true;
    }

    // Delete last node: O(n)
    bool deleteLast()
    {
        if (isEmpty()) return false;

        if (head == tail)
        {
            delete head;
            head = tail = nullptr;
            nodeCount = 0;
            return true;
        }

        Node* curr = head;
        while (curr->next != tail)
        {
            curr = curr->next;
        }
        delete tail;
        tail = curr;
        tail->next = nullptr;
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

        Node* curr = head;
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

    // Linear search for value: O(n)
    bool search(const T& value) const
    {
        Node* curr = head;
        while (curr != nullptr)
        {
            if (curr->data == value)
            {
                return true;
            }
            curr = curr->next;
        }
        return false;
    }

    // Find node with custom predicate: O(n)
    T* findIf(std::function<bool(const T&)> predicate)
    {
        Node* curr = head;
        while (curr != nullptr)
        {
            if (predicate(curr->data))
            {
                return &(curr->data);
            }
            curr = curr->next;
        }
        return nullptr;
    }

    const T* findIf(std::function<bool(const T&)> predicate) const
    {
        Node* curr = head;
        while (curr != nullptr)
        {
            if (predicate(curr->data))
            {
                return &(curr->data);
            }
            curr = curr->next;
        }
        return nullptr;
    }

    // Delete if predicate matches
    bool deleteIf(std::function<bool(const T&)> predicate)
    {
        if (isEmpty()) return false;

        if (predicate(head->data))
        {
            return deleteFirst();
        }

        Node* curr = head;
        while (curr->next != nullptr && !predicate(curr->next->data))
        {
            curr = curr->next;
        }

        if (curr->next != nullptr)
        {
            Node* target = curr->next;
            curr->next = target->next;
            if (target == tail)
            {
                tail = curr;
            }
            delete target;
            nodeCount--;
            return true;
        }
        return false;
    }

    // Display elements
    void display() const
    {
        if (isEmpty())
        {
            std::cout << "[SinglyLinkedList: Empty]\n";
            return;
        }
        Node* curr = head;
        int idx = 0;
        while (curr != nullptr)
        {
            std::cout << "[" << idx++ << "] ";
            curr->data.display();
            curr = curr->next;
        }
    }

    // In-place iterative reversal: O(n)
    void reverse()
    {
        if (nodeCount <= 1) return;

        Node* prev = nullptr;
        Node* curr = head;
        Node* nextNode = nullptr;
        tail = head;

        while (curr != nullptr)
        {
            nextNode = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextNode;
        }
        head = prev;
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
        vec.reserve(nodeCount);
        Node* curr = head;
        while (curr != nullptr)
        {
            vec.push_back(curr->data);
            curr = curr->next;
        }
        return vec;
    }

    Node* getHead() const { return head; }
};

#endif // SINGLY_LINKED_LIST_HPP
