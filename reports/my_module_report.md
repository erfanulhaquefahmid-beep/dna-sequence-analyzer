# Laboratory Project Final Report
## DNA Sequence Analyzer — Core DSA Engineering Module
**Course Code:** CSE 2105 (Data Structures and Algorithms) & CSE 2106 (Data Structures and Algorithms Laboratory)  
**Academic Term:** Fall 2026  
**Assigned Student Responsibility:** Tree Module, Map Module, STL Module, Linked List Module  

---

### 1. Cover Page Information
- **Project Title:** DNA Sequence Analyzer (High-Throughput Genomic Data Engine)
- **Module Title:** Core Indexing, Hierarchical Search, Memory Management & Analytical Subsystem
- **Language / Standard:** ISO C++17
- **Compiler Compatibility:** `g++` (GCC 16.2+ / MinGW-w64), Clang 15+, MSVC 2019+
- **Submission Date:** September 2026

---

### 2. Project Objective
The primary objective of this module is to architect, implement, and validate fundamental linear and non-linear data structures from first principles without relying on high-level container abstractions for core algorithm demonstrations. Specifically, the module demonstrates:
1. Dynamic pointer-based structures (Singly, Doubly, and Circular Linked Lists).
2. Operating system static storage simulation via Cursor-based Array Linked Lists.
3. Binary hierarchical indexing structures (Binary Search Trees and self-balancing AVL Trees).
4. Priority-driven selection systems (Binary Min-Heap and Max-Heap for Top-K frequency analysis).
5. Dynamic range query engines using Binary Indexed Trees (Fenwick Trees) for genomic prefix intervals.
6. Real-world associative indexing comparing ordered balanced trees (`std::map`, `std::multimap`) against hash tables (`std::unordered_map`).
7. Modern functional programming idioms in C++17 incorporating STL algorithms, iterators, and lambda closures.

---

### 3. Course Outcomes (CO) Addressed
- **CO1 (Theoretical Analysis):** Understand and analyze asymptotic time and space complexities ($O, \Omega, \Theta$) across diverse data structure implementations.
- **CO2 (Structure Selection & Implementation):** Select and implement appropriate linear and hierarchical structures to solve computational biological challenges (e.g. sequence indexing, K-mer frequency identification).
- **CO3 (Memory & Pointer Management):** Manage dynamic memory allocation safely without resource leakage using RAII and manual destructor cascades.
- **CO4 (Integration & Modular Design):** Design clean, object-oriented, polymorphic interfaces (`ISequenceIndex`) enabling cross-team collaboration.

---

### 4. System Overview & Architecture
The full DNA Sequence Analyzer is designed as a distributed multi-user genomic processing pipeline. Within this architecture, my assigned module serves as the **Data Access and Indexing Layer**:
```
+-------------------------------------------------------------+
|                DNA Sequence Analyzer Core                   |
+-------------------------------------------------------------+
                              |
     +------------------------+------------------------+
     |                                                 |
[Linked List Subsystem]                       [Tree & Index Subsystem]
 - SinglyLinkedList (UploadHistory)            - BinarySearchTree
 - DoublyLinkedList (Bidirectional Nav)        - AVLTree (Self-Balancing Index)
 - CircularLinkedList (Recent Carousel)        - Min/Max Heap (Top-K K-mers)
 - ArrayLinkedList (Cursor Pool)               - FenwickTree (DNA Range BIT)
     |                                                 |
     +------------------------+------------------------+
                              |
     +------------------------+------------------------+
     |                                                 |
[Associative Map Subsystem]                   [STL & Utilities Layer]
 - std::unordered_map (O(1) ID Lookup)         - STLUtilities (std::sort, copy_if)
 - std::map (Sorted Name & Prefix Index)       - DNAUtils (FASTA parser, GC calc)
 - std::multimap (Range Date & GC Queries)     - Lambda Predicates & Comparators
                              |
     +------------------------+------------------------+
                              |
                 [Unified Integration API]
                   - ISequenceIndex
                   - TreeSequenceIndex
                   - MapSequenceIndex
                   - KmerService (De Bruijn Graph Interface)
```

---

### 5. My Assigned Module Responsibilities
1. **Linked List Module:**
   - Templated generic `SinglyLinkedList<T>`, `DoublyLinkedList<T>`, and `CircularLinkedList<T>`.
   - Cursor-based `ArrayLinkedList` demonstrating static storage allocation and free-list management.
   - `UploadHistory` tracking user uploaded sequence records.
   - `RecentSequenceList` maintaining a circular buffer of recently analyzed sequences.
