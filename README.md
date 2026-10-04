# DNA Sequence Analyzer

A high-performance C++17 command-line genomic toolkit developed for **CSE 2105 (Data Structures & Algorithms)** and **CSE 2106 (Data Structures & Algorithms Laboratory)**. The project integrates molecular biology workflows, sequence transformations, string matching, De Bruijn assembly graphs, self-balancing search trees, prefix-sum indexed queries, and fundamental data structures implemented from first principles (**Zero STL**).

---

## Team Contributions & Project Plan

| Member | Assigned Plan Modules | Core Implementations |
| :--- | :--- | :--- |
| **Shakil** | **Array, Stack, Queue, Master Menu Design** | `DynamicArray<T>` (Rule of 5, geometric doubling), `Stack<T>` (LIFO), `Queue<T>` (Circular Ring Buffer), DNA Undo/Redo Engine, RNA Dot-Bracket Validator, Sliding-Window GC Scanner, Unified CLI Master Menu. |
| **Fahmid** | **Tree, Map, STL, Linked List** | `SinglyLinkedList<T>`, `DoublyLinkedList<T>`, `CircularLinkedList<T>`, `ArrayLinkedList<T>`, `BinarySearchTree`, `AVLTree` (4 rotations), `MinHeap`, `MaxHeap`, `FenwickTree` (BIT), `SequenceMapIndex`, `KmerService`, `STLUtilities`. |
| **Nadid** | **Graph, Searching, Sorting, Random Sequences, Transformations** | De Bruijn Multigraph (BFS/DFS), Knuth-Morris-Pratt (KMP) search, 5 sorting algorithms (Bubble, Selection, Insertion, Merge, Quick), Random DNA Generator, DNA Replication, Transcription, Translation, Sequence Comparison. |

---

## Grading Rubric Compliance: "Array, Linked List, Stack, Queue – 5 Marks"

> **Course Policy**: *"STL can be used for the graph, but for other tasks, e.g. if you use a stack, it would be better to implement it from scratch and demonstrate it. If you use STL, you may lose marks in the 'Array, Linked List, Stack, Queue – 5 marks' section."*

### Zero-STL Verification
- **Array (`DS::DynamicArray<T>`)**: Custom heap memory management (`new T[]`, `delete[]`), geometric resizing ($2\times$), full Rule of Five, bounds checking. **Zero STL.**
- **Linked List (`SinglyLinkedList`, `DoublyLinkedList`, `CircularLinkedList`, `ArrayLinkedList`)**: Custom node pointers (`Node*`), manual heap allocation, in-place reversal. **Zero STL.**
- **Stack (`DS::Stack<T>`)**: Custom dynamic stack backed by `DynamicArray<T>`, exception-safe push/pop/top. **Zero STL.**
- **Queue (`DS::Queue<T>`)**: Custom Circular Ring Buffer with modulo indexing and dynamic capacity doubling with ring unwrapping. **Zero STL.**
- **Graph (`DeBruijnGraph`)**: Uses `std::vector` and `std::queue` as explicitly allowed by the lab guidelines.

---

## Key Features & Subsystems

### 1. Shakil's Core Data Structures Subsystem (Custom From Scratch - Zero STL)
- **`DynamicArray<T>`**: Generic dynamic array with geometric capacity doubling, element insertion/removal, and pointer iterators.
- **`Stack<T>`**:
  - **Live DNA Mutation Undo/Redo Engine**: Dual-stack state rollback and replay across point mutations, insertions, deletions, and complements.
  - **RNA Secondary Structure & Hairpin Loop Validator**: Dot-bracket parser verifying canonical Watson-Crick ($A-U, G-C$) and Wobble ($G-U$) complementary base pairs.
  - **Palindromic Restriction Site Detection**: Stack-reversal verification of restriction enzyme recognition sites (EcoRI `GAATTC`, BamHI `GGATCC`).
- **`Queue<T>` (Circular Ring Buffer)**:
  - **Real-Time Sliding-Window GC% Scanner**: Computes running GC percentage in strict $\mathcal{O}(1)$ time per nucleotide.

### 2. Fahmid's Advanced DSA Subsystem
- **Linked List Subsystem**:
  - `SinglyLinkedList<T>`, `DoublyLinkedList<T>`, `CircularLinkedList<T>`, and cursor-based `ArrayLinkedList<T>`.
  - `RecentSequenceList` (MRU cache) and `UploadHistory`.
- **Tree Subsystem**:
  - `BinarySearchTree`: Pointer-based BST with insertion, 3-case deletion, and traversals.
  - `AVLTree`: Self-balancing binary tree with LL, RR, LR, RL rotations and length/GC range searches.
  - `MinHeap` & `MaxHeap`: Binary priority queues for top-$K$ motif extraction in $\mathcal{O}(N \log K)$.
  - `FenwickTree` (Binary Indexed Tree): Bitwise $\mathcal{O}(\log N)$ prefix-sum tree powering `DNARangeIndex` for sub-sequence GC% and base queries.
- **Map & STL Subsystem**:
  - `SequenceMapIndex`: Integrates `std::unordered_map` (hash table), `std::map` (ordered prefix tree), and `std::multimap` (range queries).
  - `STLUtilities`: Demonstration of modern STL algorithms (`std::sort`, `std::copy_if`, `std::transform`, `std::accumulate`).

