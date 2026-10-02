# DNA Sequence Analyzer — Core DSA Engineering Module

**Course:** CSE 2105 - Data Structures and Algorithms & CSE 2106 - Data Structures and Algorithms Laboratory  
**Assigned Student Responsibility:** Tree Module, Map Module, STL Module, Linked List Module  
**Standard:** Modern C++17 (Strict ISO standard, no external libraries)

---

## 1. Project & Module Overview
The **DNA Sequence Analyzer** is a multi-user genomic analytics application that processes FASTA DNA sequences, tracks user upload histories, provides sub-millisecond sequence search, computes K-mer frequencies, evaluates dynamic GC content, and feeds data into De Bruijn graph construction pipelines.

While the overall team project incorporates authentication, graphical visualization, and sequence alignment, **this module implements the foundational Data Structures and Algorithms (DSA) engine**, covering:
1. **Manual Linked Lists:** Singly, Doubly, Circular, and Cursor-based Array Linked Lists.
2. **Manual Trees:** Binary Search Tree (BST), self-balancing AVL Tree, Binary Min/Max Heaps, Binary Indexed Tree (Fenwick Tree), and educational Multi-way B-Tree / 2-3 Tree.
3. **Associative Maps:** Practical indexing via `std::unordered_map` (Hash Table), `std::map` (Red-Black Tree), and `std::multimap` with collision and load factor diagnostics.
4. **Standard Template Library (STL):** Custom functor/lambda sorting, filtering (`std::copy_if`), searching (`std::find_if`), and counting (`std::count_if`).
5. **Team Integration Interfaces:** Abstract polymorphic `ISequenceIndex` adapters (`TreeSequenceIndex`, `MapSequenceIndex`) and `KmerService` for cross-team module compatibility.

---

## 2. Directory & File Structure

```
DNA_Analyzer_My_Module/
├── main.cpp                              # Application entry point with CLI argument support
├── Makefile                              # Make build configuration
├── README.md                             # Comprehensive technical documentation
│
├── include/
│   ├── common/
│   │   ├── SequenceRecord.hpp            # Common record data structure & base counts
│   │   ├── DNAUtils.hpp                  # FASTA file parser, GC% computation, reverse complement
│   │   └── ISequenceIndex.hpp            # Polymorphic team integration interfaces
│   │
│   ├── linkedlist/
│   │   ├── SinglyLinkedList.hpp          # Generic templated Singly Linked List
│   │   ├── DoublyLinkedList.hpp          # Generic templated Doubly Linked List
│   │   ├── CircularLinkedList.hpp        # Generic templated Circular Linked List
│   │   ├── ArrayLinkedList.hpp           # Cursor/array implementation with free-list pool
│   │   ├── UploadHistory.hpp             # User upload history tracking class
│   │   └── RecentSequenceList.hpp        # Recently viewed sequences carousel
│   │
│   ├── tree/
│   │   ├── BinarySearchTree.hpp          # Binary Search Tree (BST)
│   │   ├── AVLTree.hpp                   # Self-balancing AVL Tree with rotations
│   │   ├── MinHeap.hpp                   # Array-based Binary Min-Heap
│   │   ├── MaxHeap.hpp                   # Array-based Binary Max-Heap & Top-K K-mers
│   │   ├── FenwickTree.hpp               # Binary Indexed Tree (BIT)
│   │   ├── DNARangeIndex.hpp             # 4-BIT Genomic range query engine
│   │   └── BTreeDemo.hpp                 # Multi-way search tree (2-3 / B-Tree demo)
│   │
│   ├── map/
│   │   ├── SequenceMapIndex.hpp          # Primary hash & secondary multimap indexes
│   │   └── KmerService.hpp               # K-mer counting & De Bruijn edge generation
│   │
│   ├── stl/
│   │   └── STLUtilities.hpp              # STL algorithms, lambdas, sort, filter utilities
│   │
│   └── menu/
│       └── MyModuleMenu.hpp              # Interactive console menus & automated test suite
│
├── src/
│   ├── common/
│   │   ├── SequenceRecord.cpp
│   │   ├── DNAUtils.cpp
│   │   └── ISequenceIndex.cpp
│   │
│   ├── linkedlist/
│   │   ├── UploadHistory.cpp
│   │   └── RecentSequenceList.cpp
│   │
│   ├── tree/
│   │   ├── BinarySearchTree.cpp
│   │   ├── AVLTree.cpp
│   │   ├── MinHeap.cpp
│   │   ├── MaxHeap.cpp
│   │   ├── FenwickTree.cpp
│   │   └── DNARangeIndex.cpp
│   │
│   ├── map/
│   │   ├── SequenceMapIndex.cpp
│   │   └── KmerService.cpp
│   │
│   ├── stl/
│   │   └── STLUtilities.cpp
│   │
│   └── menu/
│       └── MyModuleMenu.cpp
│
├── data/
│   ├── sample1.txt                       # Sample FASTA sequence 1 (SEQ001, 18 bp)
│   ├── sample2.txt                       # Sample FASTA sequence 2 (SEQ002, 18 bp)
│   └── sample3.txt                       # Sample FASTA sequence 3 (SEQ003, 16 bp)
│
└── reports/
    ├── my_module_report.md               # Complete academic lab report structure
    └── viva_notes.md                     # 21 comprehensive lab viva Q&A
```

