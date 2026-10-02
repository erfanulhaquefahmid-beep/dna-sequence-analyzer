#ifndef ARRAY_LINKED_LIST_HPP
#define ARRAY_LINKED_LIST_HPP

#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Array implementation of Linked List (Cursor / Static Linked List)
 * Uses parallel arrays data[] and next[] with a free-list pool.
 * Demonstrates node allocation and pointer simulation without OS heap calls.
 */
class ArrayLinkedList
{
private:
    static constexpr int CAPACITY = 50;

    std::string data[CAPACITY];
    int next[CAPACITY];
    int head{-1};
    int freeHead{0};
    int count{0};

    int allocateNode()
    {
        if (freeHead == -1)
        {
            return -1; // Out of memory pool
        }
        int allocatedIndex = freeHead;
        freeHead = next[freeHead];
        next[allocatedIndex] = -1;
        return allocatedIndex;
    }

    void deallocateNode(int index)
    {
        if (index < 0 || index >= CAPACITY) return;
        data[index].clear();
        next[index] = freeHead;
        freeHead = index;
    }

public:
    ArrayLinkedList()
    {
        // Initialize free list chain
        for (int i = 0; i < CAPACITY - 1; ++i)
        {
            next[i] = i + 1;
        }
        next[CAPACITY - 1] = -1;
    }

    bool isFull() const
    {
        return count >= CAPACITY || freeHead == -1;
    }

    bool isEmpty() const
    {
        return count == 0 || head == -1;
    }

    int size() const
    {
        return count;
    }

    // Insert at beginning: O(1)
    bool insertFirst(const std::string& val)
    {
        int newNode = allocateNode();
        if (newNode == -1)
        {
            std::cerr << "[ArrayLinkedList] Error: Pool full!\n";
            return false;
        }

        data[newNode] = val;
        next[newNode] = head;
        head = newNode;
        count++;
        return true;
    }

    // Insert at end: O(n)
    bool insertLast(const std::string& val)
    {
        if (isEmpty())
        {
            return insertFirst(val);
        }

        int newNode = allocateNode();
        if (newNode == -1)
        {
            std::cerr << "[ArrayLinkedList] Error: Pool full!\n";
            return false;
        }

        data[newNode] = val;
        next[newNode] = -1;

        int curr = head;
        while (next[curr] != -1)
        {
            curr = next[curr];
        }
        next[curr] = newNode;
        count++;
        return true;
    }

    // Insert at specified 0-based position: O(n)
    bool insertAtPosition(int position, const std::string& val)
    {
        if (position <= 0)
        {
            return insertFirst(val);
        }
        if (position >= count)
        {
            return insertLast(val);
        }

        int newNode = allocateNode();
        if (newNode == -1) return false;

        data[newNode] = val;
        int curr = head;
        for (int i = 0; i < position - 1; ++i)
        {
            curr = next[curr];
        }
        next[newNode] = next[curr];
        next[curr] = newNode;
        count++;
        return true;
    }

    // Delete from beginning: O(1)
    bool deleteFirst()
    {
        if (isEmpty()) return false;

        int temp = head;
        head = next[head];
        deallocateNode(temp);
        count--;
        return true;
    }

    // Delete from end: O(n)
    bool deleteLast()
    {
        if (isEmpty()) return false;

        if (next[head] == -1)
        {
            deallocateNode(head);
            head = -1;
            count = 0;
            return true;
        }

        int curr = head;
        while (next[next[curr]] != -1)
        {
            curr = next[curr];
        }

        int temp = next[curr];
        next[curr] = -1;
        deallocateNode(temp);
        count--;
        return true;
    }

    // Delete at specified 0-based position: O(n)
    bool deleteAtPosition(int position)
    {
        if (position < 0 || position >= count || isEmpty()) return false;
        if (position == 0) return deleteFirst();

        int curr = head;
        for (int i = 0; i < position - 1; ++i)
        {
            curr = next[curr];
        }

        int target = next[curr];
        next[curr] = next[target];
        deallocateNode(target);
        count--;
        return true;
    }

    void display() const
    {
        if (isEmpty())
        {
            std::cout << "[ArrayLinkedList: Empty]\n";
            return;
        }

        std::cout << "Array-based Linked List (Cursor representation):\n";
        std::cout << "Head index: " << head << ", Free list head: " << freeHead << ", Size: " << count << "\n";
        int curr = head;
        int logicalPos = 0;
        while (curr != -1)
        {
            std::cout << "  Pos " << logicalPos++ << " [Slot " << curr << "]: \"" 
                      << data[curr] << "\" -> Next slot: " << next[curr] << "\n";
            curr = next[curr];
        }
    }

    std::vector<std::string> toVector() const
    {
        std::vector<std::string> vec;
        int curr = head;
        while (curr != -1)
        {
            vec.push_back(data[curr]);
            curr = next[curr];
        }
        return vec;
    }
};

#endif // ARRAY_LINKED_LIST_HPP
