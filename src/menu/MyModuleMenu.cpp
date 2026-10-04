#include "../../include/menu/MyModuleMenu.hpp"
#include <iostream>
#include <limits>
#include <iomanip>
#include <chrono>
#include <cassert>

namespace
{
    int getSafeInt(const std::string& prompt)
    {
        int val;
        while (true)
        {
            std::cout << prompt;
            if (std::cin >> val)
            {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return val;
            }
            if (std::cin.eof())
            {
                return 8; // Default exit choice when stream closes
            }
            std::cout << "Invalid input. Please enter an integer.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    double getSafeDouble(const std::string& prompt)
    {
        double val;
        while (true)
        {
            std::cout << prompt;
            if (std::cin >> val)
            {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return val;
            }
            if (std::cin.eof())
            {
                return 0.0;
            }
            std::cout << "Invalid input. Please enter a valid number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    std::string getSafeString(const std::string& prompt)
    {
        std::cout << prompt;
        std::string s;
        if (!std::getline(std::cin, s))
        {
            return "";
        }
        return s;
    }
}

MyModuleMenu::MyModuleMenu()
    : recentList(5)
{
    initializeSampleData();
}

void MyModuleMenu::initializeSampleData()
{
    sampleRecords.clear();

    SequenceRecord r1{101, "user1", "SEQ001", "data/sample1.txt", 18, 50.0, "2026-09-24"};
    SequenceRecord r2{102, "user1", "SEQ002", "data/sample2.txt", 18, 55.5, "2026-09-25"};
    SequenceRecord r3{103, "user1", "SAMPLE_A", "data/sample3.txt", 16, 50.0, "2026-09-26"};

    sampleRecords.push_back(r1);
    sampleRecords.push_back(r2);
    sampleRecords.push_back(r3);

    for (const auto& r : sampleRecords)
    {
        uploadHistory.addUpload(r);
        bst.insert(r);
        avl.insert(r);
        mapIndex.addRecord(r);
        recentList.addRecent(r.sequenceName);
    }

    // Default DNA sequence loaded from sample1.txt
    currentDNASequence = DNAUtils::readDNAFromFile("data/sample1.txt");
    if (currentDNASequence.empty())
    {
        currentDNASequence = "ATGCGTACGTTAGCCATG";
    }
    rangeIndex.build(currentDNASequence);
}

void MyModuleMenu::runMainMenu()
{
    while (true)
    {
        std::cout << "\n======================================================\n";
        std::cout << "    DNA SEQUENCE ANALYZER - MY ASSIGNED MODULE\n";
        std::cout << "  (Tree | Map | STL | Linked List | BIT Range Index)\n";
        std::cout << "======================================================\n";
        std::cout << "1. Linked List Demo\n";
        std::cout << "2. Tree Demo (BST, AVL, Heap, B-Tree)\n";
        std::cout << "3. Map Demo (std::map, unordered_map, multimap)\n";
        std::cout << "4. STL Demo (vector, algorithms, lambdas, sort)\n";
        std::cout << "5. Fenwick Tree DNA Range Demo\n";
        std::cout << "6. K-mer Count & Analysis Demo\n";
        std::cout << "7. Run All Unit & Integration Tests\n";
        std::cout << "8. Return to Main Project / Exit\n";
        std::cout << "======================================================\n";

        int choice = getSafeInt("Enter choice [1-8]: ");

        switch (choice)
        {
            case 1: handleLinkedListMenu(); break;
            case 2: handleTreeMenu(); break;
            case 3: handleMapMenu(); break;
            case 4: handleSTLMenu(); break;
            case 5: handleFenwickMenu(); break;
            case 6: handleKmerMenu(); break;
            case 7: runAllTests(); break;
            case 8:
                std::cout << "\nReturning to Main Project... Goodbye!\n";
                return;
            default:
                std::cout << "Invalid choice. Please select 1-8.\n";
                break;
        }
    }
}

void MyModuleMenu::handleLinkedListMenu()
{
    while (true)
    {
        std::cout << "\n---------------- LINKED LIST DEMO MENU ----------------\n";
        std::cout << "1. Insert record at beginning\n";
        std::cout << "2. Insert record at end\n";
        std::cout << "3. Insert record at position\n";
        std::cout << "4. Delete from beginning\n";
        std::cout << "5. Delete from end\n";
        std::cout << "6. Delete from position\n";
        std::cout << "7. Search record by ID\n";
        std::cout << "8. Reverse list\n";
        std::cout << "9. Display upload history (Singly Linked List)\n";
        std::cout << "10. Compare array vs linked list efficiency\n";
        std::cout << "11. Display recent sequences (Circular Linked List)\n";
        std::cout << "12. Array-based cursor linked list demo\n";
        std::cout << "0. Back to Main Menu\n";
        std::cout << "-------------------------------------------------------\n";

        int choice = getSafeInt("Select option [0-12]: ");
        if (choice == 0) break;

        switch (choice)
        {
            case 1:
            {
                SequenceRecord rec;
                rec.id = getSafeInt("Enter record ID: ");
                rec.sequenceName = getSafeString("Enter sequence name: ");
                rec.ownerUsername = getSafeString("Enter owner username: ");
                rec.filePath = getSafeString("Enter file path: ");
                rec.length = getSafeInt("Enter length: ");
                rec.gcContent = getSafeDouble("Enter GC content (%): ");
                rec.uploadDate = getSafeString("Enter upload date (YYYY-MM-DD): ");

                uploadHistory.addUpload(rec);
                recentList.addRecent(rec.sequenceName);
                std::cout << "[SUCCESS] Record inserted at beginning.\n";
                break;
            }
            case 2:
            {
                SequenceRecord rec;
                rec.id = getSafeInt("Enter record ID: ");
                rec.sequenceName = getSafeString("Enter sequence name: ");
                rec.ownerUsername = getSafeString("Enter owner username: ");
                rec.filePath = getSafeString("Enter file path: ");
                rec.length = getSafeInt("Enter length: ");
                rec.gcContent = getSafeDouble("Enter GC content (%): ");
                rec.uploadDate = getSafeString("Enter upload date (YYYY-MM-DD): ");

                // Demonstrate insertLast via a temporary SinglyLinkedList adapter or direct vector conversion
                auto vec = uploadHistory.getHistoryVector();
                vec.push_back(rec);
                uploadHistory.clear();
                for (auto it = vec.rbegin(); it != vec.rend(); ++it)
                {
                    uploadHistory.addUpload(*it);
                }
                std::cout << "[SUCCESS] Record inserted at end.\n";
                break;
            }
            case 3:
            {
                int pos = getSafeInt("Enter 0-based position to insert at: ");
                SequenceRecord rec;
                rec.id = getSafeInt("Enter record ID: ");
                rec.sequenceName = getSafeString("Enter sequence name: ");
                rec.ownerUsername = getSafeString("Enter owner username: ");
                rec.filePath = getSafeString("Enter file path: ");
                rec.length = getSafeInt("Enter length: ");
                rec.gcContent = getSafeDouble("Enter GC content (%): ");
                rec.uploadDate = getSafeString("Enter upload date (YYYY-MM-DD): ");

                auto vec = uploadHistory.getHistoryVector();
                if (pos < 0) pos = 0;
                if (pos > static_cast<int>(vec.size())) pos = static_cast<int>(vec.size());
                vec.insert(vec.begin() + pos, rec);
                uploadHistory.clear();
                for (auto it = vec.rbegin(); it != vec.rend(); ++it)
                {
                    uploadHistory.addUpload(*it);
                }
                std::cout << "[SUCCESS] Record inserted at position " << pos << ".\n";
                break;
            }
            case 4:
            {
                if (uploadHistory.isEmpty())
                {
                    std::cout << "[ERROR] List is empty.\n";
                }
                else
                {
                    auto vec = uploadHistory.getHistoryVector();
                    int delId = vec.front().id;
                    uploadHistory.removeUploadById(delId);
                    std::cout << "[SUCCESS] Deleted first record (ID: " << delId << ").\n";
                }
                break;
            }
            case 5:
            {
                if (uploadHistory.isEmpty())
                {
                    std::cout << "[ERROR] List is empty.\n";
                }
                else
                {
                    auto vec = uploadHistory.getHistoryVector();
                    int delId = vec.back().id;
                    uploadHistory.removeUploadById(delId);
                    std::cout << "[SUCCESS] Deleted last record (ID: " << delId << ").\n";
                }
                break;
            }
            case 6:
            {
                int pos = getSafeInt("Enter 0-based position to delete: ");
                auto vec = uploadHistory.getHistoryVector();
                if (pos >= 0 && pos < static_cast<int>(vec.size()))
                {
                    int delId = vec[pos].id;
                    uploadHistory.removeUploadById(delId);
                    std::cout << "[SUCCESS] Record at position " << pos << " (ID: " << delId << ") deleted.\n";
                }
                else
                {
                    std::cout << "[ERROR] Invalid position.\n";
                }
                break;
            }
            case 7:
            {
                int searchId = getSafeInt("Enter record ID to search: ");
                SequenceRecord* found = uploadHistory.findUploadById(searchId);
                if (found)
                {
                    std::cout << "\n[FOUND IN LINKED LIST]:\n";
                    SequenceRecord::printHeader();
                    found->display();
                }
                else
                {
                    std::cout << "[NOT FOUND] Record with ID " << searchId << " does not exist.\n";
                }
                break;
            }
            case 8:
                uploadHistory.reverseHistory();
                break;
            case 9:
                uploadHistory.displayHistory();
                break;
            case 10:
                compareArrayVsLinkedListEfficiency();
                break;
            case 11:
                recentList.displayRecent();
                break;
            case 12:
            {
                std::cout << "\nDemonstrating Array-based Cursor Linked List:\n";
                ArrayLinkedList testArr;
                testArr.insertFirst("SEQ_ALPHA");
                testArr.insertLast("SEQ_BETA");
                testArr.insertAtPosition(1, "SEQ_GAMMA");
                testArr.display();
                std::cout << "Deleting from position 1...\n";
                testArr.deleteAtPosition(1);
                testArr.display();
                break;
            }
            default:
                std::cout << "Invalid choice.\n";
                break;
        }
    }
}

void MyModuleMenu::compareArrayVsLinkedListEfficiency()
{
    std::cout << "\n=========================================================================\n";
    std::cout << "       ARRAY VS LINKED LIST PERFORMANCE & ARCHITECTURE COMPARISON\n";
    std::cout << "=========================================================================\n";
    std::cout << "Operation                 | Contiguous Array (Vector) | Linked List (Dynamic Nodes)\n";
    std::cout << "-------------------------------------------------------------------------\n";
    std::cout << "Random Access (index i)   | O(1) [Direct address arithmetic]| O(N) [Must traverse pointers]\n";
    std::cout << "Insert at Beginning       | O(N) [Must shift all elements]  | O(1) [Pointer rewire only]\n";
    std::cout << "Insert at End             | O(1) amortized [Resize penalty] | O(1) [With tail pointer]\n";
    std::cout << "Insert at Middle          | O(N) [Shift elements]           | O(N) [Traverse] + O(1) [Rewire]\n";
    std::cout << "Delete from Beginning     | O(N) [Shift elements]           | O(1) [Pointer rewire & free]\n";
    std::cout << "Memory Overhead           | Minimal (Data only, spare cap)  | Extra pointer(s) per node\n";
    std::cout << "Cache Locality            | Excellent (Sequential memory)   | Poor (Scattered heap nodes)\n";
    std::cout << "Storage Reallocation      | May trigger full array copy     | Never requires reallocation\n";
    std::cout << "=========================================================================\n";
    std::cout << "Educational Takeaway:\n";
    std::cout << "- Use Linked List when frequent insertions/deletions at the front occur\n";
    std::cout << "  (e.g., Undo history, Upload logs, queue simulation).\n";
    std::cout << "- Use Array/Vector when frequent random indexing or cache-heavy scanning\n";
    std::cout << "  is required (e.g., DNA base lookups, mathematical vector operations).\n\n";
}

void MyModuleMenu::handleTreeMenu()
{
    while (true)
    {
        std::cout << "\n-------------------- TREE DEMO MENU --------------------\n";
        std::cout << "1. Insert record into BST\n";
        std::cout << "2. Delete record from BST\n";
        std::cout << "3. Search record in BST by ID\n";
        std::cout << "4. BST traversals (Inorder, Preorder, Postorder)\n";
        std::cout << "5. Insert record into AVL\n";
        std::cout << "6. Delete record from AVL (Triggers auto-rebalance)\n";
        std::cout << "7. Show AVL height & visual tree structure\n";
        std::cout << "8. Range search by sequence length [AVL]\n";
        std::cout << "9. Range search by GC content [AVL]\n";
        std::cout << "10. Heap top-K frequent K-mers demo\n";
        std::cout << "11. Demonstrate BST Skewed Degradation vs AVL Balance\n";
        std::cout << "12. Multi-way Search Tree (B-Tree / 2-3 Tree) Demo\n";
        std::cout << "0. Back to Main Menu\n";
        std::cout << "--------------------------------------------------------\n";

        int choice = getSafeInt("Select option [0-12]: ");
        if (choice == 0) break;

        switch (choice)
        {
            case 1:
            {
                SequenceRecord rec;
                rec.id = getSafeInt("Enter record ID: ");
                rec.sequenceName = getSafeString("Enter sequence name: ");
                rec.ownerUsername = getSafeString("Enter owner username: ");
                rec.filePath = getSafeString("Enter file path: ");
                rec.length = getSafeInt("Enter length: ");
                rec.gcContent = getSafeDouble("Enter GC content (%): ");
                rec.uploadDate = getSafeString("Enter upload date: ");

                bst.insert(rec);
                std::cout << "[SUCCESS] Record inserted into BST.\n";
                break;
            }
            case 2:
            {
                int id = getSafeInt("Enter record ID to delete from BST: ");
                if (bst.removeById(id))
                {
                    std::cout << "[SUCCESS] Record ID " << id << " deleted from BST.\n";
                }
                else
                {
                    std::cout << "[ERROR] Record ID " << id << " not found in BST.\n";
                }
                break;
            }
            case 3:
            {
                int id = getSafeInt("Enter record ID to search: ");
                SequenceRecord* r = bst.searchById(id);
                if (r)
                {
                    std::cout << "\n[BST SEARCH HIT]:\n";
                    SequenceRecord::printHeader();
                    r->display();
                }
                else
                {
                    std::cout << "[BST SEARCH MISS] ID " << id << " not found.\n";
                }
                break;
            }
            case 4:
                bst.inorderTraversal();
                bst.preorderTraversal();
                bst.postorderTraversal();
                break;
            case 5:
            {
                SequenceRecord rec;
                rec.id = getSafeInt("Enter record ID: ");
                rec.sequenceName = getSafeString("Enter sequence name: ");
                rec.ownerUsername = getSafeString("Enter owner username: ");
                rec.filePath = getSafeString("Enter file path: ");
                rec.length = getSafeInt("Enter length: ");
                rec.gcContent = getSafeDouble("Enter GC content (%): ");
                rec.uploadDate = getSafeString("Enter upload date: ");

                avl.insert(rec);
                std::cout << "[SUCCESS] Record inserted into AVL. Current AVL Height: " << avl.height() << "\n";
                break;
            }
            case 6:
            {
                int id = getSafeInt("Enter record ID to delete from AVL: ");
                if (avl.removeById(id))
                {
                    std::cout << "[SUCCESS] Record ID " << id << " deleted from AVL with auto-rebalancing.\n";
                }
                else
                {
                    std::cout << "[ERROR] Record ID " << id << " not found in AVL.\n";
                }
                break;
            }
            case 7:
                std::cout << "\nAVL Tree Height: " << avl.height() << ", Total Nodes: " << avl.size() << "\n";
                avl.printTreeStructure();
                break;
            case 8:
            {
                int minL = getSafeInt("Enter minimum length: ");
                int maxL = getSafeInt("Enter maximum length: ");
                auto res = avl.rangeSearchByLength(minL, maxL);
                std::cout << "\nRange Search [Length " << minL << ".." << maxL << "] matched " << res.size() << " records:\n";
                STLUtilities::printRecords(res);
                break;
            }
            case 9:
            {
                double minGC = getSafeDouble("Enter minimum GC (%): ");
                double maxGC = getSafeDouble("Enter maximum GC (%): ");
                auto res = avl.rangeSearchByGC(minGC, maxGC);
                std::cout << "\nRange Search [GC " << minGC << "%.." << maxGC << "%] matched " << res.size() << " records:\n";
                STLUtilities::printRecords(res);
                break;
            }
            case 10:
            {
                int k = getSafeInt("Enter k-mer size k (e.g. 3): ");
                int topK = getSafeInt("Enter top-K to retrieve (e.g. 5): ");
                auto counts = KmerService::buildKmerCount(currentDNASequence, k);
                auto topResults = KmerService::topKmers(counts, topK);

                std::cout << "\n--- Top " << topK << " Frequent " << k << "-mers using Min/Max-Heap ---\n";
                std::cout << "Rank | K-mer  | Frequency\n";
                std::cout << "------------------------\n";
                int rank = 1;
                for (const auto& item : topResults)
                {
                    std::cout << std::left << std::setfill(' ')
                              << std::setw(5) << rank++
                              << "| " << std::setw(6) << item.first
                              << "| " << item.second << "\n";
                }
                std::cout << "------------------------\n";
                break;
            }
            case 11:
                demonstrateBSTDegradationVsAVL();
                break;
            case 12:
            {
                std::cout << "\nDemonstrating B-Tree / 2-3 Tree (Degree t=2):\n";
                BTreeDemo btree(2);
                int sampleKeys[] = {10, 20, 5, 6, 12, 30, 7, 17};
                for (int key : sampleKeys)
                {
                    std::cout << "Inserting " << key << " into B-Tree...\n";
                    btree.insert(key);
                }
                btree.display();
                break;
            }
            default:
                std::cout << "Invalid choice.\n";
                break;
        }
    }
}

void MyModuleMenu::demonstrateBSTDegradationVsAVL()
{
    std::cout << "\n=========================================================================\n";
    std::cout << "        DEMONSTRATION: BST DEGRADATION VS AVL SELF-BALANCING\n";
    std::cout << "=========================================================================\n";
    std::cout << "Inserting 10 strictly ascending IDs: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]\n";

    BinarySearchTree testBST;
    AVLTree testAVL;

    for (int i = 1; i <= 10; ++i)
    {
        SequenceRecord r{i, "user1", "SEQ_" + std::to_string(i), "path", i * 10, 50.0, "2026-09-26"};
        testBST.insert(r);
        testAVL.insert(r);
    }

    std::cout << "\nResults:\n";
    std::cout << "  - Binary Search Tree (BST) Height : " << testBST.height() << "  (Degenerated to O(N) linked list!)\n";
    std::cout << "  - AVL Balanced Tree Height       : " << testAVL.height() << "  (Maintains strictly O(log N) balance!)\n";
    std::cout << "\nVisual structure of AVL Tree:\n";
    testAVL.printTreeStructure();
    std::cout << "=========================================================================\n\n";
}

void MyModuleMenu::handleMapMenu()
{
    while (true)
    {
        std::cout << "\n--------------------- MAP DEMO MENU ---------------------\n";
        std::cout << "1. Add record to map index\n";
        std::cout << "2. Find record by ID (O(1) unordered_map)\n";
        std::cout << "3. Find record by exact sequence name (std::map)\n";
        std::cout << "4. Find records by sequence name prefix (std::map lower_bound)\n";
        std::cout << "5. Find records by GC content range (std::multimap)\n";
        std::cout << "6. Find records by date range (std::multimap)\n";
        std::cout << "7. Display all map indexes\n";
        std::cout << "8. K-mer frequency analysis using unordered_map\n";
        std::cout << "9. Show unordered_map internal hash table stats\n";
        std::cout << "10. Compare std::map vs std::unordered_map\n";
        std::cout << "0. Back to Main Menu\n";
        std::cout << "---------------------------------------------------------\n";

        int choice = getSafeInt("Select option [0-10]: ");
        if (choice == 0) break;

        switch (choice)
        {
            case 1:
            {
                SequenceRecord rec;
                rec.id = getSafeInt("Enter record ID: ");
                rec.sequenceName = getSafeString("Enter sequence name: ");
                rec.ownerUsername = getSafeString("Enter owner username: ");
                rec.filePath = getSafeString("Enter file path: ");
                rec.length = getSafeInt("Enter length: ");
                rec.gcContent = getSafeDouble("Enter GC content (%): ");
                rec.uploadDate = getSafeString("Enter upload date: ");

                mapIndex.addRecord(rec);
                std::cout << "[SUCCESS] Record added to map index.\n";
                break;
            }
            case 2:
            {
                int id = getSafeInt("Enter ID to search in unordered_map: ");
                SequenceRecord* r = mapIndex.findById(id);
                if (r)
                {
                    std::cout << "\n[HASH TABLE HIT (O(1))]:\n";
                    SequenceRecord::printHeader();
                    r->display();
                }
                else
                {
                    std::cout << "[MISS] ID " << id << " not found.\n";
                }
                break;
            }
            case 3:
            {
                std::string name = getSafeString("Enter exact sequence name: ");
                auto ids = mapIndex.findIdsByName(name);
                std::cout << "Found " << ids.size() << " records matching name \"" << name << "\":\n";
                for (int id : ids)
                {
                    SequenceRecord* r = mapIndex.findById(id);
                    if (r) r->display();
                }
                break;
            }
            case 4:
            {
                std::string prefix = getSafeString("Enter sequence name prefix (e.g. SEQ): ");
                auto ids = mapIndex.findIdsByNamePrefix(prefix);
                std::cout << "Found " << ids.size() << " records with prefix \"" << prefix << "\":\n";
                for (int id : ids)
                {
                    SequenceRecord* r = mapIndex.findById(id);
                    if (r) r->display();
                }
                break;
            }
            case 5:
            {
                double minGC = getSafeDouble("Enter min GC (%): ");
                double maxGC = getSafeDouble("Enter max GC (%): ");
                auto ids = mapIndex.findByGCRange(minGC, maxGC);
                std::cout << "Found " << ids.size() << " records in GC range [" << minGC << "%.." << maxGC << "%]:\n";
                for (int id : ids)
                {
                    SequenceRecord* r = mapIndex.findById(id);
                    if (r) r->display();
                }
                break;
            }
            case 6:
            {
                std::string startDate = getSafeString("Enter start date (YYYY-MM-DD): ");
                std::string endDate = getSafeString("Enter end date (YYYY-MM-DD): ");
                auto ids = mapIndex.findByDateRange(startDate, endDate);
                std::cout << "Found " << ids.size() << " records in date range [" << startDate << ".." << endDate << "]:\n";
                for (int id : ids)
                {
                    SequenceRecord* r = mapIndex.findById(id);
                    if (r) r->display();
                }
                break;
            }
            case 7:
                mapIndex.displayAllIndexes();
                break;
            case 8:
            {
                int k = getSafeInt("Enter k-mer size: ");
                auto counts = countKmers(currentDNASequence, k);
                std::cout << "\nDistinct " << k << "-mers count: " << counts.size() << "\n";
                std::cout << "K-mer frequencies:\n";
                for (const auto& pair : counts)
                {
                    std::cout << "  " << pair.first << " : " << pair.second << "\n";
                }
                break;
            }
            case 9:
                mapIndex.printHashTableStats();
                break;
            case 10:
                mapIndex.compareMapVsUnorderedMap();
                break;
            default:
                std::cout << "Invalid choice.\n";
                break;
        }
    }
}

void MyModuleMenu::handleSTLMenu()
{
    while (true)
    {
        std::cout << "\n--------------------- STL DEMO MENU ---------------------\n";
        std::cout << "1. Sort records by name (std::sort + lambda)\n";
        std::cout << "2. Sort records by length ascending\n";
        std::cout << "3. Sort records by GC content\n";
        std::cout << "4. Sort records by date\n";
        std::cout << "5. Filter records by length range (std::copy_if)\n";
        std::cout << "6. Filter records by GC range\n";
        std::cout << "7. Search records by keyword (std::find_if)\n";
        std::cout << "8. Reverse DNA string (std::reverse)\n";
        std::cout << "9. Count records with GC > 50% (std::count_if)\n";
        std::cout << "10. Display all records in vector\n";
        std::cout << "0. Back to Main Menu\n";
        std::cout << "---------------------------------------------------------\n";

        int choice = getSafeInt("Select option [0-10]: ");
        if (choice == 0) break;

        switch (choice)
        {
            case 1:
                STLUtilities::sortBySequenceName(sampleRecords);
                std::cout << "[SUCCESS] Sorted by sequence name.\n";
                STLUtilities::printRecords(sampleRecords);
                break;
            case 2:
                STLUtilities::sortByLengthAscending(sampleRecords);
                std::cout << "[SUCCESS] Sorted by length ascending.\n";
                STLUtilities::printRecords(sampleRecords);
                break;
            case 3:
                STLUtilities::sortByGCContent(sampleRecords);
                std::cout << "[SUCCESS] Sorted by GC content.\n";
                STLUtilities::printRecords(sampleRecords);
                break;
            case 4:
                STLUtilities::sortByUploadDate(sampleRecords);
                std::cout << "[SUCCESS] Sorted by upload date.\n";
                STLUtilities::printRecords(sampleRecords);
                break;
            case 5:
            {
                int minL = getSafeInt("Enter min length: ");
                int maxL = getSafeInt("Enter max length: ");
                auto filtered = STLUtilities::filterByLength(sampleRecords, minL, maxL);
                STLUtilities::printRecords(filtered);
                break;
            }
            case 6:
            {
                double minGC = getSafeDouble("Enter min GC (%): ");
                double maxGC = getSafeDouble("Enter max GC (%): ");
                auto filtered = STLUtilities::filterByGC(sampleRecords, minGC, maxGC);
                STLUtilities::printRecords(filtered);
                break;
            }
            case 7:
            {
                std::string kw = getSafeString("Enter keyword to search in sequence name: ");
                auto found = STLUtilities::searchByNameContains(sampleRecords, kw);
                STLUtilities::printRecords(found);
                break;
            }
            case 8:
            {
                std::string rev = STLUtilities::reverseString(currentDNASequence);
                std::cout << "Original DNA : " << currentDNASequence << "\n";
                std::cout << "Reversed DNA : " << rev << "\n";
                break;
            }
            case 9:
            {
                int count = STLUtilities::countIfGCGreaterThan(sampleRecords, 50.0);
                std::cout << "Records with GC content > 50.0%: " << count << " / " << sampleRecords.size() << "\n";
                break;
            }
            case 10:
                STLUtilities::printRecords(sampleRecords);
                break;
            default:
                std::cout << "Invalid choice.\n";
                break;
        }
    }
}

void MyModuleMenu::handleFenwickMenu()
{
    while (true)
    {
        std::cout << "\n------------- FENWICK TREE DNA RANGE DEMO -------------\n";
        std::cout << "Current Loaded DNA: " << currentDNASequence << "\n";
        std::cout << "Length: " << rangeIndex.getLength() << " bp\n";
        std::cout << "1. Load DNA sequence from file / text\n";
        std::cout << "2. Rebuild Fenwick indexes\n";
        std::cout << "3. Count Adenine (A) in range [left..right]\n";
        std::cout << "4. Count Cytosine (C) in range [left..right]\n";
        std::cout << "5. Count Guanine (G) in range [left..right]\n";
        std::cout << "6. Count Thymine (T) in range [left..right]\n";
        std::cout << "7. Compute GC content (%) in range [left..right]\n";
        std::cout << "8. Dynamic point update nucleotide at position\n";
        std::cout << "0. Back to Main Menu\n";
        std::cout << "---------------------------------------------------------\n";

        int choice = getSafeInt("Select option [0-8]: ");
        if (choice == 0) break;

        switch (choice)
        {
            case 1:
            {
                std::cout << "1. Load from file (e.g. data/sample2.txt)\n";
                std::cout << "2. Enter manual DNA string\n";
                int sub = getSafeInt("Choice: ");
                if (sub == 1)
                {
                    std::string path = getSafeString("Enter file path: ");
                    std::string seq = DNAUtils::readDNAFromFile(path);
                    if (!seq.empty())
                    {
                        currentDNASequence = seq;
                        rangeIndex.build(currentDNASequence);
                        std::cout << "[SUCCESS] Loaded " << currentDNASequence.length() << " bp from " << path << ".\n";
                    }
                }
                else
                {
                    std::string raw = getSafeString("Enter DNA string: ");
                    currentDNASequence = STLUtilities::transformToUppercase(raw);
                    rangeIndex.build(currentDNASequence);
                    std::cout << "[SUCCESS] Built Fenwick indexes for sequence.\n";
                }
                break;
            }
            case 2:
                rangeIndex.build(currentDNASequence);
                std::cout << "[SUCCESS] Rebuilt 4 Fenwick trees for sequence.\n";
                break;
            case 3:
            {
                int l = getSafeInt("Enter left position (1-based): ");
                int r = getSafeInt("Enter right position (1-based): ");
                int cnt = rangeIndex.countA(l, r);
                std::cout << "A count in [" << l << ".." << r << "] = " << cnt << "\n";
                break;
            }
            case 4:
            {
                int l = getSafeInt("Enter left position (1-based): ");
                int r = getSafeInt("Enter right position (1-based): ");
                int cnt = rangeIndex.countC(l, r);
                std::cout << "C count in [" << l << ".." << r << "] = " << cnt << "\n";
                break;
            }
            case 5:
            {
                int l = getSafeInt("Enter left position (1-based): ");
                int r = getSafeInt("Enter right position (1-based): ");
                int cnt = rangeIndex.countG(l, r);
                std::cout << "G count in [" << l << ".." << r << "] = " << cnt << "\n";
                break;
            }
            case 6:
            {
                int l = getSafeInt("Enter left position (1-based): ");
                int r = getSafeInt("Enter right position (1-based): ");
                int cnt = rangeIndex.countT(l, r);
                std::cout << "T count in [" << l << ".." << r << "] = " << cnt << "\n";
                break;
            }
            case 7:
            {
                int l = getSafeInt("Enter left position (1-based): ");
                int r = getSafeInt("Enter right position (1-based): ");
                double gc = rangeIndex.gcContent(l, r);
                std::cout << "GC Content in [" << l << ".." << r << "] = "
                          << std::fixed << std::setprecision(2) << gc << "%\n";
                break;
            }
            case 8:
            {
                int pos = getSafeInt("Enter 1-based position to mutate: ");
                std::string newB = getSafeString("Enter new base (A, C, G, T): ");
                if (!newB.empty())
                {
                    rangeIndex.updateBase(pos, newB[0]);
                    currentDNASequence = rangeIndex.getSequence();
                    std::cout << "[SUCCESS] Mutated position " << pos << " to '" << newB[0] << "'.\n";
                    std::cout << "Updated sequence: " << currentDNASequence << "\n";
                }
                break;
            }
            default:
                std::cout << "Invalid choice.\n";
                break;
        }
    }
}

void MyModuleMenu::handleKmerMenu()
{
    std::cout << "\n----------------- K-MER FREQUENCY ANALYSIS -----------------\n";
    std::cout << "Current DNA: " << currentDNASequence << " (Length: " << currentDNASequence.length() << " bp)\n";
    int k = getSafeInt("Enter k (k-mer length, e.g. 3): ");
    int topN = getSafeInt("Enter top-N most frequent to display: ");

    auto counts = KmerService::buildKmerCount(currentDNASequence, k);
    auto topList = KmerService::topKmers(counts, topN);

    std::cout << "\nTotal unique " << k << "-mers: " << counts.size() << "\n";
    std::cout << "Rank | K-mer  | Count\n";
    std::cout << "--------------------\n";
    int rank = 1;
    for (const auto& item : topList)
    {
        std::cout << std::left << std::setw(5) << rank++
                  << "| " << std::setw(6) << item.first
                  << "| " << item.second << "\n";
    }

    std::cout << "\nDe Bruijn Graph (k-1)-mer directed edges for Graph Module integration:\n";
    auto edges = KmerService::generateDeBruijnEdges(currentDNASequence, k);
    int shown = 0;
    for (const auto& edge : edges)
    {
        std::cout << "  \"" << edge.first << "\" -> \"" << edge.second << "\"\n";
        if (++shown >= 10 && edges.size() > 10)
        {
            std::cout << "  ... (" << edges.size() - 10 << " more edges)\n";
            break;
        }
    }
    std::cout << "------------------------------------------------------------\n";
}

bool MyModuleMenu::runAllTests()
{
    std::cout << "\n======================================================\n";
    std::cout << "    RUNNING COMPREHENSIVE AUTOMATED TEST SUITE\n";
    std::cout << "======================================================\n";
    int passed = 0;
    int total = 0;

    auto testAssert = [&](const std::string& name, bool condition) {
        total++;
        if (condition)
        {
            std::cout << "  [PASS] " << name << "\n";
            passed++;
        }
        else
        {
            std::cout << "  [FAIL] " << name << "\n";
        }
    };

    // 1. SinglyLinkedList Exhaustive Tests
    {
        SinglyLinkedList<int> sll;
        testAssert("SLL: Empty initially", sll.isEmpty());
        sll.insertFirst(10);
        testAssert("SLL: Insert first when empty", sll.size() == 1 && sll.search(10));
        sll.insertLast(30);
        testAssert("SLL: Insert last", sll.size() == 2 && sll.search(30));
        sll.insertAtPosition(1, 20);
        testAssert("SLL: Insert at middle position 1", sll.size() == 3);

        // Separate empty list to test insertLast when empty
        SinglyLinkedList<int> emptyList;
        emptyList.insertLast(999);
        testAssert("SLL: Insert last when empty", emptyList.size() == 1 && emptyList.search(999));
        emptyList.insertAtPosition(0, 888);
        testAssert("SLL: Insert at position 0", emptyList.toVector()[0] == 888);
        testAssert("SLL: Delete invalid negative position fails", !emptyList.deleteAtPosition(-1));
        testAssert("SLL: Delete invalid out-of-bounds position fails", !emptyList.deleteAtPosition(100));

        auto vec = sll.toVector();
        testAssert("SLL: Vector matches [10, 20, 30]", vec.size() == 3 && vec[0] == 10 && vec[1] == 20 && vec[2] == 30);
        sll.reverse();
        vec = sll.toVector();
        testAssert("SLL: Reversal matches [30, 20, 10]", vec[0] == 30 && vec[1] == 20 && vec[2] == 10);
        testAssert("SLL: Delete at middle position", sll.deleteAtPosition(1) && sll.size() == 2);
        testAssert("SLL: Delete first", sll.deleteFirst() && sll.size() == 1);
        testAssert("SLL: Delete last", sll.deleteLast() && sll.isEmpty());
        testAssert("SLL: Delete from empty returns false", !sll.deleteFirst());
    }

    // 2. DoublyLinkedList Exhaustive Tests
    {
        DoublyLinkedList<int> dll;
        dll.insertFirst(2);
        dll.insertFirst(1);
        dll.insertLast(3);
        testAssert("DLL: Insertions size is 3", dll.size() == 3);
        auto vec = dll.toVector();
        testAssert("DLL: Order [1, 2, 3]", vec[0] == 1 && vec[1] == 2 && vec[2] == 3);
        dll.reverse();
        vec = dll.toVector();
        testAssert("DLL: Reversal [3, 2, 1]", vec[0] == 3 && vec[1] == 2 && vec[2] == 1);
        dll.deleteAtPosition(1);
        testAssert("DLL: Delete middle size is 2", dll.size() == 2 && dll.toVector()[1] == 1);
        dll.deleteFirst();
        dll.deleteLast();
        testAssert("DLL: Delete until empty", dll.isEmpty());
        testAssert("DLL: Delete empty returns false", !dll.deleteFirst());
    }

    // 3. CircularLinkedList & RecentSequenceList Tests
    {
        CircularLinkedList<std::string> cll;
        cll.insertFirst("A");
        cll.insertLast("B");
        cll.insertLast("C");
        testAssert("CLL: Size is 3", cll.size() == 3);
        auto vec = cll.toVector();
        testAssert("CLL: Circular elements [A, B, C]", vec[0] == "A" && vec[1] == "B" && vec[2] == "C");
        cll.deleteFirst();
        testAssert("CLL: Delete first gives B as head", cll.toVector()[0] == "B");

        RecentSequenceList rsl(3);
        rsl.addRecent("SEQ1");
        rsl.addRecent("SEQ2");
        rsl.addRecent("SEQ3");
        rsl.addRecent("SEQ4"); // Should evict oldest to respect capacity 3
        testAssert("RecentList: Capacity capping to 3", rsl.size() == 3);
    }

    // 4. ArrayLinkedList (Cursor-based) Tests
    {
        ArrayLinkedList all;
        testAssert("ALL: Empty initially", all.isEmpty());
        all.insertFirst("NODE1");
        all.insertLast("NODE2");
        all.insertAtPosition(1, "NODE_MID");
        testAssert("ALL: Size is 3", all.size() == 3);
        testAssert("ALL: Delete at position 1", all.deleteAtPosition(1));
        testAssert("ALL: Delete first works", all.deleteFirst() && all.size() == 1);
    }

    // 5. BinarySearchTree Exhaustive Tests
    {
        BinarySearchTree myBst;
        SequenceRecord rec1{50, "u", "S50", "p", 10, 50.0, "2026"};
        SequenceRecord rec2{20, "u", "S20", "p", 10, 50.0, "2026"};
        SequenceRecord rec3{80, "u", "S80", "p", 10, 50.0, "2026"};
        SequenceRecord rec4{10, "u", "S10", "p", 10, 50.0, "2026"};
        SequenceRecord rec5{30, "u", "S30", "p", 10, 50.0, "2026"};
        SequenceRecord rec6{90, "u", "S90", "p", 10, 50.0, "2026"};

        myBst.insert(rec1);
        myBst.insert(rec2);
        myBst.insert(rec3);
        myBst.insert(rec4);
        myBst.insert(rec5);
        myBst.insert(rec6); // 80 now has only one right child (90)

        // Test sorted inorder traversal
        auto inorder = myBst.toInorderVector();
        bool isSorted = true;
        for (size_t i = 1; i < inorder.size(); ++i)
        {
            if (inorder[i].id < inorder[i - 1].id) isSorted = false;
        }
        testAssert("BST: Inorder traversal is strictly sorted", isSorted && inorder.size() == 6);

        testAssert("BST: Search existing ID 20", myBst.searchById(20) != nullptr);
        testAssert("BST: Search missing ID 999", myBst.searchById(999) == nullptr);
        testAssert("BST: Delete leaf node (10)", myBst.removeById(10) && myBst.searchById(10) == nullptr);
        testAssert("BST: Delete node with one child (80)", myBst.removeById(80) && myBst.searchById(80) == nullptr && myBst.searchById(90) != nullptr);
        testAssert("BST: Delete node with two children (50)", myBst.removeById(50) && myBst.searchById(50) == nullptr);

        // Test BST height degradation with sorted insertion
        BinarySearchTree sortedBst;
        for (int i = 1; i <= 5; ++i)
        {
            sortedBst.insert({i, "u", "S", "p", i * 10, 50.0, "2026"});
        }
        testAssert("BST: Skewed insertion degenerates to height N (5)", sortedBst.height() == 5);
    }

    // 6. AVLTree Exhaustive Tests
    {
        AVLTree myAvl;
        // Insert strictly ascending to test LL/RR rotations
        for (int i = 1; i <= 7; ++i)
        {
            SequenceRecord r{i, "u", "S" + std::to_string(i), "p", i * 10, i * 10.0, "2026"};
            myAvl.insert(r);
        }
        testAssert("AVL: Self-balancing maintains height <= 4 for 7 nodes", myAvl.height() <= 4);
        testAssert("AVL: Search ID 4", myAvl.searchById(4) != nullptr);

        auto lenRange = myAvl.rangeSearchByLength(20, 50);
        testAssert("AVL: Range search by length returns 4 items", lenRange.size() == 4);

        auto gcRange = myAvl.rangeSearchByGC(20.0, 50.0);
        testAssert("AVL: Range search by GC returns 4 items", gcRange.size() == 4);

        // Delete node causing rotation and verify rebalancing
        testAssert("AVL: Remove ID 4", myAvl.removeById(4) && myAvl.searchById(4) == nullptr);
        testAssert("AVL: Height remains balanced after deletion", myAvl.height() <= 4);

        auto avlInorder = myAvl.toInorderVector();
        bool avlSorted = true;
        for (size_t i = 1; i < avlInorder.size(); ++i)
        {
            if (avlInorder[i].id < avlInorder[i - 1].id) avlSorted = false;
        }
        testAssert("AVL: Inorder traversal remains strictly sorted", avlSorted && avlInorder.size() == 6);
    }

    // 7. MinHeap and MaxHeap Tests
    {
        MinHeap minH;
        minH.push({"A", 5});
        minH.push({"B", 2});
        minH.push({"C", 8});
        testAssert("MinHeap: Top is lowest frequency (2)", minH.top().second == 2);
        minH.pop();
        testAssert("MinHeap: Next top is 5", minH.top().second == 5);

        MaxHeap maxH;
        maxH.push({"A", 5});
        maxH.push({"B", 2});
        maxH.push({"C", 8});
        testAssert("MaxHeap: Top is highest frequency (8)", maxH.top().second == 8);
    }

    // 8. FenwickTree and DNARangeIndex Tests
    {
        FenwickTree bit(5);
        bit.update(1, 2);
        bit.update(3, 5);
        testAssert("BIT: Prefix sum query(3) == 7", bit.query(3) == 7);
        testAssert("BIT: Range query [2..3] == 5", bit.rangeQuery(2, 3) == 5);

        DNARangeIndex dnaIdx;
        std::string sample = "ACGTACGT";
        dnaIdx.build(sample);
        testAssert("DNA Index: Count A in [1..8] is 2", dnaIdx.countA(1, 8) == 2);
        testAssert("DNA Index: Count C in [1..8] is 2", dnaIdx.countC(1, 8) == 2);
        testAssert("DNA Index: Count G in [1..8] is 2", dnaIdx.countG(1, 8) == 2);
        testAssert("DNA Index: Count T in [1..8] is 2", dnaIdx.countT(1, 8) == 2);
        testAssert("DNA Index: GC% in [1..8] is 50.0%", dnaIdx.gcContent(1, 8) == 50.0);

        // Invalid range handling
        testAssert("DNA Index: Invalid range [5..2] returns 0", dnaIdx.countA(5, 2) == 0);
        testAssert("DNA Index: Negative range [-3..0] returns 0", dnaIdx.countA(-3, 0) == 0);

        // Dynamic point mutation
        dnaIdx.updateBase(1, 'G'); // Mutate A to G
        testAssert("DNA Index: Mutated count A is now 1", dnaIdx.countA(1, 8) == 1);
        testAssert("DNA Index: Mutated count G is now 3", dnaIdx.countG(1, 8) == 3);
    }

    // 9. Map and K-mer Tests
    {
        SequenceMapIndex smi;
        SequenceRecord r1{1, "u", "SEQ_ONE", "p", 10, 45.0, "2026-01-01"};
        SequenceRecord r2{2, "u", "SEQ_TWO", "p", 20, 55.0, "2026-02-01"};
        smi.addRecord(r1);
        smi.addRecord(r2);

        testAssert("Map: Find by ID", smi.findById(1) != nullptr);
        testAssert("Map: Find by Exact Name 'SEQ_ONE'", smi.findIdsByName("SEQ_ONE").size() == 1);
        testAssert("Map: Find by Name Prefix 'SEQ'", smi.findIdsByNamePrefix("SEQ").size() == 2);
        testAssert("Map: Find by GC Range [50..60]", smi.findByGCRange(50.0, 60.0).size() == 1);
        testAssert("Map: Find by Date Range", smi.findByDateRange("2026-01-01", "2026-01-15").size() == 1);
        testAssert("Map: Remove record by ID", smi.removeRecordById(1) && smi.findById(1) == nullptr);
        testAssert("Map: Internal hash table buckets > 0", smi.getIdIndex().bucket_count() > 0);

        auto kmap = countKmers("AAAA", 2);
        testAssert("K-mer: 'AA' counted 3 times in 'AAAA'", kmap["AA"] == 3);
        auto topK = getTopKmers(kmap, 1);
        testAssert("Top-K: Top k-mer is AA", !topK.empty() && topK[0].first == "AA");
    }

    // 10. STL Utilities Tests
    {
        std::vector<SequenceRecord> vec;
        vec.push_back({10, "u", "Z", "p", 30, 40.0, "2026-01-02"});
        vec.push_back({20, "u", "A", "p", 10, 60.0, "2026-01-01"});
        STLUtilities::sortBySequenceName(vec);
        testAssert("STL: Sort by name puts 'A' first", vec[0].sequenceName == "A");
        STLUtilities::sortByLengthAscending(vec);
        testAssert("STL: Sort by length puts 10 first", vec[0].length == 10);
        STLUtilities::sortByGCContent(vec);
        testAssert("STL: Sort by GC content puts 40.0% first", vec[0].gcContent == 40.0);
        STLUtilities::sortByUploadDate(vec);
        testAssert("STL: Sort by upload date puts 2026-01-01 first", vec[0].uploadDate == "2026-01-01");

        auto filteredLen = STLUtilities::filterByLength(vec, 10, 20);
        testAssert("STL: Filter by length returns 1 item", filteredLen.size() == 1 && filteredLen[0].length == 10);
        auto filteredGC = STLUtilities::filterByGC(vec, 50.0, 70.0);
        testAssert("STL: Filter by GC finds 1 record", filteredGC.size() == 1 && filteredGC[0].id == 20);
        testAssert("STL: Search by keyword 'A'", STLUtilities::searchByNameContains(vec, "A").size() == 1);
        testAssert("STL: Count GC > 50% is 1", STLUtilities::countIfGCGreaterThan(vec, 50.0) == 1);
        testAssert("STL: Reverse string 'ATGC' == 'CGTA'", STLUtilities::reverseString("ATGC") == "CGTA");
        testAssert("STL: Transform uppercase 'atgc' == 'ATGC'", STLUtilities::transformToUppercase("atgc") == "ATGC");
    }

    // 11. Team Polymorphic Integration Tests
    {
        TreeSequenceIndex treeIndex;
        MapSequenceIndex mapIndexAdapter;

        SequenceRecord testRec{99, "team_user", "SHARED_SEQ", "path", 100, 50.0, "2026-09-27"};

        ISequenceIndex* pTree = &treeIndex;
        pTree->addSequence(testRec);
        testAssert("Integration: TreeSequenceIndex polymorphism works", pTree->findSequenceById(99) != nullptr);
        testAssert("Integration: TreeSequenceIndex searchByName", pTree->searchByName("SHARED_SEQ").size() == 1);
        testAssert("Integration: TreeSequenceIndex removal", pTree->removeSequenceById(99) && pTree->findSequenceById(99) == nullptr);

        ISequenceIndex* pMap = &mapIndexAdapter;
        pMap->addSequence(testRec);
        testAssert("Integration: MapSequenceIndex polymorphism works", pMap->findSequenceById(99) != nullptr);
        testAssert("Integration: MapSequenceIndex searchByName", pMap->searchByName("SHARED_SEQ").size() == 1);
        testAssert("Integration: MapSequenceIndex removal", pMap->removeSequenceById(99) && pMap->findSequenceById(99) == nullptr);

        auto edges = KmerService::generateDeBruijnEdges("ATGC", 3);
        testAssert("Integration: De Bruijn graph edge generation", edges.size() == 2 && edges[0].first == "AT" && edges[0].second == "TG");
    }

    std::cout << "======================================================\n";
    std::cout << "TEST RESULTS: " << passed << " / " << total << " PASSED.\n";
    if (passed == total)
    {
        std::cout << "ALL TEST CASES PASSED SUCCESSFULLY! [100%]\n";
    }
    else
    {
        std::cout << "SOME TESTS FAILED.\n";
    }
    std::cout << "======================================================\n\n";

    return passed == total;
}
