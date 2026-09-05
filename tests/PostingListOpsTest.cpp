#include <gtest/gtest.h>

#include "PostingListOps.hpp"

TEST(PostingListOpsTest, FindsCommonDocuments) {
    PostingList first = {
        {1, 2},
        {3, 1},
        {7, 4},
        {10, 1}
    };

    PostingList second = {
        {1, 1},
        {2, 3},
        {7, 2},
        {8, 1}
    };

    const std::vector<DocID> result = intersect(first, second);

    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 7);
}

TEST(PostingListOpsTest, ReturnsEmptyWhenThereIsNoOverlap) {
    PostingList first = {
        {1, 1},
        {3, 2},
        {5, 1}
    };

    PostingList second = {
        {2, 1},
        {4, 1},
        {6, 3}
    };

    const std::vector<DocID> result = intersect(first, second);

    EXPECT_TRUE(result.empty());
}

TEST(PostingListOpsTest, FindsAllDocumentsWhenListsAreIdentical) {
    PostingList first = {
        {1, 2},
        {3, 1},
        {5, 4}
    };

    PostingList second = {
        {1, 7},
        {3, 2},
        {5, 1}
    };

    const std::vector<DocID> result = intersect(first, second);

    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 3);
    EXPECT_EQ(result[2], 5);
}

TEST(PostingListOpsTest, HandlesEmptyList) {
    PostingList first = {};

    PostingList second = {
        {1, 1},
        {2, 2},
        {3, 1}
    };

    const std::vector<DocID> result = intersect(first, second);

    EXPECT_TRUE(result.empty());
}
