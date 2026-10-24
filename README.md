# C++ Search Engine

An in-memory information retrieval engine built from scratch in C++20. The project implements text normalization, an inverted index, Boolean multi-term query processing, and efficient posting-list intersection, with an interactive command-line demo and automated tests.

> **Status:** Ongoing. The current version implements the core Boolean retrieval pipeline; relevance ranking, persistent indexes, and real-file ingestion are planned future improvements.

## Features

- Tokenizes document and query text into normalized lowercase terms
- Handles punctuation, whitespace, and alphanumeric tokens
- Builds an in-memory inverted index mapping terms to posting lists
- Stores per-document term frequencies in each posting
- Maintains posting lists in sorted `DocID` order
- Prevents duplicate document IDs from being indexed more than once
- Supports single-term and multi-term Boolean AND queries
- Intersects sorted posting lists using a two-pointer algorithm
- Handles unknown terms, empty queries, repeated query terms, and punctuation-only input
- Provides an interactive command-line search demo
- Includes automated tests using GoogleTest

## How It Works

The current retrieval pipeline is:

```text
Documents
    |
    v
Tokenizer / Normalization
    |
    v
Term-Frequency Counting
    |
    v
In-Memory Inverted Index
    |
    v
Query Tokenization
    |
    v
Posting-List Lookup
    |
    v
Boolean AND Intersection
    |
    v
Matching Document IDs
```

### 1. Text Processing

Documents and queries use the same tokenizer. Alphanumeric characters are converted to lowercase, while punctuation and other non-alphanumeric characters act as token boundaries.

For example:

```text
"Search, ENGINES!"
```

becomes:

```text
["search", "engines"]
```

### 2. Inverted Index

The engine stores an inverted index using:

```cpp
std::unordered_map<std::string, PostingList>
```

Each term maps to a posting list containing the documents in which that term occurs.

A posting contains:

```cpp
struct Posting {
    DocID doc_id;
    uint32_t term_frequency;
};
```

For example, documents containing the term `cat` could produce:

```text
cat -> [{doc_id: 1, term_frequency: 2},
        {doc_id: 3, term_frequency: 1}]
```

Posting lists are kept sorted by document ID so they can be intersected efficiently.

### 3. Query Processing

Queries currently use Boolean AND semantics.

For example:

```text
game engines
```

returns only documents containing both `game` and `engines`.

The engine retrieves the posting list for each query term and repeatedly intersects the lists. If a query contains a term that is not present in the index, the result is empty.

### 4. Posting-List Intersection

Two sorted posting lists are intersected using a two-pointer algorithm.

Instead of comparing every document in one list against every document in another, each pointer only moves forward. Intersecting lists of lengths `A` and `B` therefore runs in:

```text
O(A + B)
```

This is the core algorithm used for multi-term AND queries.

## Project Structure

```text
search-engine/
|-- include/
|   |-- InvertedIndex.hpp
|   |-- PostingListOps.hpp
|   |-- QueryEngine.hpp
|   |-- Tokenizer.hpp
|   `-- Types.hpp
|
|-- src/
|   |-- InvertedIndex.cpp
|   |-- PostingListOps.cpp
|   |-- QueryEngine.cpp
|   |-- Tokenizer.cpp
|   `-- main.cpp
|
|-- tests/
|   |-- InvertedIndexTest.cpp
|   |-- PostingListOpsTest.cpp
|   |-- QueryEngineTest.cpp
|   |-- SanityTest.cpp
|   `-- TokenizerTest.cpp
|
|-- CMakeLists.txt
`-- README.md
```

## Build and Run

### Requirements

- C++20-compatible compiler
- CMake 3.20 or newer
- Git

GoogleTest is fetched automatically by CMake for the test build.

### Configure

From the project root:

```powershell
cmake -S . -B build
```

### Build

For a Visual Studio multi-configuration build:

```powershell
cmake --build build --config Debug
```

### Run

On Windows with the Visual Studio generator:

```powershell
.\build\Debug\search_engine.exe
```

## Example

The executable currently indexes a small deterministic sample corpus so the search pipeline can be demonstrated without external data files.

Example session:

```text
C++ Search Engine
=================
Indexed 5 sample documents.
Enter a query to search, or type 'exit' to quit.

search> game engines
2 matching document(s):
[1] C++ is used for systems programming and game engines.
[3] Modern game engines use C++ for performance-critical systems.

search> unicorn
No matching documents.

search> exit
Goodbye.
```

## Testing

The project uses GoogleTest and CTest.

Run the complete test suite with:

```powershell
ctest --test-dir build -C Debug --output-on-failure
```

The current suite contains **25 automated tests** covering:

- tokenization and lowercase normalization
- punctuation, whitespace, numbers, and empty input
- inverted-index construction and term frequencies
- missing-term lookup
- posting-list intersection
- single-term and multi-term queries
- case-insensitive queries
- unknown and punctuation-only queries
- documents indexed out of `DocID` order
- repeated query terms
- duplicate document-ID handling

## Technical Concepts

The project currently demonstrates:

- inverted indexes
- posting lists
- term-frequency counting
- hash-based term lookup with `std::unordered_map`
- duplicate-ID tracking with `std::unordered_set`
- sorted vector insertion
- two-pointer intersection
- Boolean information retrieval
- C++ classes and const-correctness
- CMake-based builds
- automated unit testing with GoogleTest

## Current Limitations

The current version is intentionally focused on the core retrieval engine.

- Queries use Boolean AND semantics only.
- Results are not ranked by relevance.
- Stored term frequencies are not yet used for scoring.
- Documents are currently supplied in memory; the CLI uses a built-in sample corpus.
- The index is not persisted to disk.
- Existing documents cannot currently be updated after they are indexed.
- Stop-word removal is not implemented.
- Stemming and lemmatization are not implemented.
- Phrase, OR, NOT, fuzzy, and prefix queries are not implemented.

## Future Improvements

Planned extensions may include:

- TF-IDF or BM25 relevance ranking
- loading documents from files or directories
- persistent index serialization
- document update/removal support
- richer Boolean query operators
- phrase and positional search
- performance benchmarking on larger corpora
- index compression or other storage optimizations

## Technologies

- C++20
- CMake
- GoogleTest
- CTest
- Git