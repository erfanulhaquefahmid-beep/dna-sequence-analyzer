#include "../../include/linkedlist/RecentSequenceList.hpp"
#include <iostream>

RecentSequenceList::RecentSequenceList(int capacity)
    : maxCapacity(capacity > 0 ? capacity : 5)
{
}

void RecentSequenceList::addRecent(const std::string& sequenceNameOrId)
{
    // If full, remove oldest (deleteLast) and insert at beginning
    if (circularList.size() >= maxCapacity)
    {
        circularList.deleteLast();
    }
    circularList.insertFirst(sequenceNameOrId);
}

void RecentSequenceList::displayRecent() const
{
    if (circularList.isEmpty())
    {
        std::cout << "[RecentSequenceList] No recent sequences viewed.\n";
        return;
    }

    std::cout << "\n========== RECENTLY ACCESSED SEQUENCES (Circular List) ==========\n";
    circularList.display();
    std::cout << "Capacity: " << circularList.size() << "/" << maxCapacity << "\n\n";
}

std::vector<std::string> RecentSequenceList::toVector() const
{
    return circularList.toVector();
}

int RecentSequenceList::size() const
{
    return circularList.size();
}

void RecentSequenceList::clear()
{
    circularList.clear();
}
