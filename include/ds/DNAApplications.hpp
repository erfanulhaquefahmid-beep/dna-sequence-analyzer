#ifndef DNA_APPLICATIONS_HPP
#define DNA_APPLICATIONS_HPP

#include "DynamicArray.hpp"
#include "Stack.hpp"
#include "Queue.hpp"

#include <cstddef>
#include <string>

namespace DS {

// 1. Stack Application: Live DNA Mutation & Transformation Undo / Redo Engine
class DNAHistoryManager {
public:
    struct HistoryState {
        std::string sequence;
        std::string description;
    };

    explicit DNAHistoryManager(const std::string& initialSequence = "");

    void setSequence(const std::string& sequence);
    void applyTransformation(const std::string& newSequence, const std::string& description);

    bool canUndo() const noexcept;
    bool canRedo() const noexcept;

    bool undo();
    bool redo();

    const std::string& getCurrentSequence() const noexcept;
    const std::string& getLastAction() const noexcept;
    std::size_t getUndoCount() const noexcept;
    std::size_t getRedoCount() const noexcept;
    void reset(const std::string& sequence = "");

private:
    std::string currentSequence_;
    std::string lastAction_;
    Stack<HistoryState> undoStack_;
    Stack<HistoryState> redoStack_;
};

// 2. Stack Application: RNA Secondary Structure & Hairpin Loop Validator
class RNAStructureValidator {
public:
    struct ValidationResult {
        bool isValid;
        std::string errorMessage;
        std::size_t errorPosition;
        std::size_t basePairCount;
    };

    // Validates balanced dot-bracket notation, e.g. "((((....))))"
    static ValidationResult validateDotBracket(const std::string& dotBracket);

    // Validates that paired bases satisfy canonical Watson-Crick (A-U, G-C) or Wobble (G-U) pairing
    static ValidationResult validateSecondaryStructure(
        const std::string& rnaSequence, const std::string& dotBracket);

private:
    static bool isComplementaryRNA(char b1, char b2);
};

// 3. Queue Application: Real-time Sliding Window GC% Scanner
class SlidingWindowGCScanner {
public:
    struct WindowResult {
        std::size_t startPosition;
        std::string windowSubstr;
        double gcPercentage;
    };

    // Scans a DNA sequence in O(1) per nucleotide using custom Queue<char>
    static DynamicArray<WindowResult> scanSequence(
        const std::string& sequence, std::size_t windowSize);
};

// 4. Stack Application: Palindromic Restriction Site Detection
class RestrictionSiteDetector {
public:
    // Detects if sequence equals its reverse complement via Stack reversal
    static bool isPalindromicSite(const std::string& sequence);
};

} // namespace DS

#endif // DNA_APPLICATIONS_HPP
