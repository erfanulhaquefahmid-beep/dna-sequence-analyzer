#include "menu/AppMenu.hpp"

#include "ds/DynamicArray.hpp"
#include "ds/Stack.hpp"
#include "ds/Queue.hpp"
#include "ds/DNAApplications.hpp"

#include "comparison.h"
#include "dna_generator.h"
#include "graph.h"
#include "replication.h"
#include "searching.h"
#include "sorting.h"
#include "transformation.h"
#include "translation.h"
#include "menu/MyModuleMenu.hpp"
#include "tests.h"

#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace UI {
namespace {

std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string value;
    std::getline(std::cin, value);
    return value;
}

bool parseSize(const std::string& input, std::size_t& value) {
    std::stringstream stream(input);
    unsigned long long parsed = 0;
    char extra = '\0';
    if (!(stream >> parsed) || (stream >> extra)) {
        return false;
    }
    value = static_cast<std::size_t>(parsed);
    return true;
}

void printDivider() {
    std::cout << "------------------------------------------------------------\n";
}

} // namespace

void AppMenu::run() {
    while (true) {
        std::cout << "\n============================================================\n"
                  << "                   DNA SEQUENCE ANALYZER                      \n"
                  << "                       CSE 2106 LAB                         \n"
                  << "============================================================\n"
                  << " [1] Shakil's Core DSA Workbench (Array, Stack, Queue Demos)\n"
                  << " [2] Fahmid's DSA Subsystem (Trees, Maps, Linked Lists, STL)\n"
                  << " [3] Sequence Generation & Molecular Biology Subsystem (Nadid)\n"
                  << " [4] Genome Transformations & KMP Search Subsystem (Nadid)  \n"
                  << " [5] Sequence Comparison & Multi-Algorithm Sorting (Nadid)  \n"
                  << " [6] De Bruijn Graph Assembly & Graph Traversal (Nadid)     \n"
                  << " [7] Run Full Automated Test Suite (All 160 Tests)          \n"
                  << " [0] Exit Application                                       \n"
                  << "============================================================\n";
        std::string choice = readLine("Select Subsystem: ");

        if (choice == "0") {
            std::cout << "\nExiting DNA Sequence Analyzer. Goodbye!\n";
            break;
        } else if (choice == "1") {
            runDSAWorkbench();
        } else if (choice == "2") {
            runFahmidModule();
        } else if (choice == "3") {
            runMolecularBiology();
        } else if (choice == "4") {
            runTransformationsAndSearch();
        } else if (choice == "5") {
            runComparisonAndSorting();
        } else if (choice == "6") {
            runGraphAnalytics();
        } else if (choice == "7") {
            std::cout << "\nExecuting Automated Test Suite...\n";
            (void)runAllTests();
        } else {
            std::cout << "Invalid selection. Please choose an option between 0 and 7.\n";
        }
    }
}

void AppMenu::runFahmidModule() {
    MyModuleMenu fahmidMenu;
    fahmidMenu.runMainMenu();
}

// ============================================================================
// 1. Shakil's Core DSA Workbench
// ============================================================================

void AppMenu::runDSAWorkbench() {
    while (true) {
        std::cout << "\n--- Shakil's Core DSA Workbench (Custom Scratch Implementations) ---\n"
                  << " 1. DynamicArray: DNA Sequence Collection Store & Capacity Diagnostics\n"
                  << " 2. Stack: Interactive DNA Transformation with Live Undo / Redo\n"
                  << " 3. Stack: RNA Secondary Structure & Hairpin Loop Bracket Validator\n"
                  << " 4. Queue: Real-time Sliding-Window GC% Scanner (O(1) Ring Buffer)\n"
                  << " 5. Stack: Palindromic Restriction Enzyme Recognition Site Detector\n"
                  << " 0. Return to Main Menu\n";
        std::string choice = readLine("Choose Workbench Demo: ");

        if (choice == "0") break;
        else if (choice == "1") runDynamicArrayDemo();
        else if (choice == "2") runUndoRedoDemo();
        else if (choice == "3") runRNAValidatorDemo();
        else if (choice == "4") runSlidingWindowDemo();
        else if (choice == "5") runRestrictionSiteDemo();
        else std::cout << "Invalid choice. Please select 0-5.\n";
    }
}