2. **Tree Module:**
   - Manual `BinarySearchTree` with full insertion, deletion (0, 1, 2 children), and tree traversals.
   - Manual `AVLTree` with strict balance factor invariant enforcement via Left/Right/LR/RL rotations.
   - Vector-based `MinHeap` and `MaxHeap` with `heapifyUp` and `heapifyDown` operations.
   - Optimal Top-$K$ K-mer extraction in $O(N \log K)$ time.
   - `FenwickTree` (Binary Indexed Tree) providing $O(\log N)$ point updates and prefix range queries for genomic nucleotide counting.
   - Educational multi-way search tree (`BTreeDemo`) demonstrating 2-3 / B-tree node splits.
3. **Map Module:**
   - Multi-index container `SequenceMapIndex` combining primary hash indexing (`std::unordered_map`), sorted name prefix indexing (`std::map`), and duplicate-tolerant metric range indexing (`std::multimap`).
   - Detailed diagnostics exposing hash table bucket count, load factor, and collision distribution.
4. **STL Integration Module:**
   - Comprehensive genomic record manipulation via `std::sort`, `std::copy_if`, `std::find_if`, `std::count_if`, `std::transform`, `std::reverse`, and `std::lower_bound`.

---

### 6. Data Structures Implemented

#### 6.1 Linear Structures
- **`SinglyLinkedList<T>`:** Node chaining via forward pointer. Utilized in `UploadHistory`.
- **`DoublyLinkedList<T>`:** Bidirectional chaining with `prev` and `next` pointers.
- **`CircularLinkedList<T>`:** Single tail pointer architecture where `tail->next` yields the head in $O(1)$ time. Utilized in `RecentSequenceList`.
- **`ArrayLinkedList`:** Static memory pool cursor implementation with parallel arrays `data[50]` and `next[50]`.

#### 6.2 Hierarchical Structures
- **`BinarySearchTree`:** Ordered tree keyed on `SequenceRecord::id`.
- **`AVLTree`:** Height-augmented node tree maintaining $|BF| \le 1$.
- **`MinHeap` / `MaxHeap`:** Complete binary trees stored in contiguous arrays providing $O(1)$ extreme element inspection and $O(\log N)$ updates.
- **`FenwickTree`:** Binary indexed array utilizing two's complement bitwise arithmetic (`i & -i`) to manage cumulative frequencies.
- **`BTreeDemo`:** Balanced multi-way tree of degree $t=2$ demonstrating non-binary branching.

---

### 7. Algorithms & Mathematical Mechanics

#### 7.1 AVL Tree Self-Balancing
Balance Factor calculation:
$$BF(node) = \text{height}(node.left) - \text{height}(node.right)$$
- When $BF > 1$ and $BF(node.left) \ge 0$: Single Right Rotation.
- When $BF < -1$ and $BF(node.right) \le 0$: Single Left Rotation.
- When $BF > 1$ and $BF(node.left) < 0$: Left Rotation on left child, then Right Rotation on node.
- When $BF < -1$ and $BF(node.right) > 0$: Right Rotation on right child, then Left Rotation on node.

#### 7.2 Fenwick Tree Bit Manipulation
The lowest set bit of an integer index is isolated using two's complement negation:
$$\text{lowbit}(i) = i \ \& \ (-i)$$
- **Point Update:** `while (idx <= N) { bit[idx] += delta; idx += (idx & -idx); }`
- **Prefix Sum Query:** `while (idx > 0) { sum += bit[idx]; idx -= (idx & -idx); }`
- **Range Query:** `rangeQuery(L, R) = prefixSum(R) - prefixSum(L - 1)`

#### 7.3 Top-K Selection via Min-Heap
To identify the $K$ most frequent K-mers out of $N$ unique entries:
- Maintain a Min-Heap of capacity $K$.
- Insert the first $K$ elements.
- For every remaining element $(kmer, freq)$:
  - If $freq > \text{minHeap.top().second}$, pop the root and push the new element.
- Complexity: $O(N \log K)$ time and $O(K)$ space.

---

### 8. Asymptotic Complexity Table

