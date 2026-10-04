#include "ds/DNAApplications.hpp"

#include <cctype>
#include <utility>

namespace DS {

// ============================================================================
// 1. DNAHistoryManager
// ============================================================================

DNAHistoryManager::DNAHistoryManager(const std::string& initialSequence)
    : currentSequence_(initialSequence), lastAction_("Initial sequence set") {}

void DNAHistoryManager::setSequence(const std::string& sequence) {
    currentSequence_ = sequence;
    lastAction_ = "Sequence loaded";
    undoStack_.clear();
    redoStack_.clear();
}

void DNAHistoryManager::applyTransformation(
    const std::string& newSequence, const std::string& description) {
    undoStack_.push({currentSequence_, lastAction_});
    redoStack_.clear();
    currentSequence_ = newSequence;
    lastAction_ = description;
}

bool DNAHistoryManager::canUndo() const noexcept {
    return !undoStack_.isEmpty();
}

bool DNAHistoryManager::canRedo() const noexcept {
    return !redoStack_.isEmpty();
}

bool DNAHistoryManager::undo() {
    if (!canUndo()) {
        return false;
    }
    HistoryState prev = undoStack_.top();
    undoStack_.pop();

    redoStack_.push({currentSequence_, lastAction_});
    currentSequence_ = prev.sequence;
    lastAction_ = "Undo: restored state prior to '" + lastAction_ + "'";
    return true;
}

bool DNAHistoryManager::redo() {
    if (!canRedo()) {
        return false;
    }
    HistoryState next = redoStack_.top();
    redoStack_.pop();

    undoStack_.push({currentSequence_, lastAction_});
    currentSequence_ = next.sequence;
    lastAction_ = "Redo: reapplied '" + next.description + "'";
    return true;
}

const std::string& DNAHistoryManager::getCurrentSequence() const noexcept {
    return currentSequence_;
}

const std::string& DNAHistoryManager::getLastAction() const noexcept {
    return lastAction_;
}

std::size_t DNAHistoryManager::getUndoCount() const noexcept {
    return undoStack_.size();
}

std::size_t DNAHistoryManager::getRedoCount() const noexcept {
    return redoStack_.size();
}

void DNAHistoryManager::reset(const std::string& sequence) {
    setSequence(sequence);
}

// ============================================================================
// 2. RNAStructureValidator
// ============================================================================

bool RNAStructureValidator::isComplementaryRNA(char b1, char b2) {
    char c1 = static_cast<char>(std::toupper(static_cast<unsigned char>(b1)));
    char c2 = static_cast<char>(std::toupper(static_cast<unsigned char>(b2)));

    // Watson-Crick canonical pairs (A-U, G-C) or Wobble base pair (G-U)
    if ((c1 == 'A' && c2 == 'U') || (c1 == 'U' && c2 == 'A')) return true;
    if ((c1 == 'G' && c2 == 'C') || (c1 == 'C' && c2 == 'G')) return true;
    if ((c1 == 'G' && c2 == 'U') || (c1 == 'U' && c2 == 'G')) return true;
    return false;
}

RNAStructureValidator::ValidationResult RNAStructureValidator::validateDotBracket(
    const std::string& dotBracket) {
    Stack<std::size_t> stack;
    std::size_t pairCount = 0;

    for (std::size_t i = 0; i < dotBracket.size(); ++i) {
        char ch = dotBracket[i];
        if (ch == '(') {
            stack.push(i);
        } else if (ch == ')') {
            if (stack.isEmpty()) {
                return {false, "Unmatched closing bracket ')' at position " + std::to_string(i), i, pairCount};
            }
            stack.pop();
            ++pairCount;
        } else if (ch == '.') {
            // Unpaired nucleotide, valid
            continue;
        } else {
            return {false, "Invalid character '" + std::string(1, ch) + "' in dot-bracket notation", i, pairCount};
        }
    }

    if (!stack.isEmpty()) {
        std::size_t unclosedPos = stack.top();
        return {false, "Unmatched opening bracket '(' at position " + std::to_string(unclosedPos), unclosedPos, pairCount};
    }

    return {true, "Valid dot-bracket secondary structure", 0, pairCount};
}

RNAStructureValidator::ValidationResult RNAStructureValidator::validateSecondaryStructure(
    const std::string& rnaSequence, const std::string& dotBracket) {
    if (rnaSequence.size() != dotBracket.size()) {
        return {false, "RNA sequence length does not match dot-bracket notation length", 0, 0};
    }

    struct BaseNode {
        char base;
        std::size_t pos;
    };

    Stack<BaseNode> stack;
    std::size_t pairCount = 0;

    for (std::size_t i = 0; i < dotBracket.size(); ++i) {
        char ch = dotBracket[i];
        if (ch == '(') {
            stack.push({rnaSequence[i], i});
        } else if (ch == ')') {
            if (stack.isEmpty()) {
                return {false, "Unmatched closing bracket ')' at position " + std::to_string(i), i, pairCount};
            }
            BaseNode openNode = stack.top();
            stack.pop();
            ++pairCount;

            char closeBase = rnaSequence[i];
            if (!isComplementaryRNA(openNode.base, closeBase)) {
                return {false, "Non-complementary base pair (" + std::string(1, openNode.base) +
                                   "-" + std::string(1, closeBase) + ") between positions " +
                                   std::to_string(openNode.pos) + " and " + std::to_string(i),
                        i, pairCount};
            }
        } else if (ch == '.') {
            continue;
        } else {
            return {false, "Invalid character in dot-bracket structure", i, pairCount};
        }
    }

    if (!stack.isEmpty()) {
        return {false, "Unmatched opening bracket '(' at position " + std::to_string(stack.top().pos), stack.top().pos, pairCount};
    }

    return {true, "Valid complementary RNA secondary structure", 0, pairCount};
}

// ============================================================================
// 3. SlidingWindowGCScanner
// ============================================================================

DynamicArray<SlidingWindowGCScanner::WindowResult> SlidingWindowGCScanner::scanSequence(
    const std::string& sequence, std::size_t windowSize) {
    DynamicArray<WindowResult> results;
    if (windowSize == 0 || sequence.size() < windowSize) {
        return results;
    }

    Queue<char> windowQueue(windowSize + 2);
    std::size_t gcCount = 0;

    auto isGC = [](char ch) {
        char up = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
        return up == 'G' || up == 'C';
    };

    // Initialize first window
    for (std::size_t i = 0; i < windowSize; ++i) {
        char ch = sequence[i];
        if (isGC(ch)) {
            ++gcCount;
        }
        windowQueue.enqueue(ch);
    }

    double gcPct = (100.0 * static_cast<double>(gcCount)) / static_cast<double>(windowSize);
    results.push_back({0, sequence.substr(0, windowSize), gcPct});

    // Slide window in O(1) per step
    for (std::size_t i = windowSize; i < sequence.size(); ++i) {
        char leaving = windowQueue.front();
        windowQueue.dequeue();
        if (isGC(leaving)) {
            --gcCount;
        }

        char entering = sequence[i];
        windowQueue.enqueue(entering);
        if (isGC(entering)) {
            ++gcCount;
        }

        std::size_t startPos = i - windowSize + 1;
        gcPct = (100.0 * static_cast<double>(gcCount)) / static_cast<double>(windowSize);
        results.push_back({startPos, sequence.substr(startPos, windowSize), gcPct});
    }

    return results;
}

// ============================================================================
// 4. RestrictionSiteDetector
// ============================================================================

bool RestrictionSiteDetector::isPalindromicSite(const std::string& sequence) {
    if (sequence.empty() || (sequence.size() % 2 != 0)) {
        return false;
    }

    auto complement = [](char base) -> char {
        char up = static_cast<char>(std::toupper(static_cast<unsigned char>(base)));
        switch (up) {
            case 'A': return 'T';
            case 'T': return 'A';
            case 'G': return 'C';
            case 'C': return 'G';
            default: return '\0';
        }
    };

    Stack<char> complementStack;
    for (char ch : sequence) {
        char comp = complement(ch);
        if (comp == '\0') return false; // invalid base
        complementStack.push(comp);
    }

    // A reverse complement matches the sequence when popped from the stack
    for (char ch : sequence) {
        char up = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
        if (complementStack.isEmpty() || complementStack.top() != up) {
            return false;
        }
        complementStack.pop();
    }

    return true;
}

} // namespace DS
