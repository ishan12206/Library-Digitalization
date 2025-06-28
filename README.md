# 📚 Dynamic Hash Tables and Digital Libraries in C++

This project implements customizable **hash table data structures** and demonstrates their usage in two digital library systems:

- **MuskLibrary** — A library using traditional sorting and binary search
- **JGBLibrary** — A hash table–driven library using different collision resolution techniques

---

## 🔧 Features

### ✅ Hash Table Variants
- **Separate Chaining** (`Chain`)
- **Linear Probing** (`Linear`)
- **Double Hashing** (`Double`)

### ✅ Dynamic Resizing
- Tables resize automatically when the **load factor exceeds 0.5**
- Table size is determined from a global descending prime list (`get_next_size()`)

### ✅ Digital Library Interfaces
- Retrieve distinct words in a book
- Count unique words
- Search for a keyword across multiple books
- Pretty-print the book collection

---

## 📦 Structure

📁 src/
├── hash_table.h # Core hash table logic
├── digital_library.cpp # Contains MuskLibrary and JGBLibrary implementations
├── prime_generator.h # Utility to manage resizing prime numbers



---

## 🧠 Key Classes

### `DynamicHashSet` / `DynamicHashMap`
- Extend standard hash tables
- Trigger `rehash()` when needed
- Support chaining, linear probing, and double hashing

### `MuskLibrary`
- Stores books as sorted vectors of unique words
- Uses merge sort and binary search
- Optimized for read-heavy operations

### `JGBLibrary`
- Uses dynamic hash tables to store books
- Supports adding books and keyword-based searches
- Configurable with different collision resolution strategies

---

## 🛠 Example Usage

```cpp
MuskLibrary ml(
    {"Book1", "Book2"},
    {
        {"apple", "banana", "apple", "carrot"},
        {"banana", "date", "apple"}
    }
);

ml.print_books(); // Outputs sorted unique words for each book
auto words = ml.distinct_words("Book1");

JGBLibrary jl("Gates", {31, 29}); // Linear probing
jl.add_book("Code", {"hash", "table", "rehash", "key"});
auto hits = jl.search_keyword("key");
