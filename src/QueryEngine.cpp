#include "QueryEngine.hpp"
#include "Tokenizer.hpp"
#include "PostingListOps.hpp"

QueryEngine::QueryEngine(const InvertedIndex& index)
    : index_(index) {
}

std::vector<DocID> QueryEngine::search(
    const std::string& query
) const {
    const std::vector<std::string> terms = tokenize(query);

    if (terms.empty()) {
        return {};
    }

    const PostingList* first_posting_list =
        index_.get_posting_list(terms[0]);

    if (first_posting_list == nullptr) {
        return {};
    }

    std::vector<DocID> results;

    for (const Posting& posting : *first_posting_list) {
        results.push_back(posting.doc_id);
    }

    for (size_t i = 1; i < terms.size(); ++i) {
        const PostingList* posting_list =
            index_.get_posting_list(terms[i]);

        if (posting_list == nullptr) {
            return {};
        }

        results = intersect(results, *posting_list);

        if (results.empty()) {
            return {};
        }
    }

    return results;
}
