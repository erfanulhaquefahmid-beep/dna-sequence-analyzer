#include "test_data.h"

namespace TestData {

const std::vector<std::string> dnaSequences = {
    "ATGCGATACGCTAGCTAGC",
    "AATGCGAATGCCTAG",
    "TTACCGGATTAACCGG",
    "CGTACGTAGGCTAAC",
    "ATGC"
};

const std::vector<std::string> searchPatterns = {
    "ATG",
    "GCT",
    "AAC",
    "TTT"
};

const std::vector<std::string> proteinExamples = {
    "MTEYKLVVVG",
    "MKWVTF",
    "ACDEFGHIK"
};

// Template DNA -> RNA with the requested A->U, T->A, C->G, G->C mapping.
// GTACCTTATT -> CAUGGAAUAA, which contains AUG and UAA as start/stop.
const std::string templateForTranslation = "GTACCTTATT";

const std::string graphSequence = "AATGCGAT";

} // namespace TestData