| Structure / Module | Operation | Average Complexity | Worst-Case Complexity | Space Complexity |
| :--- | :--- | :--- | :--- | :--- |
| **Singly Linked List** | Access by Index | $O(N)$ | $O(N)$ | $O(N)$ |
| | Insert at Head | $O(1)$ | $O(1)$ | $O(1)$ |
| | Insert at Tail (with tail ptr) | $O(1)$ | $O(1)$ | $O(1)$ |
| | Delete at Head | $O(1)$ | $O(1)$ | $O(1)$ |
| | Delete at Position | $O(N)$ | $O(N)$ | $O(1)$ |
| | Search by Value | $O(N)$ | $O(N)$ | $O(1)$ |
| **Binary Search Tree** | Search by ID | $O(\log N)$ | $O(N)$ (Degenerate chain) | $O(N)$ |
| | Insert Record | $O(\log N)$ | $O(N)$ | $O(1)$ aux |
| | Delete Record | $O(\log N)$ | $O(N)$ | $O(1)$ aux |
| | Inorder Traversal | $O(N)$ | $O(N)$ | $O(N)$ stack |
| **AVL Tree** | Search by ID | $O(\log N)$ | $O(\log N)$ (Strict) | $O(N)$ |
| | Insert Record | $O(\log N)$ | $O(\log N)$ | $O(1)$ aux |
| | Delete Record | $O(\log N)$ | $O(\log N)$ | $O(1)$ aux |
| | Rotation Step | $O(1)$ | $O(1)$ | $O(1)$ |
| **Binary Min/Max Heap** | Peek Extreme Element | $O(1)$ | $O(1)$ | $O(N)$ |
| | Push Element | $O(\log N)$ | $O(\log N)$ | $O(1)$ aux |
| | Pop Element | $O(\log N)$ | $O(\log N)$ | $O(1)$ aux |
| | Top-K K-mers (Size K) | $O(N \log K)$ | $O(N \log K)$ | $O(K)$ aux |
| **Fenwick Tree (BIT)** | Point Update | $O(\log N)$ | $O(\log N)$ | $O(N)$ |
| | Prefix Query | $O(\log N)$ | $O(\log N)$ | $O(1)$ aux |
| | Range Query $[L, R]$ | $O(\log N)$ | $O(\log N)$ | $O(1)$ aux |
| **`std::map`** | Search / Insert / Delete | $O(\log N)$ | $O(\log N)$ | $O(N)$ |
| | Prefix / Range Search | $O(\log N + M)$ | $O(\log N + M)$ | $O(M)$ output |
| **`std::unordered_map`** | Search / Insert / Delete | $O(1)$ | $O(N)$ (Hash collisions) | $O(N)$ |

---

