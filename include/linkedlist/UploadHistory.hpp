#ifndef UPLOAD_HISTORY_HPP
#define UPLOAD_HISTORY_HPP

#include "SinglyLinkedList.hpp"
#include "../common/SequenceRecord.hpp"
#include <vector>

class UploadHistory
{
private:
    SinglyLinkedList<SequenceRecord> history;

public:
    UploadHistory() = default;

    void addUpload(const SequenceRecord& record);
    void removeUploadById(int id);
    void displayHistory() const;
    SequenceRecord* findUploadById(int id);
    void reverseHistory();
    std::vector<SequenceRecord> getHistoryVector() const;
    int size() const;
    bool isEmpty() const;
    void clear();
};

#endif // UPLOAD_HISTORY_HPP
