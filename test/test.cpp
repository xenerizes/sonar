#include "gtest/gtest.h"
#include "Json.h"

namespace test {

TEST(ParseValue, Int) {
    auto in = "10";
    auto parsed = json::parse(in);

    EXPECT_TRUE(parsed.value.has_value());
    EXPECT_EQ(parsed.type, json::ValueType::Integer);
    EXPECT_EQ(10, std::any_cast<int>(parsed.value));

    in = " 10   ";
    parsed = json::parse(in);

    EXPECT_TRUE(parsed.value.has_value());
    EXPECT_EQ(parsed.type, json::ValueType::Integer);
    EXPECT_EQ(10, std::any_cast<int>(parsed.value));
}

TEST(ParseValue, String) {
    auto in = "\"string\"";
    auto parsed = json::parse(in);

    EXPECT_TRUE(parsed.value.has_value());
    EXPECT_EQ(parsed.type, json::ValueType::String);
    EXPECT_TRUE(nullptr != std::any_cast<std::string>(&parsed.value));
    EXPECT_EQ(std::string("string"), std::any_cast<std::string>(parsed.value));

    in = "   \"string\"      ";
    parsed = json::parse(in);
    EXPECT_TRUE(parsed.value.has_value());
    EXPECT_EQ(parsed.type, json::ValueType::String);
    EXPECT_TRUE(nullptr != std::any_cast<std::string>(&parsed.value));
    EXPECT_EQ(std::string("string"), std::any_cast<std::string>(parsed.value));
}

TEST(ParseValue, Bool) {
    auto in = "true";
    auto parsed = json::parse(in);

    EXPECT_TRUE(parsed.value.has_value());
    EXPECT_EQ(parsed.type, json::ValueType::Boolean);
    EXPECT_TRUE(nullptr != std::any_cast<bool>(&parsed.value));
    EXPECT_EQ(true, std::any_cast<bool>(parsed.value));

    in = "   false      ";
    parsed = json::parse(in);
    EXPECT_TRUE(parsed.value.has_value());
    EXPECT_EQ(parsed.type, json::ValueType::Boolean);
    EXPECT_TRUE(nullptr != std::any_cast<bool>(&parsed.value));
    EXPECT_EQ(false, std::any_cast<bool>(parsed.value));
}

} // ns test