void AppMenu::runDynamicArrayDemo() {
    std::cout << "\n--- DynamicArray<T> Sequence Store Demo ---\n";
    DS::DynamicArray<std::string> store(2);

    while (true) {
        std::cout << "\nStored Sequences (Count = " << store.size()
                  << ", Capacity = " << store.capacity()
                  << ", Load Factor = " << (store.loadFactor() * 100.0) << "%):\n";
        for (std::size_t i = 0; i < store.size(); ++i) {
            std::cout << "  [" << i << "] " << store[i]
                      << " (len=" << store[i].size() << ")\n";
        }

        std::cout << "\nActions: [1] Push Back  [2] Insert at Index  [3] Remove at Index  [4] Shrink to Fit  [0] Back\n";
        std::string opt = readLine("Select action: ");

        if (opt == "0") {
            break;
        } else if (opt == "1") {
            std::string seq = readLine("Enter DNA sequence to append: ");
            if (!seq.empty()) {
                store.push_back(seq);
                std::cout << "Appended. Current capacity: " << store.capacity() << "\n";
            }
        } else if (opt == "2") {
            std::size_t idx = 0;
            if (!parseSize(readLine("Index: "), idx) || idx > store.size()) {
                std::cout << "Invalid index.\n";
                continue;
            }
            std::string seq = readLine("Enter DNA sequence: ");
            store.insert(idx, seq);
            std::cout << "Inserted successfully.\n";
        } else if (opt == "3") {
            std::size_t idx = 0;
            if (!parseSize(readLine("Index to remove: "), idx) || idx >= store.size()) {
                std::cout << "Invalid index.\n";
                continue;
            }
            store.removeAt(idx);
            std::cout << "Removed element at index " << idx << ".\n";
        } else if (opt == "4") {
            store.shrink_to_fit();
            std::cout << "Shrunk capacity to: " << store.capacity() << "\n";
        }
    }
}

void AppMenu::runUndoRedoDemo() {
    std::cout << "\n--- Live DNA Mutation with Stack-based Undo / Redo ---\n";
    std::string initial = readLine("Enter initial DNA sequence (default: ATGCGATC): ");
    if (initial.empty()) initial = "ATGCGATC";

    DS::DNAHistoryManager history(initial);

    while (true) {
        std::cout << "\n========================================\n"
                  << "Current DNA : " << history.getCurrentSequence() << "\n"
                  << "Last Action : " << history.getLastAction() << "\n"
                  << "Undo Stack  : " << history.getUndoCount() << " states available\n"
                  << "Redo Stack  : " << history.getRedoCount() << " states available\n"
                  << "========================================\n"
                  << "Mutations: [1] Complement  [2] Reverse  [3] Rev-Complement\n"
                  << "           [4] Substitute  [5] Insert   [6] Delete\n"
                  << "History:   [U] Undo        [R] Redo     [0] Return\n";
        std::string action = readLine("Choose option: ");

        if (action == "0") {
            break;
        } else if (action == "u" || action == "U") {
            if (history.undo()) {
                std::cout << "Undo successful!\n";
            } else {
                std::cout << "Nothing to undo!\n";
            }
        } else if (action == "r" || action == "R") {
            if (history.redo()) {
                std::cout << "Redo successful!\n";
            } else {
                std::cout << "Nothing to redo!\n";
            }
        } else if (action == "1") {
            std::string mutated = Transformation::complement(history.getCurrentSequence());
            history.applyTransformation(mutated, "Applied Complement");
        } else if (action == "2") {
            std::string mutated = Transformation::reverse(history.getCurrentSequence());
            history.applyTransformation(mutated, "Applied Reversal");
        } else if (action == "3") {
            std::string mutated = Transformation::reverseComplement(history.getCurrentSequence());
            history.applyTransformation(mutated, "Applied Reverse-Complement");
        } else if (action == "4") {
            std::size_t idx = 0;
            if (!parseSize(readLine("Index: "), idx) || idx >= history.getCurrentSequence().size()) {
                std::cout << "Invalid index.\n";
                continue;
            }
            std::string b = readLine("New base (A/T/G/C): ");
            if (b.size() == 1) {
                std::string mutated = Transformation::substitute(history.getCurrentSequence(), idx, b[0]);
                history.applyTransformation(mutated, "Substituted base at " + std::to_string(idx) + " with " + b);
            }
        } else if (action == "5") {
            std::size_t idx = 0;
            if (!parseSize(readLine("Index: "), idx) || idx > history.getCurrentSequence().size()) {
                std::cout << "Invalid index.\n";
                continue;
            }
            std::string b = readLine("Bases to insert: ");
            std::string mutated = Transformation::insert(history.getCurrentSequence(), idx, b);
            history.applyTransformation(mutated, "Inserted '" + b + "' at index " + std::to_string(idx));
        } else if (action == "6") {
            std::size_t idx = 0;
            std::size_t count = 0;
            if (!parseSize(readLine("Index: "), idx) || !parseSize(readLine("Count: "), count)) {
                std::cout << "Invalid deletion parameters.\n";
                continue;
            }
            try {
                std::string mutated = Transformation::erase(history.getCurrentSequence(), idx, count);
                history.applyTransformation(mutated, "Deleted " + std::to_string(count) + " bases from index " + std::to_string(idx));
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << "\n";
            }
        }
    }
}

