# DNA Sequence Analyzer

A C++ command-line application for working with DNA sequences developed for CSE 2105 / CSE 2106 (Data Structures and Algorithms Laboratory). The program provides a modular, high-throughput genomic toolkit for sequence generation, molecular transformations, string searching, De Bruijn graph construction, sorting, and core custom data structure implementations built from first principles (zero STL).

## Features

### 1. Shakil's Core Data Structures Subsystem (Custom From Scratch - Zero STL)
- **`DynamicArray<T>`**: Heap-allocated generic dynamic array with geometric resizing ($2\times$ capacity doubling), full Rule of Five support, bounds checking, and iterator support.
- **`Stack<T>`**: Zero-STL stack powering:
  - **Live DNA Mutation Undo/Redo Engine**: Interactive state history tracking substitutions, insertions, deletions, and complements.
  - **RNA Secondary Structure & Hairpin Loop Bracket Validator**: Validates dot-bracket syntax and confirms Watson-Crick ($A-U, G-C$) and Wobble ($G-U$) complementary base pairing.
  - **Palindromic Restriction Site Detection**: Stack-reversal verification of restriction enzyme recognition sites (e.g., EcoRI `GAATTC`, BamHI `GGATCC`).
- **`Queue<T>`**: Zero-STL Circular Ring Buffer queue powering:
  - **Real-Time Sliding-Window GC% Scanner**: Computes running GC percentage across genomic sequences in strict $\mathcal{O}(1)$ time per nucleotide.
  - **FIFO Pipeline Job Scheduling**: Queueing batch genomic workflows.

### 2. Molecular Biology & Transformations Subsystem
- Generate random DNA sequences with configurable length and seed
- Replicate DNA into complementary double-stranded format ($5' \rightarrow 3'$ and $3' \rightarrow 5'$)
- Transcribe template DNA to RNA
- Translate RNA to protein sequences via codon mapping (start codon AUG to stop codons)
- Genomic transformations: complement, reverse, reverse complement, point mutation, insertion, deletion

### 3. Search, Comparison & Sorting Subsystem
- KMP (Knuth-Morris-Pratt) pattern searching with $\mathcal{O}(m)$ LPS table preprocessing
- Sequence comparison: equality, matches, mismatches, percentage similarity, and Hamming distance
- Multi-algorithm length sorting: Bubble Sort, Selection Sort, Insertion Sort, Merge Sort, and Quick Sort

### 4. Assembly & Graph Analytics
- De Bruijn multigraph construction from sequence $k$-mers
- Adjacency list representation
- Breadth-First Search (BFS) and Depth-First Search (DFS) traversals

---

## Asymptotic Complexity Table (Shakil's Core Data Structures)

| Data Structure / Operation | Average Complexity | Worst-Case Complexity | Space Complexity |
| :--- | :---: | :---: | :---: |
| **`DynamicArray<T>`** | | | |
| - Access by Index (`[]`) | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ | $\mathcal{O}(N)$ |
| - Push Back (Amortized) | $\mathcal{O}(1)$ | $\mathcal{O}(N)$ (Resize) | $\mathcal{O}(1)$ aux |
| - Pop Back | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ aux |
| - Insert / Remove at Index | $\mathcal{O}(N)$ | $\mathcal{O}(N)$ | $\mathcal{O}(1)$ aux |
| **`Stack<T>`** | | | |
| - Push | $\mathcal{O}(1)$ | $\mathcal{O}(N)$ (Resize) | $\mathcal{O}(N)$ |
| - Pop / Top | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ aux |
| - Undo / Redo Transformation Step | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ | $\mathcal{O}(K)$ history |
| - RNA Dot-Bracket Validation | $\mathcal{O}(N)$ | $\mathcal{O}(N)$ | $\mathcal{O}(N)$ stack |
| **`Queue<T>` (Circular Ring Buffer)** | | | |
| - Enqueue | $\mathcal{O}(1)$ | $\mathcal{O}(N)$ (Resize) | $\mathcal{O}(N)$ |
| - Dequeue / Front | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ aux |
| - Sliding Window GC% per Base | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ | $\mathcal{O}(W)$ window |

---

## Project Structure

```
dna-sequence-analyzer/
├── include/
│   ├── ds/                       # Shakil: Custom Data Structures (Zero STL)
│   │   ├── DynamicArray.hpp      # Generic dynamic array with Rule of 5
│   │   ├── Stack.hpp             # Generic stack from scratch
│   │   ├── Queue.hpp             # Generic circular ring buffer queue
│   │   └── DNAApplications.hpp   # Undo/Redo, RNA validator, GC scanner
│   ├── menu/                     # Shakil: Hierarchical Menu System
│   │   └── AppMenu.hpp
│   ├── comparison.h              # Nadid: Sequence comparison & Hamming
│   ├── dna_generator.h           # Nadid: Random sequence generator
│   ├── graph.h                   # Nadid: De Bruijn graph, BFS, DFS
│   ├── replication.h             # Nadid: DNA replication
│   ├── searching.h               # Nadid: KMP pattern matching
│   ├── sorting.h                 # Nadid: Length sorting algorithms
│   ├── transformation.h          # Nadid: Sequence transformations
│   └── translation.h             # Nadid: Transcription & translation
├── src/
│   ├── ds/
│   │   └── DNAApplications.cpp   # Implementation of genomic applications
│   ├── menu/
│   │   └── AppMenu.cpp           # Interactive multi-tiered CLI
│   ├── comparison.cpp
│   ├── dna_generator.cpp
│   ├── graph.cpp
│   ├── main.cpp                  # Entry point delegating to AppMenu::run()
│   ├── replication.cpp
│   ├── searching.cpp
│   ├── sorting.cpp
│   ├── transformation.cpp
│   └── translation.cpp
├── tests/
│   ├── test_data.cpp
│   ├── test_data.h
│   ├── tests.cpp                 # Automated test suite (78/78 passing)
│   └── tests.h
├── CMakeLists.txt
├── Makefile
├── Dockerfile
└── docker-compose.yml
```

---

## Requirements

- CMake 3.16 or newer
- C++17-compatible compiler (e.g. GCC 9+, Clang 10+, MSVC 2019+)
- Make or Ninja generator

---

## Build

From the project root:

```powershell
cmake -S . -B build
cmake --build build
```

This compiles two executables in the `build/` directory:
- `build/dna_analyzer.exe` (Interactive CLI application)
- `build/dna_tests.exe` (Automated test suite)

---

## Run the Application

```powershell
.\build\dna_analyzer.exe
```

The application presents a categorized, multi-tiered interactive menu:
1. **Shakil's Core DSA Workbench**: DynamicArray sequence storage, Live DNA mutation with Undo/Redo, RNA secondary structure validation, Sliding-window GC% scanner, Palindromic restriction site detector.
2. **Sequence Generation & Molecular Biology**: Random sequences, double-strand replication, transcription, translation.
3. **Genome Transformations & KMP Search**: Complements, reverses, point mutations, insertions, deletions, KMP motif searching.
4. **Sequence Comparison & Multi-Algorithm Sorting**: Equality, similarity %, Hamming distance, Bubble/Selection/Insertion/Merge/Quick sort by length.
5. **De Bruijn Graph Assembly & Graph Traversal**: $k$-mer generation, adjacency list multigraph, BFS, DFS.
6. **Run Full Automated Test Suite**: Executes all 78 integrated unit tests.
0. **Exit Application**

---

## Run the Automated Test Suite

```powershell
.\build\dna_tests.exe
```

Total Test Cases: **78 Passed, 0 Failed (100% Pass Rate)**.