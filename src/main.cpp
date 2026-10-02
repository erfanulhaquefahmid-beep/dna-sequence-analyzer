#include "comparison.h"
#include "dna_generator.h"
#include "graph.h"
#include "replication.h"
#include "searching.h"
#include "sorting.h"
#include "test_data.h"
#include "tests.h"
#include "transformation.h"
#include "translation.h"

#include <cstddef>
#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace {

void printMenu() {
    std::cout << "\n===== DNA Sequence Analyzer =====\n"
              << "1. Generate Random DNA Sequence\n"
              << "2. Search DNA Sequence\n"
              << "3. Build De Bruijn Graph\n"
              << "4. Replicate DNA\n"
              << "5. Transcribe DNA to RNA\n"
              << "6. Translate RNA to Protein\n"
              << "7. Transform DNA Sequence\n"
              << "8. Compare Two Sequences\n"
              << "9. Sort Sequences by Length\n"
              << "10. Run Test Cases\n"
              << "0. Exit\n"
              << "Select an option: ";
}

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

void runSearch() {
    const std::string sequence = readLine("DNA sequence: ");
    const std::string pattern = readLine("Pattern (3+ characters recommended): ");

    if (pattern.size() < 3) {
        std::cout << "Warning: patterns shorter than 3 are allowed by the algorithm, "
                     "but the project recommends 3+ characters.\n";
    }

    const Searching::SearchResult result = Searching::kmpSearch(sequence, pattern);
    std::cout << "Found: " << (result.found ? "Yes" : "No") << '\n';
    std::cout << "Occurrences: " << result.positions.size() << '\n';

    if (result.found) {
        std::cout << "Starting positions (0-based): ";
        for (std::size_t i = 0; i < result.positions.size(); ++i) {
            if (i > 0) {
                std::cout << ", ";
            }
            std::cout << result.positions[i];
        }
        std::cout << '\n';
    }
}

void runGraph() {
    const std::string sequence = readLine("DNA sequence: ");
    const std::string kInput = readLine("k (>= 2): ");
    std::size_t k = 0;

    if (!parseSize(kInput, k) || k < 2) {
        std::cout << "Invalid k.\n";
        return;
    }

    DeBruijnGraph graph(k);
    if (!graph.build(sequence)) {
        std::cout << "Cannot build graph: sequence is shorter than k or k is invalid.\n";
        return;
    }

    std::cout << "k-mers:\n";
    const std::vector<std::string> kmers = graph.generateKmers(sequence);
    for (const std::string& kmer : kmers) {
        std::cout << "  " << kmer << '\n';
    }

    graph.display(std::cout);

    const std::string start = readLine("Traversal start vertex (k-1 bases): ");
    const std::vector<std::string> bfsOrder = graph.bfs(start);
    const std::vector<std::string> dfsOrder = graph.dfs(start);

    std::cout << "BFS: ";
    for (const std::string& value : bfsOrder) {
        std::cout << value << ' ';
    }
    std::cout << '\n';

    std::cout << "DFS: ";
    for (const std::string& value : dfsOrder) {
        std::cout << value << ' ';
    }
    std::cout << '\n';
}

void runGeneration() {
    const std::string lengthInput = readLine("Sequence length: ");
    std::size_t length = 0;
    if (!parseSize(lengthInput, length)) {
        std::cout << "Invalid length.\n";
        return;
    }

    const std::string seedInput = readLine("Seed (0 for random): ");
    std::size_t seedValue = 0;
    if (!parseSize(seedInput, seedValue)) {
        std::cout << "Invalid seed.\n";
        return;
    }

    const std::string sequence =
        DNAGenerator::generateSequence(length, static_cast<unsigned int>(seedValue));
    std::cout << "Generated sequence: " << sequence << '\n';
}

void runReplication() {
    const std::string dna = readLine("DNA sequence: ");
    try {
        std::cout << Replication::formattedDoubleStrand(dna) << '\n';
    } catch (const std::exception& error) {
        std::cout << "Error: " << error.what() << '\n';
    }
}

void runTranscription() {
    const std::string dna = readLine("Template DNA sequence: ");
    const std::string rna = Translation::transcribeTemplateDNA(dna);
    std::cout << "RNA: " << rna << '\n';
}

void runTranslation() {
    const std::string rna = readLine("RNA sequence: ");
    const std::string protein = Translation::translateRNA(rna);
    if (protein.empty()) {
        std::cout << "No start codon (AUG) found, or no translatable protein region.\n";
    } else {
        std::cout << "Protein: " << protein << '\n';
    }
}