void AppMenu::runRNAValidatorDemo() {
    std::cout << "\n--- RNA Secondary Structure & Bracket Matching Validator ---\n";
    std::cout << "Example Hairpin:\n"
              << "  RNA Sequence : GCUUUGC\n"
              << "  Dot-Bracket  : ((...))\n";

    std::string rna = readLine("Enter RNA sequence: ");
    std::string dot = readLine("Enter Dot-Bracket notation: ");

    auto dotResult = DS::RNAStructureValidator::validateDotBracket(dot);
    if (!dotResult.isValid) {
        std::cout << "Bracket Syntax Error: " << dotResult.errorMessage << "\n";
        return;
    }

    auto fullResult = DS::RNAStructureValidator::validateSecondaryStructure(rna, dot);
    if (fullResult.isValid) {
        std::cout << "[SUCCESS] Valid RNA secondary structure!\n"
                  << "  Base pairs formed: " << fullResult.basePairCount << "\n";
    } else {
        std::cout << "[FAILED] " << fullResult.errorMessage << "\n";
    }
}

void AppMenu::runSlidingWindowDemo() {
    std::cout << "\n--- Queue-Based Sliding-Window GC% Scanner (O(1) Ring Buffer) ---\n";
    std::string seq = readLine("Enter DNA sequence (e.g. GCGCATATGCGC): ");
    if (seq.empty()) seq = "GCGCATATGCGC";

    std::size_t wSize = 4;
    std::string wInput = readLine("Enter Window Size W (>= 2): ");
    if (!parseSize(wInput, wSize) || wSize < 2 || wSize > seq.size()) {
        std::cout << "Invalid window size. Using default W=4.\n";
        wSize = 4;
    }

    auto windows = DS::SlidingWindowGCScanner::scanSequence(seq, wSize);
    std::cout << "\nWindow Scan Results (Total windows: " << windows.size() << "):\n";
    std::cout << "  Start\tSubsequence\tGC Percentage\n";
    printDivider();
    for (std::size_t i = 0; i < windows.size(); ++i) {
        std::cout << "  " << windows[i].startPosition << "\t"
                  << windows[i].windowSubstr << "\t\t"
                  << windows[i].gcPercentage << "%\n";
    }
}

void AppMenu::runRestrictionSiteDemo() {
    std::cout << "\n--- Palindromic Restriction Site Detection (Stack Reversal) ---\n";
    std::string seq = readLine("Enter DNA sequence (e.g. GAATTC for EcoRI, GGATCC for BamHI): ");
    bool isPal = DS::RestrictionSiteDetector::isPalindromicSite(seq);
    if (isPal) {
        std::cout << "[TRUE] '" << seq << "' is a reverse palindromic restriction recognition site!\n";
    } else {
        std::cout << "[FALSE] '" << seq << "' is not a reverse palindrome.\n";
    }
}

// ============================================================================
// 2. Molecular Biology Subsystem (Nadid)
// ============================================================================

