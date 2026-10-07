# Comprehensive Lab Viva Examination Notes
## Course: CSE 2106 (Data Structures & Algorithms Laboratory)
## Module: DNA Sequence Analyzer (Tree | Map | STL | Linked List | Fenwick Tree)

---

### PART 1: LINKED LIST MODULE

#### Q1: Why use a linked list over an array?
**Answer:**
1. **Dynamic Size:** Linked lists allocate memory on demand on the heap, growing and shrinking dynamically during runtime without needing pre-allocation or costly reallocation.
2. **O(1) Insertions/Deletions at Ends:** Inserting or deleting at the beginning (or at the end if a tail pointer is maintained) takes strict $O(1)$ time because it only requires pointer manipulations. In contrast, an array requires shifting elements ($O(N)$).
3. **No Memory Reallocation Overhead:** Arrays/vectors must occasionally double their capacity and copy all existing elements to a new contiguous memory block. Linked lists never suffer from this reallocation penalty.

#### Q2: When is an array better than a linked list?
**Answer:**
1. **Random Access:** Arrays provide $O(1)$ constant-time random access via direct memory offset calculation (`base_address + index * sizeof(element)`). Linked lists require sequential traversal in $O(N)$ time.
2. **Memory Overhead:** Linked lists require 8 extra bytes per node for pointers (16 bytes in doubly linked lists) on 64-bit systems. Arrays store raw data without pointer overhead.
3. **CPU Cache Locality:** Arrays reside in contiguous memory, maximizing CPU cache line hits and spatial locality during iterations. Dynamic linked list nodes are scattered across the heap, causing frequent CPU cache misses.

#### Q3: How do you insert a node at a middle position in a singly linked list?
**Answer:**
1. Traverse to the node immediately preceding the target position (`position - 1`), say `curr`.
2. Allocate the new node: `Node* newNode = new Node(value)`.
3. Set the new node's next pointer: `newNode->next = curr->next`.
4. Update `curr`'s next pointer: `curr->next = newNode`.
5. Increment the list size counter. Time complexity is $O(N)$ for traversal, $O(1)$ for insertion.

#### Q4: How do you delete a node from a middle position?
**Answer:**
1. Traverse to the node preceding the target node (`curr`).
2. Identify the target node: `Node* target = curr->next`.
3. Bypass the target node: `curr->next = target->next`.
4. Free target node's memory: `delete target;`.
5. Decrement size. Time complexity is $O(N)$.

#### Q5: What is the time complexity of insertion at the beginning?
**Answer:**
$O(1)$ constant time for singly, doubly, and circular linked lists, as it requires only creating a node, pointing its `next` to the current `head`, and updating the `head` pointer.

#### Q6: What is the difference between Singly, Doubly, and Circular Linked Lists?
**Answer:**
- **Singly Linked List:** Each node contains data and a single pointer (`next`). Traversal is unidirectional (forward only). Memory overhead: 1 pointer per node.
- **Doubly Linked List:** Each node contains `prev` and `next` pointers. Allows bidirectional traversal (forward and backward) and $O(1)$ deletion of a node if a pointer to that node is already held. Memory overhead: 2 pointers per node.
- **Circular Linked List:** The last node's `next` pointer loops back to the first node (`head`) instead of `nullptr`. Useful for round-robin scheduling, cyclic playlist navigation, and circular sequence buffers (as implemented in `RecentSequenceList`).

#### Q7: What is the array implementation of a linked list (Cursor-based list)?
**Answer:**
Instead of dynamic memory allocation (`new`/`delete`), a static array or pool of nodes is used with parallel arrays (`data[]` and `next[]`), or an array of structs. Pointers are simulated using integer array indices:
- A `head` index points to the first active element (-1 if empty).
- A `freeHead` index manages a chain of unused slots (the "free list").
- Allocating a node pops a slot index from `freeHead`.
- Deallocating a node returns its slot index back to `freeHead`.
This eliminates heap fragmentation and demonstrates operating system storage management concepts.

---

### PART 2: TREE MODULE (BST, AVL, HEAP, BIT, B-TREE)