---

## 3. How to Compile & Run

### 3.1 Using GCC / G++ (Windows / Linux / macOS)
To compile all source files into a standalone native binary:

```bash
# Windows (PowerShell):
$srcs = (Get-ChildItem -Path "src" -Recurse -Filter "*.cpp").FullName
g++ -std=c++17 -Wall -Wextra -O2 -static -static-libgcc -static-libstdc++ -Iinclude main.cpp $srcs -o dna_my_module.exe

# Linux / macOS (Bash):
g++ -std=c++17 -Wall -Wextra -O2 -Iinclude main.cpp src/*/*.cpp -o dna_my_module
```

### 3.2 Using Make
```bash
make          # Compiles the executable
make test     # Runs the automated test suite
make run      # Launches the interactive console menu
make clean    # Cleans build artifacts
```

### 3.3 Running the Application
- **Interactive Console Menu:**
  ```bash
  ./dna_my_module.exe
  ```
- **Automated Test Suite (Headless / CI Mode):**
  ```bash
  ./dna_my_module.exe --test
  ```

---

## 4. Interactive Console Menu Breakdown

### Main Menu
```
======================================================
    DNA SEQUENCE ANALYZER - MY ASSIGNED MODULE
  (Tree | Map | STL | Linked List | BIT Range Index)
======================================================
1. Linked List Demo
2. Tree Demo (BST, AVL, Heap, B-Tree)
3. Map Demo (std::map, unordered_map, multimap)
4. STL Demo (vector, algorithms, lambdas, sort)
5. Fenwick Tree DNA Range Demo
6. K-mer Count & Analysis Demo
7. Run All Unit & Integration Tests
8. Return to Main Project / Exit
======================================================
```

### Submenus
1. **Linked List Submenu:** Insert/delete at beginning, end, and specific positions; reverse list; display `UploadHistory` singly linked list; view `RecentSequenceList` circular linked list; compare array vs linked list memory & cache performance; demonstrate cursor-based `ArrayLinkedList`.
2. **Tree Submenu:** Insert/delete/search in manual BST; traversals (inorder, preorder, postorder); insert/delete in manual AVL Tree with dynamic rotations; display visual ASCII tree structure; range queries by length and GC content; Top-$K$ K-mers via Min/Max Heap; BST skewed degradation demo vs AVL; multi-way B-Tree demonstration.
3. **Map Submenu:** Exact search by ID via $O(1)$ `std::unordered_map`; prefix search via `std::map::lower_bound`; range queries via `std::multimap`; hash table diagnostics (`bucket_count`, `load_factor`, bucket collision chains); educational comparison table.
4. **STL Submenu:** Sort records by Name, Length, GC%, Date using custom lambda comparators; filter records by Length and GC% with `std::copy_if`; keyword search via `std::find_if`; nucleotide counting via `std::count_if`; string uppercase transformation and reversal.
5. **Fenwick Tree Submenu:** Build 4 parallel Fenwick Trees for nucleotides A, C, G, T; query counts in $[L, R]$ in $O(\log N)$ time; dynamic point mutation updates in $O(\log N)$ time; compute range GC%.
6. **K-mer Submenu:** Extract K-mers; count frequencies; extract Top-$K$ motifs; export directed De Bruijn graph edges `(prefix, suffix)` for graph module integration.

---

## 5. Sample Outputs

### 5.1 Automated Test Execution (`--test`)
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
ALL TEST CASES PASSED SUCCESSFULLY! [100%]
======================================================
```

### 5.2 AVL Visual Tree Structure & BST Degradation Demo
```
Inserting 10 strictly ascending IDs: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