void AppMenu::runMolecularBiology() {
    while (true) {
        std::cout << "\n--- Sequence Generation & Molecular Biology Subsystem ---\n"
                  << " 1. Generate Random DNA Sequence\n"
                  << " 2. Replicate DNA (Double Strand 5' -> 3' and 3' -> 5')\n"
                  << " 3. Transcribe Template DNA to RNA\n"
                  << " 4. Translate RNA to Protein Sequence\n"
                  << " 0. Return to Main Menu\n";
        std::string choice = readLine("Select Option: ");

        if (choice == "0") break;
        else if (choice == "1") {
            std::size_t len = 0;
            if (!parseSize(readLine("Sequence length: "), len)) {
                std::cout << "Invalid length.\n";
                continue;
            }
            std::size_t seed = 0;
            (void)parseSize(readLine("Seed (0 for random): "), seed);
            std::string generated = DNAGenerator::generateSequence(len, static_cast<unsigned int>(seed));
            std::cout << "Generated DNA: " << generated << "\n";
        } else if (choice == "2") {
            std::string dna = readLine("DNA sequence: ");
            try {
                std::cout << Replication::formattedDoubleStrand(dna) << "\n";
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << "\n";
            }
        } else if (choice == "3") {
            std::string dna = readLine("Template DNA sequence: ");
            std::cout << "RNA: " << Translation::transcribeTemplateDNA(dna) << "\n";
        } else if (choice == "4") {
            std::string rna = readLine("RNA sequence: ");
            std::string protein = Translation::translateRNA(rna);
            if (protein.empty()) {
                std::cout << "No start codon (AUG) found, or no translatable region.\n";
            } else {
                std::cout << "Protein Sequence: " << protein << "\n";
            }
        }
    }
}

// ============================================================================
// 3. Genome Transformations & KMP Search (Nadid)
// ============================================================================

void AppMenu::runTransformationsAndSearch() {
    while (true) {
        std::cout << "\n--- Genome Transformations & KMP Search Subsystem ---\n"
                  << " 1. KMP Pattern Search (Find Motifs with LPS Table)\n"
                  << " 2. Complement Sequence\n"
                  << " 3. Reverse Sequence\n"
                  << " 4. Reverse Complement Sequence\n"
                  << " 5. Substitute Base\n"
                  << " 6. Insert Bases\n"
                  << " 7. Delete Bases\n"
                  << " 0. Return to Main Menu\n";
        std::string choice = readLine("Select Option: ");

        if (choice == "0") break;
        else if (choice == "1") {
            std::string seq = readLine("DNA sequence: ");
            std::string pat = readLine("Pattern: ");
            auto res = Searching::kmpSearch(seq, pat);
            std::cout << "Pattern Found: " << (res.found ? "Yes" : "No") << "\n";
            std::cout << "Total Occurrences: " << res.positions.size() << "\n";
            if (res.found) {
                std::cout << "0-based Positions: ";
                for (std::size_t i = 0; i < res.positions.size(); ++i) {
                    if (i > 0) std::cout << ", ";
                    std::cout << res.positions[i];
                }
                std::cout << "\n";
            }
        } else if (choice == "2") {
            std::string seq = readLine("DNA: ");
            std::cout << "Result: " << Transformation::complement(seq) << "\n";
        } else if (choice == "3") {
            std::string seq = readLine("DNA: ");
            std::cout << "Result: " << Transformation::reverse(seq) << "\n";
        } else if (choice == "4") {
            std::string seq = readLine("DNA: ");
            std::cout << "Result: " << Transformation::reverseComplement(seq) << "\n";
        } else if (choice == "5") {
            std::string seq = readLine("DNA: ");
            std::size_t idx = 0;
            if (!parseSize(readLine("Index: "), idx)) continue;
            std::string b = readLine("New base: ");
            if (b.size() == 1) {
                try {
                    std::cout << "Result: " << Transformation::substitute(seq, idx, b[0]) << "\n";
                } catch (const std::exception& e) {
                    std::cout << "Error: " << e.what() << "\n";
                }
            }
        } else if (choice == "6") {
            std::string seq = readLine("DNA: ");
            std::size_t idx = 0;
            if (!parseSize(readLine("Insertion Index: "), idx)) continue;
            std::string b = readLine("Bases: ");
            try {
                std::cout << "Result: " << Transformation::insert(seq, idx, b) << "\n";
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << "\n";
            }
        } else if (choice == "7") {
            std::string seq = readLine("DNA: ");
            std::size_t idx = 0, cnt = 0;
            if (!parseSize(readLine("Start Index: "), idx) || !parseSize(readLine("Count: "), cnt)) continue;
            try {
                std::cout << "Result: " << Transformation::erase(seq, idx, cnt) << "\n";
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << "\n";
            }
        }
    }
}

