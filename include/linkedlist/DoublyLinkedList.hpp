#ifndef DOUBLY_LINKED_LIST_HPP
#define DOUBLY_LINKED_LIST_HPP

#include <iostream>
#include <vector>

template <typename T>
class DoublyLinkedList
{
public:
    struct Node
    {
        T data;
        Node* prev{nullptr};
        Node* next{nullptr};
        explicit Node(const T& val) : data(val), prev(nullptr), next(nullptr) {}
    };

private:
    Node* head{nullptr};
    Node* tail{nullptr};
    int nodeCount{0};

public:
    DoublyLinkedList() = default;

    ~DoublyLinkedList()
    {
        clear();
    }

    DoublyLinkedList(const DoublyLinkedList& other)
    {
        Node* curr = other.head;
        while (curr != nullptr)
        {
            insertLast(curr->data);
            curr = curr->next;
        }
    }

    DoublyLinkedList& operator=(const DoublyLinkedList& other)
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

    DoublyLinkedList(DoublyLinkedList&& other) noexcept
        : head(other.head), tail(other.tail), nodeCount(other.nodeCount)
    {
        other.head = nullptr;
        other.tail = nullptr;
        other.nodeCount = 0;
    }

    DoublyLinkedList& operator=(DoublyLinkedList&& other) noexcept
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
            Node* nxt = curr->next;
            delete curr;
            curr = nxt;
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
            head->prev = newNode;
            head = newNode;
        }
        nodeCount++;
    }

    // Insert at end: O(1)
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
            newNode->prev = tail;
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
        for (int i = 0; i < position; ++i)
        {
            curr = curr->next;
        }

        newNode->next = curr;
        newNode->prev = curr->prev;
        if (curr->prev != nullptr)
        {
            curr->prev->next = newNode;
        }
        curr->prev = newNode;
        nodeCount++;
    }

    // Delete first node: O(1)
    bool deleteFirst()
    {
        if (isEmpty()) return false;

        Node* temp = head;
        if (head == tail)
        {
            head = tail = nullptr;
        }
        else
        {
            head = head->next;
            head->prev = nullptr;
        }
        delete temp;
        nodeCount--;
        return true;
    }

    // Delete last node: O(1)
    bool deleteLast()
    {
        if (isEmpty()) return false;

        Node* temp = tail;
        if (head == tail)
        {
            head = tail = nullptr;
        }
        else
        {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete temp;
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
        for (int i = 0; i < position; ++i)
        {
            curr = curr->next;
        }

        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        delete curr;
        nodeCount--;
        return true;
    }

    void displayForward() const
    {
        if (isEmpty())
        {
            std::cout << "[DoublyLinkedList: Empty]\n";
            return;
        }
        Node* curr = head;
        int idx = 0;
        while (curr != nullptr)
        {
            std::cout << "[Fwd " << idx++ << "] ";
            curr->data.display();
            curr = curr->next;
        }
    }

    void displayBackward() const
    {
        if (isEmpty())
        {
            std::cout << "[DoublyLinkedList: Empty]\n";
            return;
        }
        Node* curr = tail;
        int idx = nodeCount - 1;
        while (curr != nullptr)
        {
            std::cout << "[Rev " << idx-- << "] ";
            curr->data.display();
            curr = curr->prev;
        }
    }

    // Invert pointers to reverse: O(n)
    void reverse()
    {
        if (nodeCount <= 1) return;

        Node* curr = head;
        Node* temp = nullptr;
        while (curr != nullptr)
        {
            temp = curr->prev;
            curr->prev = curr->next;
            curr->next = temp;
            curr = curr->prev; // because curr->prev was next
        }
        if (temp != nullptr)
        {
            tail = head;
            head = temp->prev;
        }
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
};

#endif // DOUBLY_LINKED_LIST_HPP
