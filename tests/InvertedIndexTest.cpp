#include <gtest/gtest.h>

#include "InvertedIndex.hpp"

TEST(InvertedIndexTest, AddsSingleDocument) {
    InvertedIndex index;

    index.add_document(1, "cat dog cat");

    const PostingList* cat_postings = index.get_posting_list("cat");

    ASSERT_NE(cat_postings, nullptr);
    ASSERT_EQ(cat_postings->size(), 1);

    EXPECT_EQ((*cat_postings)[0].doc_id, 1);
    EXPECT_EQ((*cat_postings)[0].term_frequency, 2);
}

TEST(InvertedIndexTest, AddsMultipleDocuments) {
    InvertedIndex index;

    index.add_document(1, "cat dog cat");
    index.add_document(2, "dog bird");
    index.add_document(3, "cat bird");

    const PostingList* cat_postings = index.get_posting_list("cat");

    ASSERT_NE(cat_postings, nullptr);
    ASSERT_EQ(cat_postings->size(), 2);

    EXPECT_EQ((*cat_postings)[0].doc_id, 1);
    EXPECT_EQ((*cat_postings)[0].term_frequency, 2);

    EXPECT_EQ((*cat_postings)[1].doc_id, 3);
    EXPECT_EQ((*cat_postings)[1].term_frequency, 1);
}

TEST(InvertedIndexTest, ReturnsNullForMissingTerm) {
    InvertedIndex index;

    index.add_document(1, "cat dog");

    const PostingList* postings = index.get_posting_list("elephant");

    EXPECT_EQ(postings, nullptr);
}