#### Q8: What is a Binary Search Tree (BST)?
**Answer:**
A BST is a binary tree in which every node satisfies the **Binary Search Tree Invariant**:
- All keys in the node's left subtree are strictly smaller than the node's key.
- All keys in the node's right subtree are strictly greater than the node's key.
An inorder traversal (`Left -> Root -> Right`) of a BST yields all stored keys in sorted ascending order.

#### Q9: What is the problem with a normal BST?
**Answer:**
The height of an unbalanced BST depends entirely on insertion order:
- If keys are inserted in random order, height is typically $O(\log N)$.
- If keys are inserted in sorted (ascending or descending) order, the BST degenerates into a linear chain (equivalent to a linked list). Its height becomes $O(N)$, causing search, insertion, and deletion to degrade from $O(\log N)$ to $O(N)$ worst-case time.

#### Q10: Why is an AVL Tree used and how does it guarantee balance?
**Answer:**
An AVL tree (Adelson-Velsky and Landis) is a **self-balancing Binary Search Tree**. For every node $v$, the heights of its left and right subtrees differ by at most 1:
$$\text{Balance Factor } BF(v) = \text{height}(v.left) - \text{height}(v.right) \in \{-1, 0, 1\}$$
If an insertion or deletion causes $|BF| > 1$, local tree rotations are immediately executed in $O(1)$ time to restore balance. This guarantees that the tree height remains strictly bounded by $h \le 1.44 \log_2 N$, ensuring $O(\log N)$ worst-case guarantees for search, insertion, and deletion.

#### Q11: What are the 4 AVL rotation types and when are they used?
**Answer:**
1. **Left-Left (LL) Heavy ($BF > 1$ and $BF(left) \ge 0$):** Fixed by a single **Right Rotation** around the node.
2. **Right-Right (RR) Heavy ($BF < -1$ and $BF(right) \le 0$):** Fixed by a single **Left Rotation** around the node.
3. **Left-Right (LR) Heavy ($BF > 1$ and $BF(left) < 0$):** Fixed by a **Left Rotation on the left child**, followed by a **Right Rotation on the node**.
4. **Right-Left (RL) Heavy ($BF < -1$ and $BF(right) > 0$):** Fixed by a **Right Rotation on the right child**, followed by a **Left Rotation on the node**.

#### Q12: Why is a Heap used and how does it differ from a BST?
**Answer:**
- A **Heap** is a complete binary tree that satisfies the **Heap Order Property**:
  - In a **Min-Heap**, parent $\le$ children; the minimum element is always at the root ($O(1)$ peek).
  - In a **Max-Heap**, parent $\ge$ children; the maximum element is always at the root ($O(1)$ peek).
- **Difference from BST:**
  - A BST maintains total sorted order between left and right subtrees.
  - A Heap only enforces ancestor-descendant ordering (no left vs right relationship).
  - A Heap can be stored space-efficiently inside a contiguous array (children of index $i$ are at $2i+1$ and $2i+2$) without storing explicit pointers.

#### Q13: How is a Heap used to find the Top-K frequent K-mers?
**Answer:**
To find top-$K$ frequent items out of $N$ unique elements:
1. Maintain a **Min-Heap** of capacity $K$.
2. For each element in the frequency table:
   - If heap size $< K$, push the element.
   - Else if element frequency $>$ root of min-heap, pop the root and push the new element.
3. Total time complexity is $O(N \log K)$ and space complexity is $O(K)$, which is substantially superior to sorting all $N$ elements ($O(N \log N)$) when $K \ll N$.

#### Q14: What is a Binary Indexed Tree (Fenwick Tree)?
**Answer:**
A Fenwick Tree is a data structure represented as a 1D array of size $N+1$ that maintains prefix sums of an underlying array.
- Each index $i$ stores the sum of elements in a range of length equal to its lowest set bit:
  $$\text{lowbit}(i) = i \ \& \ (-i)$$
- **Point Update:** Adding $\Delta$ to index $i$ updates all ancestors by repeatedly adding $\text{lowbit}(i)$ ($O(\log N)$).
- **Prefix Query:** Querying sum from $1$ to $i$ accumulates values by repeatedly subtracting $\text{lowbit}(i)$ ($O(\log N)$).
- **Range Query $[L, R]$:** Computed as $\text{query}(R) - \text{query}(L - 1)$ in $O(\log N)$ time.

