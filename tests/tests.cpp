#include "tests.h"
#include "comparison.h"
#include "dna_generator.h"
#include "graph.h"
#include "replication.h"
#include "searching.h"
#include "sorting.h"
#include "test_data.h"
#include "transformation.h"
#include "translation.h"
#include "ds/DynamicArray.hpp"
#include "ds/Stack.hpp"
#include "ds/Queue.hpp"
#include "ds/DNAApplications.hpp"

#include <cmath>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

namespace {

int passed = 0;
int failed = 0;

void expect(bool condition, const std::string& name) {
    if (condition) {
        ++passed;
        std::cout << "PASS: " << name << '\n';
    } else {
        ++failed;
        std::cout << "FAIL: " << name << '\n';
    }
}


} // namespace

int runAllTests() {
    std::cout << "===== DNA Sequence Analyzer Tests =====\n";

    // Searching
    {
        const Searching::SearchResult result =
            Searching::kmpSearch("AAAAA", "AAA");
        expect(result.found, "KMP finds a pattern");
        expect(result.positions == std::vector<std::size_t>({0, 1, 2}),
               "KMP returns overlapping positions");

        const Searching::SearchResult missing =
            Searching::kmpSearch("ATGC", "TTT");
        expect(!missing.found && missing.positions.empty(),
               "KMP handles a missing pattern");
    }

    // Graph
    {
        DeBruijnGraph graph(3);
        expect(graph.build(TestData::graphSequence), "De Bruijn graph builds");
        expect(graph.getVertices().size() == 6, "Graph creates expected vertices");
        expect(!graph.bfs("AA").empty(), "Graph BFS visits vertices");
        expect(!graph.dfs("AA").empty(), "Graph DFS visits vertices");
        expect(!graph.generateKmers("AT").empty() ? false : true,
               "k-mer generation rejects too-short input");
    }

    // Generation
    {
        const std::string generated = DNAGenerator::generateSequence(20, 12345);
        expect(generated.size() == 20, "Random DNA sequence has requested length");
        bool valid = true;
        for (const char base : generated) {
            if (base != 'A' && base != 'T' && base != 'G' && base != 'C') {
                valid = false;
            }
        }
        expect(valid, "Random DNA sequence uses only A/T/G/C");

        const std::vector<std::string> many =
            DNAGenerator::generateSequences(3, 8, 42);
        expect(many.size() == 3 && many[0].size() == 8,
               "Multiple random sequences are generated");
    }

    // Replication
    {
        expect(Replication::complementaryStrand("ATCG") == "TAGC",
               "Complementary strand uses DNA base pairing");
        expect(Replication::formattedDoubleStrand("ATCG") ==
                   "5' ATCG 3'\n3' TAGC 5'",
               "Double-strand formatting preserves directionality");
    }

    // Transcription / translation
    {
        expect(Translation::transcribeTemplateDNA("ATGC") == "UACG",
               "Template DNA transcribes using requested mapping");
        expect(Translation::aminoAcidForCodon("AUG") == "M",
               "AUG maps to methionine");
        expect(Translation::aminoAcidForCodon("UAA") == "*",
               "UAA maps to stop");
        expect(Translation::translateRNA("CCAUGGCCUAA") == "MA",
               "RNA translation starts at AUG and stops at UAA");
        expect(Translation::translateDNA(TestData::templateForTranslation) == "ME",
               "DNA template transcription plus translation works");
    }

    // Transformation
    {
        expect(Transformation::complement("ATGC") == "TACG",
               "Complement transformation works");
        expect(Transformation::reverse("ATGC") == "CGTA",
               "Reverse transformation works");
        expect(Transformation::reverseComplement("ATGC") == "GCAT",
               "Reverse-complement transformation works");
        expect(Transformation::substitute("ATGC", 1, 'C') == "ACGC",
               "Substitution transformation works");
        expect(Transformation::insert("ATGC", 2, "TT") == "ATTTGC",
               "Insertion transformation works");
        expect(Transformation::erase("ATGC", 1, 2) == "AC",
               "Deletion transformation works");
    }

    // Sorting by sequence length
    {
        const std::vector<std::string> input = {
            "ATGC", "A", "ATGCG", "AT", "ATG", "GCGCGC"
        };

        const std::vector<std::string> expectedAscending = {
            "A", "AT", "ATG", "ATGC", "ATGCG", "GCGCGC"
        };
        const std::vector<std::string> expectedDescending = {
            "GCGCGC", "ATGCG", "ATGC", "ATG", "AT", "A"
        };

        const std::vector<std::string> bubble =
            Sorting::bubbleSortByLength(input);
        const std::vector<std::string> selection =
            Sorting::selectionSortByLength(input);
        const std::vector<std::string> insertion =
            Sorting::insertionSortByLength(input);
        const std::vector<std::string> merge =
            Sorting::mergeSortByLength(input);
        const std::vector<std::string> quick =
            Sorting::quickSortByLength(input);

        expect(bubble == expectedAscending, "Bubble sort orders by length");
        expect(selection == expectedAscending, "Selection sort orders by length");
        expect(insertion == expectedAscending, "Insertion sort orders by length");
        expect(merge == expectedAscending, "Merge sort orders by length");
        expect(quick == expectedAscending, "Quick sort orders by length");
        expect(Sorting::mergeSortByLength(input, false) == expectedDescending,
               "Merge sort supports descending length order");
        expect(Sorting::quickSortByLength(input, false) == expectedDescending,
               "Quick sort supports descending length order");
        expect(Sorting::isSortedByLength(quick),
               "Sorting verifier recognizes ascending result");
        expect(Sorting::isSortedByLength(expectedDescending, false),
               "Sorting verifier recognizes descending result");
    }

    // Comparison
    {
        const Comparison::ComparisonResult result =
            Comparison::compareSequences("ATGC", "ATCC");
        expect(!result.equal, "Comparison detects unequal sequences");
        expect(result.matchingPositions == 3, "Comparison counts matching positions");
        expect(result.mismatches == 1, "Comparison counts mismatches");
        expect(result.hammingDefined && result.hammingDistance == 1,
               "Hamming distance works for equal lengths");
        expect(std::fabs(result.similarityPercentage - 75.0) < 0.0001,
               "Similarity percentage is correct");

        const Comparison::ComparisonResult differentLengths =
            Comparison::compareSequences("ATGC", "ATGCA");
    }

    // Shakil: Custom DynamicArray<T> from scratch (zero STL)
    {
        DS::DynamicArray<int> arr(2);
        expect(arr.size() == 0 && arr.capacity() == 2 && arr.isEmpty(),
               "DynamicArray initializes empty with requested capacity");
        arr.push_back(10);
        arr.push_back(20);
        arr.push_back(30); // triggers capacity doubling to 4
        expect(arr.size() == 3 && arr.capacity() == 4,
               "DynamicArray doubles capacity when full");
        expect(arr[0] == 10 && arr[1] == 20 && arr[2] == 30,
               "DynamicArray operator[] retrieves correct elements");
        expect(arr.front() == 10 && arr.back() == 30,
               "DynamicArray front() and back() are correct");

        arr.insert(1, 15); // [10, 15, 20, 30]
        expect(arr.size() == 4 && arr[1] == 15 && arr[2] == 20,
               "DynamicArray insert at middle index works");

        arr.removeAt(1); // [10, 20, 30]
        expect(arr.size() == 3 && arr[1] == 20,
               "DynamicArray removeAt index works");

        arr.pop_back(); // [10, 20]
        expect(arr.size() == 2 && arr.back() == 20,
               "DynamicArray pop_back removes last element");

        DS::DynamicArray<int> copy = arr;
        expect(copy == arr, "DynamicArray copy constructor produces identical array");
        copy.push_back(99);
        expect(copy != arr, "DynamicArray deep copy is independent of original");

        bool caughtOutOfRange = false;
        try {
            arr.at(99);
        } catch (const std::out_of_range&) {
            caughtOutOfRange = true;
        }
        expect(caughtOutOfRange, "DynamicArray at() throws out_of_range on invalid index");
    }

    // Shakil: Custom Stack<T> from scratch (zero STL)
    {
        DS::Stack<std::string> st;
        expect(st.isEmpty() && st.size() == 0, "Stack initializes empty");
        st.push("first");
        st.push("second");
        st.push("third");
        expect(st.size() == 3 && st.top() == "third", "Stack push and top are correct");
        st.pop();
        expect(st.size() == 2 && st.top() == "second", "Stack pop correctly updates top");
        st.pop();
        st.pop();
        expect(st.isEmpty(), "Stack is empty after popping all elements");

        bool caughtUnderflow = false;
        try {
            st.pop();
        } catch (const std::underflow_error&) {
            caughtUnderflow = true;
        }
        expect(caughtUnderflow, "Stack pop throws underflow_error when empty");
    }

    // Shakil: Custom Queue<T> Circular Ring Buffer from scratch (zero STL)
    {
        DS::Queue<int> q(3);
        expect(q.isEmpty() && q.size() == 0, "Queue initializes empty");
        q.enqueue(1);
        q.enqueue(2);
        q.enqueue(3);
        expect(q.size() == 3 && q.front() == 1 && q.back() == 3,
               "Queue enqueue and front/back work");
        q.dequeue();
        q.dequeue();
        expect(q.size() == 1 && q.front() == 3,
               "Queue dequeue removes from front");

        // Enqueue to trigger circular wraparound
        q.enqueue(4);
        q.enqueue(5);
        expect(q.size() == 3 && q.front() == 3 && q.back() == 5,
               "Queue handles circular index wraparound correctly");

        // Enqueue to trigger dynamic capacity doubling while preserving FIFO order
        q.enqueue(6);
        expect(q.size() == 4 && q.front() == 3 && q.back() == 6,
               "Queue preserves FIFO order across dynamic resizing");

        bool caughtUnderflow = false;
        q.dequeue(); q.dequeue(); q.dequeue(); q.dequeue();
        expect(q.isEmpty(), "Queue drains to empty");
        try {
            q.dequeue();
        } catch (const std::underflow_error&) {
            caughtUnderflow = true;
        }
        expect(caughtUnderflow, "Queue dequeue throws underflow_error when empty");
    }

    // Shakil: Stack Application - DNA Transformation Undo / Redo History
    {
        DS::DNAHistoryManager history("ATGC");
        expect(history.getCurrentSequence() == "ATGC", "DNAHistoryManager sets initial sequence");
        expect(!history.canUndo() && !history.canRedo(), "Undo/Redo unavailable initially");

        history.applyTransformation("TACG", "Complement");
        history.applyTransformation("TACGT", "Insert T");
        expect(history.getUndoCount() == 2 && history.getCurrentSequence() == "TACGT",
               "DNAHistoryManager tracks mutation states");

        expect(history.undo() && history.getCurrentSequence() == "TACG",
               "DNAHistoryManager undo restores previous state");
        expect(history.undo() && history.getCurrentSequence() == "ATGC",
               "DNAHistoryManager second undo restores initial state");
        expect(!history.undo(), "DNAHistoryManager cannot undo past initial state");

        expect(history.redo() && history.getCurrentSequence() == "TACG",
               "DNAHistoryManager redo reapplies state");
        expect(history.redo() && history.getCurrentSequence() == "TACGT",
               "DNAHistoryManager second redo restores latest state");
    }

    // Shakil: Stack Application - RNA Secondary Structure & Hairpin Loop Validator
    {
        auto validDot = DS::RNAStructureValidator::validateDotBracket("((...))");
        expect(validDot.isValid && validDot.basePairCount == 2,
               "RNAStructureValidator accepts balanced dot-bracket notation");

        auto invalidDot = DS::RNAStructureValidator::validateDotBracket("((..)");
        expect(!invalidDot.isValid,
               "RNAStructureValidator rejects unbalanced opening brackets");

        // "GCUUUGC" with "((...))": G-C and C-G are canonical Watson-Crick base pairs
        auto validPairing = DS::RNAStructureValidator::validateSecondaryStructure(
            "GCUUUGC", "((...))");
        expect(validPairing.isValid,
               "RNAStructureValidator confirms complementary stem base pairs");

        // "AAUUUAA" with "((...))": A-A is non-complementary
        auto invalidPairing = DS::RNAStructureValidator::validateSecondaryStructure(
            "AAUUUAA", "((...))");
        expect(!invalidPairing.isValid,
               "RNAStructureValidator rejects non-complementary stem base pairs");
    }

    // Shakil: Queue Application - Real-time Sliding Window GC% Scanner
    {
        std::string seq = "GCATGC";
        // W=4: "GCAT" (50%), "CATG" (50%), "ATGC" (50%)
        auto windows = DS::SlidingWindowGCScanner::scanSequence(seq, 4);
        expect(windows.size() == 3, "SlidingWindowGCScanner generates correct window count");
        expect(std::fabs(windows[0].gcPercentage - 50.0) < 0.001,
               "SlidingWindowGCScanner calculates first window GC% correctly");
        expect(std::fabs(windows[2].gcPercentage - 50.0) < 0.001,
               "SlidingWindowGCScanner maintains running GC% in O(1) time per base");
    }

    // Shakil: Stack Application - Palindromic Restriction Site Detection
    {
        expect(DS::RestrictionSiteDetector::isPalindromicSite("GAATTC"),
               "EcoRI recognition site GAATTC is palindromic");
        expect(DS::RestrictionSiteDetector::isPalindromicSite("GGATCC"),
               "BamHI recognition site GGATCC is palindromic");
        expect(!DS::RestrictionSiteDetector::isPalindromicSite("GAATTA"),
               "Non-palindromic sequence GAATTA is rejected");
    }

    std::cout << "\n===== Test Summary =====\n";
    std::cout << "Passed: " << passed << '\n';
    std::cout << "Failed: " << failed << '\n';

    return failed == 0 ? 0 : 1;
}

#ifndef DNA_TESTS_AS_LIBRARY
int main() {
    return runAllTests();
}
#endif
