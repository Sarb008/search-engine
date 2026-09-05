#pragma once

#include "Types.hpp"

#include <vector>

std::vector<DocID> intersect(
    const PostingList& first,
    const PostingList& second
);

std::vector<DocID> intersect(
    const std::vector<DocID>& first,
    const PostingList& second
);
