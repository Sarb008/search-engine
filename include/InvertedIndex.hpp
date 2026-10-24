#pragma once

#include "Types.hpp"

#include <string>
#include <unordered_map>
#include <unordered_set>

class InvertedIndex {
public:
    void add_document(DocID doc_id, const std::string& content);

    [[nodiscard]]
    const PostingList* get_posting_list(const std::string& term) const;

private:
    std::unordered_map<std::string, PostingList> dictionary_;
    std::unordered_set<DocID> indexed_documents_;
};