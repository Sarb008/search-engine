#include "InvertedIndex.hpp"
#include "Tokenizer.hpp"

#include <algorithm>
#include <unordered_map>

void InvertedIndex::add_document(
    DocID doc_id,
    const std::string& content
) {

    if (indexed_documents_.contains(doc_id)) {
        return;
    }

    indexed_documents_.insert(doc_id);

    const std::vector<std::string> tokens = tokenize(content);

    std::unordered_map<std::string, uint32_t> term_frequencies;

    for (const std::string& token : tokens) {
        ++term_frequencies[token];
    }

    for (const auto& [term, frequency] : term_frequencies) {
        PostingList& postings = dictionary_[term];

        const auto position = std::lower_bound(
            postings.begin(),
            postings.end(),
            doc_id,
            [](const Posting& posting, DocID id) {
                return posting.doc_id < id;
            }
        );

        postings.insert(position, {doc_id, frequency});
    }
}

const PostingList* InvertedIndex::get_posting_list(
    const std::string& term
) const {
    const auto it = dictionary_.find(term);

    if (it == dictionary_.end()) {
        return nullptr;
    }

    return &it->second;
}