#ifndef RECENT_SEQUENCE_LIST_HPP
#define RECENT_SEQUENCE_LIST_HPP

#include "CircularLinkedList.hpp"
#include <string>
#include <vector>

class RecentSequenceList
{
private:
    CircularLinkedList<std::string> circularList;
    int maxCapacity{5};

public:
    explicit RecentSequenceList(int capacity = 5);

    void addRecent(const std::string& sequenceNameOrId);
    void displayRecent() const;
    std::vector<std::string> toVector() const;
    int size() const;
    void clear();
};

#endif // RECENT_SEQUENCE_LIST_HPP