void runTransformation() {
    const std::string dna = readLine("DNA sequence: ");
    std::cout << "\n1. Complement\n"
              << "2. Reverse\n"
              << "3. Reverse complement\n"
              << "4. Substitute\n"
              << "5. Insert\n"
              << "6. Delete\n"
              << "Choose transformation: ";
    std::string option;
    std::getline(std::cin, option);

    try {
        if (option == "1") {
            std::cout << "Result: " << Transformation::complement(dna) << '\n';
        } else if (option == "2") {
            std::cout << "Result: " << Transformation::reverse(dna) << '\n';
        } else if (option == "3") {
            std::cout << "Result: " << Transformation::reverseComplement(dna) << '\n';
        } else if (option == "4") {
            const std::string indexInput = readLine("Zero-based index: ");
            std::size_t index = 0;
            if (!parseSize(indexInput, index)) {
                std::cout << "Invalid index.\n";
                return;
            }
            const std::string base = readLine("New base (A/T/G/C): ");
            if (base.size() != 1) {
                std::cout << "Invalid base.\n";
                return;
            }
            std::cout << "Result: " << Transformation::substitute(dna, index, base[0]) << '\n';
        } else if (option == "5") {
            const std::string indexInput = readLine("Insertion index (0 to length): ");
            std::size_t index = 0;
            if (!parseSize(indexInput, index)) {
                std::cout << "Invalid index.\n";
                return;
            }
            const std::string bases = readLine("Bases to insert: ");
            std::cout << "Result: " << Transformation::insert(dna, index, bases) << '\n';
        } else if (option == "6") {
            const std::string indexInput = readLine("Deletion start index: ");
            const std::string countInput = readLine("Number of bases to delete: ");
            std::size_t index = 0;
            std::size_t count = 0;
            if (!parseSize(indexInput, index) || !parseSize(countInput, count)) {
                std::cout << "Invalid deletion parameters.\n";
                return;
            }
            std::cout << "Result: " << Transformation::erase(dna, index, count) << '\n';
        } else {
            std::cout << "Unknown transformation.\n";
        }
    } catch (const std::exception& error) {
        std::cout << "Error: " << error.what() << '\n';
    }
}


void printSequenceList(const std::vector<std::string>& sequences) {
    for (std::size_t i = 0; i < sequences.size(); ++i) {
        std::cout << (i + 1) << ". " << sequences[i]
                  << " (length = " << sequences[i].size() << ")\n";
    }
}

void runSorting() {
    std::cout << "\nSorting algorithms:\n"
              << "1. Bubble Sort\n"
              << "2. Selection Sort\n"
              << "3. Insertion Sort\n"
              << "4. Merge Sort\n"
              << "5. Quick Sort\n"
              << "Choose algorithm: ";

    std::string algorithm;
    std::getline(std::cin, algorithm);

    const std::string orderInput = readLine("Order (1 = ascending, 2 = descending): ");
    const bool ascending = orderInput != "2";

    const std::string countInput = readLine("Number of sequences: ");
    std::size_t count = 0;
    if (!parseSize(countInput, count)) {
        std::cout << "Invalid number of sequences.\n";
        return;
    }

    std::vector<std::string> sequences;
    sequences.reserve(count);
    for (std::size_t i = 0; i < count; ++i) {
        sequences.push_back(readLine("Sequence " + std::to_string(i + 1) + ": "));
    }

    std::vector<std::string> sorted;
    if (algorithm == "1") {
        sorted = Sorting::bubbleSortByLength(sequences, ascending);
    } else if (algorithm == "2") {
        sorted = Sorting::selectionSortByLength(sequences, ascending);
    } else if (algorithm == "3") {
        sorted = Sorting::insertionSortByLength(sequences, ascending);
    } else if (algorithm == "4") {
        sorted = Sorting::mergeSortByLength(sequences, ascending);
    } else if (algorithm == "5") {
        sorted = Sorting::quickSortByLength(sequences, ascending);
    } else {
        std::cout << "Unknown sorting algorithm.\n";
        return;
    }

    std::cout << "\nOriginal sequences:\n";
    printSequenceList(sequences);
    std::cout << "\nSorted by length:\n";
    printSequenceList(sorted);
}

void runComparison() {
    const std::string first = readLine("First sequence: ");
    const std::string second = readLine("Second sequence: ");
    const Comparison::ComparisonResult result =
        Comparison::compareSequences(first, second);

    std::cout << "Equal: " << (result.equal ? "Yes" : "No") << '\n';
    std::cout << "Matching positions: " << result.matchingPositions << '\n';
    std::cout << "Mismatches: " << result.mismatches << '\n';
    std::cout << "Similarity: " << result.similarityPercentage << "%\n";
    if (result.hammingDefined) {
        std::cout << "Hamming distance: " << result.hammingDistance << '\n';
    } else {
        std::cout << "Hamming distance: undefined for unequal lengths\n";
    }
}

int runTests() {
    return runAllTests();
}

} // namespace

int main() {
    while (true) {
        printMenu();
        std::string choice;
        if (!std::getline(std::cin, choice)) {
            std::cout << "\nInput closed. Exiting.\n";
            break;
        }

        if (choice == "0") {
            std::cout << "Goodbye.\n";
            break;
        }

        if (choice == "1") {
            runGeneration();
        } else if (choice == "2") {
            runSearch();
        } else if (choice == "3") {
            runGraph();
        } else if (choice == "4") {
            runReplication();
        } else if (choice == "5") {
            runTranscription();
        } else if (choice == "6") {
            runTranslation();
        } else if (choice == "7") {
            runTransformation();
        } else if (choice == "8") {
            runComparison();
        } else if (choice == "9") {
            runSorting();
        } else if (choice == "10") {
            (void)runTests();
        } else {
            std::cout << "Invalid menu option. Please choose 0-10.\n";
        }
    }

    return 0;
}
