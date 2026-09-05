#include <gtest/gtest.h>

#include "InvertedIndex.hpp"
#include "QueryEngine.hpp"

TEST(QueryEngineTest, FindsDocumentsForSingleTerm) {
    InvertedIndex index;

    index.add_document(1, "cat dog");
    index.add_document(2, "cat bird");
    index.add_document(3, "dog bird");
    index.add_document(4, "cat dog bird");

    QueryEngine engine(index);

    const std::vector<DocID> result = engine.search("cat");

    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 2);
    EXPECT_EQ(result[2], 4);
}

TEST(QueryEngineTest, FindsDocumentsContainingAllTerms) {
    InvertedIndex index;

    index.add_document(1, "cat dog");
    index.add_document(2, "cat bird");
    index.add_document(3, "dog bird");
    index.add_document(4, "cat dog bird");

    QueryEngine engine(index);

    const std::vector<DocID> result = engine.search("cat dog");

    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 4);
}

TEST(QueryEngineTest, ReturnsEmptyWhenTermDoesNotExist) {
    InvertedIndex index;

    index.add_document(1, "cat dog");
    index.add_document(2, "cat bird");
    index.add_document(3, "dog bird");
    index.add_document(4, "cat dog bird");

    QueryEngine engine(index);

    const std::vector<DocID> result = engine.search("cat unicorn");

    EXPECT_TRUE(result.empty());
}

TEST(QueryEngineTest, FindsDocumentsContainingAllThreeTerms) {
    InvertedIndex index;

    index.add_document(1, "cat dog");
    index.add_document(2, "cat bird");
    index.add_document(3, "dog bird");
    index.add_document(4, "cat dog bird");

    QueryEngine engine(index);

    const std::vector<DocID> result = engine.search("dog bird cat");

    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], 4);
}

TEST(QueryEngineTest, ReturnsEmptyForEmptyQuery) {
    InvertedIndex index;

    index.add_document(1, "cat dog");
    index.add_document(2, "cat bird");

    QueryEngine engine(index);

    const std::vector<DocID> result = engine.search("");

    EXPECT_TRUE(result.empty());
}

TEST(QueryEngineTest, QueryIsCaseInsensitive) {
    InvertedIndex index;

    index.add_document(1, "cat dog");
    index.add_document(2, "cat bird");
    index.add_document(3, "dog bird");

    QueryEngine engine(index);

    const std::vector<DocID> result = engine.search("CAT");

    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 2);
}

TEST(QueryEngineTest, ReturnsEmptyForPunctuationOnlyQuery) {
    InvertedIndex index;

    index.add_document(1, "cat dog");
    index.add_document(2, "cat bird");

    QueryEngine engine(index);

    const std::vector<DocID> result = engine.search("!!!");

    EXPECT_TRUE(result.empty());
}