### 3. Nadid's Molecular Biology, Transformations & Graph Subsystem
- **Sequence Generation & Replication**: Mersenne Twister PRNG DNA sequence generator, double-strand replication with $5' \rightarrow 3'$ and $3' \rightarrow 5'$ directionality formatting.
- **Transcription & Translation**: DNA $\rightarrow$ RNA transcription, standard codon mapping, translation from start codon `AUG` to stop codons (`UAA`, `UAG`, `UGA`).
- **Transformations & Comparison**: Complement, reverse, reverse-complement, substitution, insertion, deletion; Hamming distance, match count, mismatch count, and percentage similarity.
- **KMP Pattern Search**: Knuth-Morris-Pratt string matching with $\mathcal{O}(m)$ LPS table preprocessing.
- **Length Sorting Algorithms**: Bubble Sort, Selection Sort, Insertion Sort, Merge Sort, and Quick Sort (both ascending and descending).
- **De Bruijn Graph Assembly**: Multigraph construction from $(k-1)$-mer prefixes and suffixes, adjacency list representation, BFS and DFS graph traversals.

---

## Asymptotic Complexity Table

| Structure / Module | Operation | Average Complexity | Worst-Case Complexity | Space Complexity |
| :--- | :--- | :---: | :---: | :---: |
| **`DynamicArray<T>`** | Push Back (Amortized) | $\mathcal{O}(1)$ | $\mathcal{O}(N)$ (Resize) | $\mathcal{O}(1)$ aux |
| | Access by Index (`[]`) | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ aux |
| | Insert / Remove at Index | $\mathcal{O}(N)$ | $\mathcal{O}(N)$ | $\mathcal{O}(1)$ aux |
| **`Stack<T>`** | Push / Pop / Top | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ aux |
| | Undo / Redo Mutation Step | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ | $\mathcal{O}(K)$ history |
| | RNA Dot-Bracket Validation | $\mathcal{O}(N)$ | $\mathcal{O}(N)$ | $\mathcal{O}(N)$ stack |
| **`Queue<T>` (Circular)** | Enqueue / Dequeue | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ aux |
| | Sliding Window GC% per Base | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ | $\mathcal{O}(W)$ window |
| **`SinglyLinkedList<T>`** | Head/Tail Insert, Head Delete | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ aux |
| | In-place Reversal | $\mathcal{O}(N)$ | $\mathcal{O}(N)$ | $\mathcal{O}(1)$ aux |
| **`AVLTree`** | Search / Insert / Delete | $\mathcal{O}(\log N)$ | $\mathcal{O}(\log N)$ | $\mathcal{O}(1)$ aux |
| **`FenwickTree`** | Point Update & Range Sum | $\mathcal{O}(\log N)$ | $\mathcal{O}(\log N)$ | $\mathcal{O}(1)$ aux |
| **`Min/Max Heap`** | Top-K Frequent Motifs | $\mathcal{O}(N \log K)$ | $\mathcal{O}(N \log K)$ | $\mathcal{O}(K)$ aux |
| **KMP Search** | LPS Build + Text Search | $\mathcal{O}(N + M)$ | $\mathcal{O}(N + M)$ | $\mathcal{O}(M)$ aux |
| **Merge / Quick Sort** | Length Sorting | $\mathcal{O}(N \log N)$ | $\mathcal{O}(N^2)$ (Quick worst) | $\mathcal{O}(N)$ / $\mathcal{O}(\log N)$ |
| **De Bruijn Graph** | Graph Build + BFS / DFS | $\mathcal{O}(V + E)$ | $\mathcal{O}(V + E)$ | $\mathcal{O}(V)$ aux |

---

## Build & Execution Instructions

### Requirements
- CMake 3.16+
- C++17 compatible compiler (GCC 9+, Clang 10+, MSVC 2019+)

### Build
From the project root:

```powershell
cmake -S . -B build
cmake --build build
```

This compiles two executables:
- `build/dna_analyzer.exe` (Interactive Multi-Tiered Application)
- `build/dna_tests.exe` (Automated Test Suite)

---

## Running the Application

```powershell
.\build\dna_analyzer.exe
```

The application provides a unified master menu:
1. **Shakil's Core DSA Workbench**: DynamicArray, Stack Undo/Redo, RNA validator, Circular Queue GC% scanner, Palindrome detector.
2. **Fahmid's DSA Subsystem**: Linked List demos, BST & AVL tree indexing, Min/Max heaps, Fenwick range index, Maps, STL algorithms.
3. **Sequence Generation & Molecular Biology (Nadid)**: Random sequences, double-strand replication, transcription, translation.
4. **Genome Transformations & KMP Search (Nadid)**: Complements, point mutations, insertions, deletions, KMP motif matching.
5. **Sequence Comparison & Multi-Algorithm Sorting (Nadid)**: Hamming distance, similarity %, Bubble/Selection/Insertion/Merge/Quick sort.
6. **De Bruijn Graph Assembly & Graph Traversal (Nadid)**: $k$-mer generation, adjacency multigraph, BFS, DFS.
7. **Run Full Automated Test Suite**: Executes all 160 unit tests.
0. **Exit Application**

---

## Running the Automated Test Suite

```powershell
.\build\dna_tests.exe
```

**Results**: Total Test Cases: **160 Passed, 0 Failed (100% Pass Rate)**.