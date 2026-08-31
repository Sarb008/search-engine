#include "Tokenizer.hpp"

#include <gtest/gtest.h>

TEST(TokenizerTest, BasicNormalization) {
    const std::vector<std::string> expected = {
        "hello",
        "world"
    };

    EXPECT_EQ(tokenize("Hello World"), expected);
}

TEST(TokenizerTest, ConvertsToLowercase) {
    const std::vector<std::string> expected = {
        "hello",
        "world"
    };

    EXPECT_EQ(tokenize("HELLO WORLD"), expected);
}

TEST(TokenizerTest, RemovesPunctuation) {
    const std::vector<std::string> expected = {
        "hello",
        "world"
    };

    EXPECT_EQ(tokenize("Hello, World!"), expected);
}

TEST(TokenizerTest, HandlesMultipleSpaces) {
    const std::vector<std::string> expected = {
        "hello",
        "world"
    };

    EXPECT_EQ(tokenize("   Hello     World   "), expected);
}

TEST(TokenizerTest, HandlesNumbers) {
    const std::vector<std::string> expected = {
        "c",
        "20"
    };

    EXPECT_EQ(tokenize("C++20"), expected);
}

TEST(TokenizerTest, HandlesEmptyInput) {
    const std::vector<std::string> expected = {};

    EXPECT_EQ(tokenize(""), expected);
}

TEST(TokenizerTest, HandlesPunctuationOnly) {
    const std::vector<std::string> expected = {};

    EXPECT_EQ(tokenize("!!!,,,???"), expected);
}