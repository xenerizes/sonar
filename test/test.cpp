#include "gtest/gtest.h"
#include "Parser.h"

namespace test {

TEST(ParseValue, Int) {
    auto in = "10";
    auto parsed = json::parse(in);

    EXPECT_FALSE(parsed.empty());
    EXPECT_EQ(parsed.type, json::ValueType::Integer);
    EXPECT_NO_THROW(parsed.access<json::JsonNumber>());
    EXPECT_ANY_THROW(parsed.access<json::JsonString>());
    EXPECT_EQ(10, parsed.access<json::JsonNumber>().value);

    in = " 10   ";
    parsed = json::parse(in);

    EXPECT_FALSE(parsed.empty());
    EXPECT_EQ(parsed.type, json::ValueType::Integer);
    EXPECT_NO_THROW(parsed.access<json::JsonNumber>());
    EXPECT_ANY_THROW(parsed.access<json::JsonString>());
    EXPECT_EQ(10, parsed.access<json::JsonNumber>().value);
}

TEST(ParseValue, String) {
    auto in = "\"string\"";
    auto parsed = json::parse(in);

    EXPECT_FALSE(parsed.empty());
    EXPECT_EQ(parsed.type, json::ValueType::String);
    EXPECT_NO_THROW(parsed.access<json::JsonString>());
    EXPECT_ANY_THROW(parsed.access<json::JsonNumber>());
    EXPECT_EQ(std::string("string"), parsed.access<json::JsonString>().value);

    in = "   \"string\"      ";
    parsed = json::parse(in);
    EXPECT_FALSE(parsed.empty());
    EXPECT_EQ(parsed.type, json::ValueType::String);
    EXPECT_NO_THROW(parsed.access<json::JsonString>());
    EXPECT_ANY_THROW(parsed.access<json::JsonNumber>());
    EXPECT_EQ(std::string("string"), parsed.access<json::JsonString>().value);
}

TEST(ParseValue, Bool) {
    auto in = "true";
    auto parsed = json::parse(in);

    EXPECT_FALSE(parsed.empty());
    EXPECT_EQ(parsed.type, json::ValueType::Boolean);
    EXPECT_NO_THROW(parsed.access<json::JsonBoolean>());
    EXPECT_ANY_THROW(parsed.access<json::JsonString>());
    EXPECT_EQ(true, parsed.access<json::JsonBoolean>().value);

    in = "   false      ";
    parsed = json::parse(in);
    EXPECT_FALSE(parsed.empty());
    EXPECT_EQ(parsed.type, json::ValueType::Boolean);
    EXPECT_NO_THROW(parsed.access<json::JsonBoolean>());
    EXPECT_ANY_THROW(parsed.access<json::JsonString>());
    EXPECT_EQ(false, parsed.access<json::JsonBoolean>().value);
}

} // ns test