### 9. Automated Test Verification Results
The test suite executes 82 unit, edge-case, and polymorphic integration assertions across all assigned modules:
```
======================================================
    RUNNING COMPREHENSIVE AUTOMATED TEST SUITE
======================================================
  [PASS] SLL: Empty initially
  [PASS] SLL: Insert first when empty
  [PASS] SLL: Insert last
  [PASS] SLL: Insert at middle position 1
  [PASS] SLL: Insert last when empty
  [PASS] SLL: Insert at position 0
  [PASS] SLL: Delete invalid negative position fails
  [PASS] SLL: Delete invalid out-of-bounds position fails
  [PASS] SLL: Vector matches [10, 20, 30]
  [PASS] SLL: Reversal matches [30, 20, 10]
  [PASS] SLL: Delete at middle position
  [PASS] SLL: Delete first
  [PASS] SLL: Delete last
  [PASS] SLL: Delete from empty returns false
  [PASS] DLL: Insertions size is 3
  [PASS] DLL: Order [1, 2, 3]
  [PASS] DLL: Reversal [3, 2, 1]
  [PASS] DLL: Delete middle size is 2
  [PASS] DLL: Delete until empty
  [PASS] DLL: Delete empty returns false
  [PASS] CLL: Size is 3
  [PASS] CLL: Circular elements [A, B, C]
  [PASS] CLL: Delete first gives B as head
  [PASS] RecentList: Capacity capping to 3
  [PASS] ALL: Empty initially
  [PASS] ALL: Size is 3
  [PASS] ALL: Delete at position 1
  [PASS] ALL: Delete first works
  [PASS] BST: Inorder traversal is strictly sorted
  [PASS] BST: Search existing ID 20
  [PASS] BST: Search missing ID 999
  [PASS] BST: Delete leaf node (10)
  [PASS] BST: Delete node with one child (80)
  [PASS] BST: Delete node with two children (50)
  [PASS] BST: Skewed insertion degenerates to height N (5)
  [PASS] AVL: Self-balancing maintains height <= 4 for 7 nodes
  [PASS] AVL: Search ID 4
  [PASS] AVL: Range search by length returns 4 items
  [PASS] AVL: Range search by GC returns 4 items
  [PASS] AVL: Remove ID 4
  [PASS] AVL: Height remains balanced after deletion
  [PASS] AVL: Inorder traversal remains strictly sorted
  [PASS] MinHeap: Top is lowest frequency (2)
  [PASS] MinHeap: Next top is 5
  [PASS] MaxHeap: Top is highest frequency (8)
  [PASS] BIT: Prefix sum query(3) == 7
  [PASS] BIT: Range query [2..3] == 5
  [PASS] DNA Index: Count A in [1..8] is 2
  [PASS] DNA Index: Count C in [1..8] is 2
  [PASS] DNA Index: Count G in [1..8] is 2
  [PASS] DNA Index: Count T in [1..8] is 2
  [PASS] DNA Index: GC% in [1..8] is 50.0%
  [PASS] DNA Index: Invalid range [5..2] returns 0
  [PASS] DNA Index: Negative range [-3..0] returns 0
  [PASS] DNA Index: Mutated count A is now 1
  [PASS] DNA Index: Mutated count G is now 3
  [PASS] Map: Find by ID
  [PASS] Map: Find by Exact Name 'SEQ_ONE'
  [PASS] Map: Find by Name Prefix 'SEQ'
  [PASS] Map: Find by GC Range [50..60]
  [PASS] Map: Find by Date Range
  [PASS] Map: Remove record by ID
  [PASS] Map: Internal hash table buckets > 0
  [PASS] K-mer: 'AA' counted 3 times in 'AAAA'
  [PASS] Top-K: Top k-mer is AA
  [PASS] STL: Sort by name puts 'A' first
  [PASS] STL: Sort by length puts 10 first
  [PASS] STL: Sort by GC content puts 40.0% first
  [PASS] STL: Sort by upload date puts 2026-01-01 first
  [PASS] STL: Filter by length returns 1 item
  [PASS] STL: Filter by GC finds 1 record
  [PASS] STL: Search by keyword 'A'
  [PASS] STL: Count GC > 50% is 1
  [PASS] STL: Reverse string 'ATGC' == 'CGTA'
  [PASS] STL: Transform uppercase 'atgc' == 'ATGC'
  [PASS] Integration: TreeSequenceIndex polymorphism works
  [PASS] Integration: TreeSequenceIndex searchByName
  [PASS] Integration: TreeSequenceIndex removal
  [PASS] Integration: MapSequenceIndex polymorphism works
  [PASS] Integration: MapSequenceIndex searchByName
  [PASS] Integration: MapSequenceIndex removal
  [PASS] Integration: De Bruijn graph edge generation
======================================================
TEST RESULTS: 82 / 82 PASSED.
ALL TEST CASES PASSED SUCCESSFULLY! [100%]
======================================================
```

---

### 10. Team Integration Interfaces
To interface with teammates working on Authentication, Sequence Comparison, Graph Building, and Reporting, the module exports:
1. `ISequenceIndex` interface:
   - Allows teammates to plug in either `TreeSequenceIndex` (AVL Tree-based) or `MapSequenceIndex` (STL Map/Hash-based) interchangeably.
2. `KmerService`:
   - `buildKmerCount(dna, k)`: Returns nucleotide frequency map.
   - `topKmers(counts, k)`: Returns top-K frequent motifs for biomarker analysis.
   - `generateDeBruijnEdges(dna, k)`: Directly emits directed edge pairs `(prefix, suffix)` to instantiate the teammate's Graph Module.
3. `DNARangeIndex`:
   - High-speed range evaluation utility for the sequence comparison module.

---

### 11. Limitations & Future Work
- **Limitations:** The cursor-based array linked list currently uses a static buffer of 50 elements. Dynamic expansion of the static pool can be incorporated.
- **Future Improvements:** Implement Suffix Trees and Suffix Automata for substring queries in $O(M)$ time; extend Fenwick Tree to a 2D BIT for alignment dot-plot matrix range queries.

---

### 12. Conclusion
The assigned module provides a production-grade, highly educational implementation fulfilling every requirement of the CSE 2105/2106 syllabus. Manual pointer structures verify mastery of dynamic memory management, self-balancing trees guarantee theoretical efficiency, and modern STL integration bridges academic theory with industry-grade software engineering.
