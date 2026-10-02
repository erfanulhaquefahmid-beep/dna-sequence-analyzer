#include "../../include/linkedlist/UploadHistory.hpp"
#include <iostream>

void UploadHistory::addUpload(const SequenceRecord& record)
{
    // New uploads are placed at the beginning of the history (most recent first)
    history.insertFirst(record);
}

void UploadHistory::removeUploadById(int id)
{
    bool removed = history.deleteIf([id](const SequenceRecord& r) {
        return r.id == id;
    });

    if (removed)
    {
        std::cout << "[UploadHistory] Sequence Record ID " << id << " successfully removed from history.\n";
    }
    else
    {
        std::cout << "[UploadHistory] Sequence Record ID " << id << " not found in history.\n";
    }
}

void UploadHistory::displayHistory() const
{
    if (history.isEmpty())
    {
        std::cout << "[UploadHistory] No sequence records in history.\n";
        return;
    }

    std::cout << "\n========== UPLOAD HISTORY (Singly Linked List) ==========\n";
    SequenceRecord::printHeader();
    history.display();
    std::cout << "Total Records in History: " << history.size() << "\n\n";
}

SequenceRecord* UploadHistory::findUploadById(int id)
{
    return history.findIf([id](const SequenceRecord& r) {
        return r.id == id;
    });
}

void UploadHistory::reverseHistory()
{
    history.reverse();
    std::cout << "[UploadHistory] History sequence reversed successfully.\n";
}

std::vector<SequenceRecord> UploadHistory::getHistoryVector() const
{
    return history.toVector();
}

int UploadHistory::size() const
{
    return history.size();
}

bool UploadHistory::isEmpty() const
{
    return history.isEmpty();
}

void UploadHistory::clear()
{
    history.clear();
}
