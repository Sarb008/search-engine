#include "PostingListOps.hpp"

#include <cstddef>

std::vector<DocID> intersect(
    const PostingList& first,
    const PostingList& second
) {
    std::vector<DocID> result;

    size_t i = 0;
    size_t j = 0;

    while (i < first.size() && j < second.size()) {
        if (first[i].doc_id == second[j].doc_id) {
            result.push_back(first[i].doc_id);
            ++i;
            ++j;
        }
        else if (first[i].doc_id < second[j].doc_id) {
            ++i;
        }
        else {
            ++j;
        }
    }

    return result;
}
