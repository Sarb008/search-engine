#include "InvertedIndex.hpp"
#include "QueryEngine.hpp"

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

int main() {
    const std::unordered_map<DocID, std::string> documents = {
        {1, "C++ is used for systems programming and game engines."},
        {2, "Search engines use inverted indexes for efficient retrieval."},
        {3, "Modern game engines use C++ for performance-critical systems."},
        {4, "An inverted index maps terms to the documents containing them."},
        {5, "Information retrieval systems process search queries efficiently."}
    };

    InvertedIndex index;

    for (const auto& [doc_id, content] : documents) {
        index.add_document(doc_id, content);
    }

    QueryEngine engine(index);

    std::cout << "C++ Search Engine\n";
    std::cout << "=================\n";
    std::cout << "Indexed " << documents.size() << " sample documents.\n";
    std::cout << "Enter a query to search, or type 'exit' to quit.\n\n";

    std::string query;

    while (true) {
        std::cout << "search> ";
        std::getline(std::cin, query);

        if (!std::cin) {
            break;
        }

        if (query == "exit") {
            break;
        }

        const std::vector<DocID> results = engine.search(query);

        if (results.empty()) {
            std::cout << "No matching documents.\n\n";
            continue;
        }

        std::cout << results.size() << " matching document(s):\n";

        for (DocID doc_id : results) {
            const auto it = documents.find(doc_id);

            if (it != documents.end()) {
                std::cout << "[" << doc_id << "] "
                          << it->second << '\n';
            }
        }

        std::cout << '\n';
    }

    std::cout << "Goodbye.\n";

    return 0;
}