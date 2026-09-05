#pragma once

#include <cstdint>
#include <vector>

using DocID = uint32_t;

struct Posting {
    DocID doc_id;
    uint32_t term_frequency;
};

using PostingList = std::vector<Posting>;