// ============================================================================
// 4. Sequence Comparison & Multi-Algorithm Sorting (Nadid)
// ============================================================================

void AppMenu::runComparisonAndSorting() {
    while (true) {
        std::cout << "\n--- Sequence Comparison & Multi-Algorithm Sorting ---\n"
                  << " 1. Compare Two Sequences (Similarity %, Mismatches, Hamming Distance)\n"
                  << " 2. Sort Sequences by Length (Bubble, Selection, Insertion, Merge, Quick)\n"
                  << " 0. Return to Main Menu\n";
        std::string choice = readLine("Select Option: ");

        if (choice == "0") break;
        else if (choice == "1") {
            std::string s1 = readLine("First sequence: ");
            std::string s2 = readLine("Second sequence: ");
            auto res = Comparison::compareSequences(s1, s2);
            std::cout << "Equal: " << (res.equal ? "Yes" : "No") << "\n";
            std::cout << "Matching positions: " << res.matchingPositions << "\n";
            std::cout << "Mismatches: " << res.mismatches << "\n";
            std::cout << "Similarity: " << res.similarityPercentage << "%\n";
            if (res.hammingDefined) {
                std::cout << "Hamming distance: " << res.hammingDistance << "\n";
            } else {
                std::cout << "Hamming distance: undefined for unequal lengths\n";
            }
        } else if (choice == "2") {
            std::cout << "Algorithms: [1] Bubble  [2] Selection  [3] Insertion  [4] Merge  [5] Quick\n";
            std::string alg = readLine("Choose algorithm (1-5): ");
            bool asc = (readLine("Order (1 = asc, 2 = desc): ") != "2");
            std::size_t n = 0;
            if (!parseSize(readLine("Number of sequences: "), n) || n == 0) continue;

            std::vector<std::string> seqs;
            for (std::size_t i = 0; i < n; ++i) {
                seqs.push_back(readLine("Sequence " + std::to_string(i + 1) + ": "));
            }

            std::vector<std::string> sorted;
            if (alg == "1") sorted = Sorting::bubbleSortByLength(seqs, asc);
            else if (alg == "2") sorted = Sorting::selectionSortByLength(seqs, asc);
            else if (alg == "3") sorted = Sorting::insertionSortByLength(seqs, asc);
            else if (alg == "4") sorted = Sorting::mergeSortByLength(seqs, asc);
            else if (alg == "5") sorted = Sorting::quickSortByLength(seqs, asc);
            else {
                std::cout << "Unknown algorithm.\n";
                continue;
            }

            std::cout << "\nSorted Sequences by Length:\n";
            for (std::size_t i = 0; i < sorted.size(); ++i) {
                std::cout << "  " << (i + 1) << ". " << sorted[i]
                          << " (length = " << sorted[i].size() << ")\n";
            }
        }
    }
}

// ============================================================================
// 5. De Bruijn Graph Assembly & Traversal (Nadid)
// ============================================================================

void AppMenu::runGraphAnalytics() {
    std::cout << "\n--- De Bruijn Graph Assembly & Analytics ---\n";
    std::string seq = readLine("Enter DNA sequence: ");
    std::size_t k = 0;
    if (!parseSize(readLine("Enter k (>= 2): "), k) || k < 2) {
        std::cout << "Invalid k.\n";
        return;
    }

    DeBruijnGraph graph(k);
    if (!graph.build(seq)) {
        std::cout << "Failed to build graph: sequence too short.\n";
        return;
    }

    std::cout << "\nGenerated k-mers:\n";
    for (const auto& kmer : graph.generateKmers(seq)) {
        std::cout << "  " << kmer << "\n";
    }

    std::cout << "\nGraph Adjacency List:\n";
    graph.display(std::cout);

    std::string start = readLine("Start vertex for traversal (" + std::to_string(k - 1) + " bases): ");
    auto bfsOrder = graph.bfs(start);
    auto dfsOrder = graph.dfs(start);

    std::cout << "BFS Traversal: ";
    for (const auto& v : bfsOrder) std::cout << v << " ";
    std::cout << "\nDFS Traversal: ";
    for (const auto& v : dfsOrder) std::cout << v << " ";
    std::cout << "\n";
}

} // namespace UI
