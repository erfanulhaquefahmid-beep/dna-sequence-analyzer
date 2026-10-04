#include "../../include/common/SequenceRecord.hpp"
#include <iostream>
#include <iomanip>

void SequenceRecord::printHeader()
{
    std::cout << std::left
              << std::setw(6)  << "ID"
              << std::setw(12) << "Owner"
              << std::setw(16) << "Name"
              << std::setw(24) << "File Path"
              << std::setw(10) << "Length"
              << std::setw(12) << "GC (%)"
              << std::setw(14) << "Upload Date"
              << "\n";
    std::cout << std::string(94, '-') << "\n";
}

void SequenceRecord::display() const
{
    std::cout << std::left
              << std::setw(6)  << id
              << std::setw(12) << ownerUsername
              << std::setw(16) << sequenceName
              << std::setw(24) << filePath
              << std::setw(10) << length
              << std::setw(12) << std::fixed << std::setprecision(2) << gcContent
              << std::setw(14) << uploadDate
              << "\n";
}
