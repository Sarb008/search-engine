#pragma once

#include "InvertedIndex.hpp"
#include "Types.hpp"

#include <string>
#include <vector>

class QueryEngine {
public:
    explicit QueryEngine(const InvertedIndex& index);

    std::vector<DocID> search(const std::string& query) const;

private:
    const InvertedIndex& index_;
};
