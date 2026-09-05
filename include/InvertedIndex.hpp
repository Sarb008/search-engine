#pragma once

#include "Types.hpp"

#include <string>
#include <unordered_map>

class InvertedIndex {
public:
    void add_document(DocID doc_id, const std::string& content);

    [[nodiscard]]
    const PostingList* get_posting_list(const std::string& term) const;

private:
    std::unordered_map<std::string, PostingList> dictionary_;
};