#### Q15: Why is Fenwick Tree applied to DNA sequence analysis in our project?
**Answer:**
Genomic sequences have millions of base pairs. We construct 4 Fenwick trees for nucleotides A, C, G, and T.
This allows querying base frequencies and GC content of any arbitrary genomic window $[L, R]$ in $O(\log N)$ time and supports point mutations (single nucleotide polymorphisms) dynamically in $O(\log N)$ time without re-scanning the DNA string ($O(N)$).

#### Q16: What is a Multi-way Search Tree (2-3 Tree / B-Tree)?
**Answer:**
A B-Tree of minimum degree $t$ is a balanced multi-way search tree where:
- Every node has at most $2t - 1$ keys and at least $t - 1$ keys (except root).
- A node with $k$ keys has $k+1$ children.
- All leaves are at the exact same depth.
- **2-3 Tree:** Corresponds to a B-tree where each node contains 1 or 2 keys and has 2 or 3 children.
- **Significance:** Designed for disk storage and databases where block I/O is expensive; shallow tree depth minimizes disk seeks.

---

### PART 3: MAP, HASHING & STL MODULE

#### Q17: What is the fundamental difference between `std::map` and `std::unordered_map`?
**Answer:**
| Criteria | `std::map` | `std::unordered_map` |
| :--- | :--- | :--- |
| **Underlying Data Structure** | Self-balancing Red-Black Tree | Hash Table with Separate Chaining |
| **Search Time Complexity** | $O(\log N)$ strict | $O(1)$ average, $O(N)$ worst-case |
| **Insertion / Deletion** | $O(\log N)$ strict | $O(1)$ average, $O(N)$ worst-case |
| **Ordering** | Sorted by key (Inorder traversal) | Arbitrary / Unordered |
| **Range Queries** | Supported (`lower_bound`, `upper_bound`) | Not supported (requires full linear scan) |
| **Key Requirement** | Strict weak ordering (`operator<`) | Hash functor (`std::hash`) & `operator==` |

#### Q18: What is a Hash Table and how does collision resolution work?
**Answer:**
A hash table maps keys to bucket indices using a hash function:
$$\text{index} = \text{hash}(\text{key}) \pmod{\text{bucket\_count}}$$
When two distinct keys produce the same index, a **collision** occurs.
Common collision resolution techniques:
1. **Separate Chaining (Open Hashing):** Each bucket contains a linked list of entries that hashed to the same index (used in GCC `std::unordered_map`).
2. **Open Addressing (Closed Hashing):** All entries are stored directly in the bucket array:
   - *Linear Probing:* Check $i+1, i+2, \dots$
   - *Quadratic Probing:* Check $i+1^2, i+2^2, \dots$
   - *Double Hashing:* Step size is determined by a second hash function $h_2(k)$.

#### Q19: What is Load Factor in `std::unordered_map`?
**Answer:**
The load factor is the average number of elements per bucket:
$$\alpha = \frac{\text{size()}}{\text{bucket\_count()}}$$
When $\alpha$ exceeds `max_load_factor()` (typically 1.0), the hash table triggers **rehashing**: it allocates a larger array of buckets (usually double) and re-inserts all existing elements to prevent chains from becoming long and degrading search performance.

#### Q20: What is an Iterator in C++ STL?
**Answer:**
An iterator is an abstraction representing a pointer-like object that allows sequential or random access to elements in a container without exposing the underlying memory structure.
Categories:
- Input / Output Iterators
- Forward Iterators (e.g. `std::forward_list`)
- Bidirectional Iterators (e.g. `std::list`, `std::map`)
- Random Access Iterators (e.g. `std::vector`, raw arrays)
- Contiguous Iterators (C++20)

#### Q21: What is a Lambda Function in C++?
**Answer:**
A lambda is an anonymous, inline callable object introduced in C++11. Syntax:
`[captures](parameters) -> return_type { body }`
In our project, lambdas are extensively used with STL algorithms:
```cpp
std::sort(records.begin(), records.end(), [](const SequenceRecord& a, const SequenceRecord& b) {
    return a.gcContent < b.gcContent;
});
```
This enables expressive, modular sorting and filtering without boilerplate helper functions.
