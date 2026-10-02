# Generic Binary Search Tree in Modern C++

A header-only, templated **key–value binary search tree** (similar in spirit to `std::map`) written from scratch in C++17, without STL containers. It covers manual memory management, the Rule of Five, STL-compatible iterators and const-correctness.

> Built for the *Efficient C++ Programming* university course (Assignment 2).

---

## Highlights

- **Generic container:** `BinarySearchTree<Key, Value>` works with any key type that supports `<` and `==`, and stores elements as `std::pair<const Key, Value>`, the same layout `std::map` uses.
- **Rule of Five:** deep-copy constructor and assignment (recursive subtree cloning), `noexcept` move constructor and move assignment (O(1) pointer transfer), self-assignment protection and leak-free destruction.
- **STL-compatible iterators:** separate `Iterator` and `ConstIterator` classes with full `iterator_traits` typedefs (`forward_iterator_tag`), so the tree works with range-based `for` loops and structured bindings (`auto [key, value] : tree`).
- **Iterative in-order traversal:** the iterators walk the tree in sorted order **without recursion and without parent pointers**. They keep an explicit stack of the left spine, which gives amortised O(1) `++` and O(h) memory.
- **Custom `Stack<T>`:** the traversal stack is a hand-written, singly-linked, templated stack that also implements the full Rule of Five (with an iterative, order-preserving deep copy).
- **Pointer-reference recursion:** `insert`, `remove` and `operator[]` take `Node*&` parameters, so the function can rewire the parent's child link directly. This removes the need for parent pointers and for special handling of the root.
- **In-place node deletion:** removing a node with two children relinks the in-order successor node itself instead of copying its key and value. This matters because the key is `const`, and it also avoids copying values that may be expensive to copy.
- **Const-correct, map-like access:**
  - `Value& operator[](key)` inserts a default-constructed value if the key is missing (like `std::map`).
  - `const Value& operator[](key) const` throws `std::out_of_range` instead of modifying the tree.
- **Defensive error handling:** dereferencing an end iterator, or calling `top()`/`pop()` on an empty stack, throws `std::out_of_range` instead of causing undefined behaviour.
- **Stream output:** `operator<<` prints the tree in sorted order, e.g. `[(3: three), (5: five), (10: ten)]`.

---

## Project structure

| File | Description |
|------|-------------|
| `binarySearchTree.h` | The `BinarySearchTree<Key, Value>` class, its `Iterator` / `ConstIterator`, and `operator<<` |
| `node.h` | Tree node: `std::pair<const Key, Value>` plus left/right child pointers |
| `stack.h` | Generic linked-list `Stack<T>` used by the iterators |
| `stackNode.h` | Stack node type |
| `main.cpp` | Demo / manual test scenarios for every feature (commented out, enable as needed) |

---

## Skills demonstrated

`C++17` · `Templates / generic programming` · `Manual memory management` · `RAII` · `Rule of Five & move semantics` · `Custom STL-style iterators` · `Data structures & algorithms` · `Const-correctness` · `Exception safety`

## Author

**Tamás Szőnyi**
