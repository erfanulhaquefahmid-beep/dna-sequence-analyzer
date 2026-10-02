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
        expect(!differentLengths.hammingDefined,
               "Hamming distance is not reported for different lengths");
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