Results:
  - Binary Search Tree (BST) Height : 10  (Degenerated to O(N) linked list!)
  - AVL Balanced Tree Height       : 4   (Maintains strictly O(log N) balance!)

Visual structure of AVL Tree:
--- AVL Visual Structure (Rotated 90 deg clockwise) ---
                [ID:10 H:1 BF:0]
        [ID:9 H:2 BF:-1]
[ID:8 H:3 BF:-1]
        [ID:7 H:1 BF:0]
[ID:6 H:4 BF:0]
                [ID:5 H:1 BF:0]
        [ID:4 H:2 BF:0]
                [ID:3 H:1 BF:0]
[ID:2 H:3 BF:0]
        [ID:1 H:1 BF:0]
---------------------------------------------------------
```

---

## 6. DSA Syllabus Mapping & Theoretical Rigor

| Syllabus Section | Theoretical Concept | Project Implementation |
| :--- | :--- | :--- |
| **Linked List** | Dynamic Singly, Doubly, Circular Lists | `SinglyLinkedList<T>`, `DoublyLinkedList<T>`, `CircularLinkedList<T>` |
| | Storage Management / Free-List Pool | `ArrayLinkedList` with cursor-based index allocations |
| | Head/Tail Insertions, In-place Reversal | `UploadHistory::addUpload`, `UploadHistory::reverseHistory` |
| **Tree** | Binary Search Tree Invariants & Traversals | `BinarySearchTree` (Inorder, Preorder, Postorder, Deletion 0/1/2 children) |
| | Self-Balancing Trees & Rotations | `AVLTree` (Height tracking, LL, RR, LR, RL balancing rotations) |
| | Multi-way Search Trees | `BTreeDemo` (2-3 / B-Tree degree $t=2$ splitting) |
| | Priority Queues & Complete Trees | `MinHeap` & `MaxHeap` with `heapifyUp` / `heapifyDown` |
| | Advanced Range Query Trees (Lab Week 10) | `FenwickTree` & `DNARangeIndex` with lowbit arithmetic |
| **Hashing & Map** | Hash Tables, Buckets, Load Factor | `SequenceMapIndex` (`std::unordered_map` with diagnostics) |
| | Balanced Tree Associative Indexing | `SequenceMapIndex` (`std::map`, `std::multimap` range queries) |
| **STL & Algorithms**| Modern C++ Functional Algorithms | `STLUtilities` (`std::sort`, `std::copy_if`, `std::find_if`, lambdas) |

---

## 7. Asymptotic Complexity Reference

| Structure | Operation | Average Complexity | Worst Case Complexity |
| :--- | :--- | :--- | :--- |
| **Linked List** | Head Insert / Delete | $O(1)$ | $O(1)$ |
| | Tail Insert (with tail ptr)| $O(1)$ | $O(1)$ |
| | Arbitrary Pos Insert/Del | $O(N)$ | $O(N)$ |
| **BST** | Search / Insert / Delete | $O(\log N)$ | $O(N)$ (Degenerate chain) |
| **AVL Tree** | Search / Insert / Delete | $O(\log N)$ | $O(\log N)$ (Guaranteed) |
| **Heap** | Peek Extreme Element | $O(1)$ | $O(1)$ |
| | Push / Pop | $O(\log N)$ | $O(\log N)$ |
| **Fenwick Tree** | Point Update / Range Query| $O(\log N)$ | $O(\log N)$ |
| **`std::unordered_map`**| Lookup / Insert / Delete | $O(1)$ | $O(N)$ (Collisions) |
| **`std::map`** | Lookup / Insert / Delete | $O(\log N)$ | $O(\log N)$ |
| | Range Query $[L, R]$ | $O(\log N + M)$ | $O(\log N + M)$ |

---

## 8. Integration Architecture for Team Project
Teammates integrating their modules can utilize the clean APIs defined in `include/`:
- **For Sequence Search & Storage:** Implement or query through `ISequenceIndex`:
  ```cpp
  std::unique_ptr<ISequenceIndex> index = std::make_unique<TreeSequenceIndex>();
  index->addSequence(record);
  SequenceRecord* found = index->findSequenceById(101);
  ```
- **For K-mer & De Bruijn Graph Construction:**
  ```cpp
  auto edges = KmerService::generateDeBruijnEdges(dnaSequence, 3);
  // Pass edges to Teammate's Graph Module (Adjacency List / Matrix)
  ```
- **For Range Comparison:**
  ```cpp
  DNARangeIndex rangeIdx;
  rangeIdx.build(dna);
  double localGC = rangeIdx.gcContent(1, 100);
  ```
