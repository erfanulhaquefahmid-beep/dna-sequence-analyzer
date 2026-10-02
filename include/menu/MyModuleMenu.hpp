#ifndef MY_MODULE_MENU_HPP
#define MY_MODULE_MENU_HPP

#include "../common/SequenceRecord.hpp"
#include "../common/DNAUtils.hpp"
#include "../common/ISequenceIndex.hpp"
#include "../linkedlist/SinglyLinkedList.hpp"
#include "../linkedlist/DoublyLinkedList.hpp"
#include "../linkedlist/CircularLinkedList.hpp"
#include "../linkedlist/UploadHistory.hpp"
#include "../linkedlist/RecentSequenceList.hpp"
#include "../linkedlist/ArrayLinkedList.hpp"
#include "../tree/BinarySearchTree.hpp"
#include "../tree/AVLTree.hpp"
#include "../tree/MinHeap.hpp"
#include "../tree/MaxHeap.hpp"
#include "../tree/FenwickTree.hpp"
#include "../tree/DNARangeIndex.hpp"
#include "../tree/BTreeDemo.hpp"
#include "../map/SequenceMapIndex.hpp"
#include "../map/KmerService.hpp"
#include "../stl/STLUtilities.hpp"

#include <vector>
#include <string>

class MyModuleMenu
{
private:
    UploadHistory uploadHistory;
    RecentSequenceList recentList;
    ArrayLinkedList arrayList;
    BinarySearchTree bst;
    AVLTree avl;
    SequenceMapIndex mapIndex;
    DNARangeIndex rangeIndex;
    std::vector<SequenceRecord> sampleRecords;
    std::string currentDNASequence;

    void initializeSampleData();

    // Submenu handlers
    void handleLinkedListMenu();
    void handleTreeMenu();
    void handleMapMenu();
    void handleSTLMenu();
    void handleFenwickMenu();
    void handleKmerMenu();

    // Detailed action helpers
    void compareArrayVsLinkedListEfficiency();
    void demonstrateBSTDegradationVsAVL();

public:
    MyModuleMenu();

    void runMainMenu();
    bool runAllTests();
};

#endif // MY_MODULE_MENU_HPP
