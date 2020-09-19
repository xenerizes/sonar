#include "gtest/gtest.h"
#include "Parser.h"

namespace test {

TEST(ParseValue, Empty) {
    auto in = "";
    auto parsed = json::parse(in);

    EXPECT_TRUE(parsed.empty());
    EXPECT_FALSE(parsed.valuePtr);
    EXPECT_ANY_THROW(parsed.access<json::JsonString>());

    in = "     \t\n    \n";
    parsed = json::parse(in);

    EXPECT_TRUE(parsed.empty());
    EXPECT_FALSE(parsed.valuePtr);
    EXPECT_ANY_THROW(parsed.access<json::JsonString>());
}

TEST(ParseValue, Null) {
    auto in = "null";
    auto parsed = json::parse(in);

    EXPECT_FALSE(parsed.empty());
    EXPECT_EQ(parsed.type, json::ValueType::Null);
    EXPECT_NO_THROW(parsed.access<json::JsonNull>());
    EXPECT_ANY_THROW(parsed.access<json::JsonString>());

    in = "     \t\nnull    \n";
    parsed = json::parse(in);

    EXPECT_FALSE(parsed.empty());
    EXPECT_TRUE(parsed.valuePtr);
    EXPECT_EQ(parsed.type, json::ValueType::Null);
    EXPECT_NO_THROW(parsed.access<json::JsonNull>());
    EXPECT_ANY_THROW(parsed.access<json::JsonString>());
}

TEST(ParseValue, Int) {
    auto in = "10";
    auto parsed = json::parse(in);

    EXPECT_FALSE(parsed.empty());
    EXPECT_EQ(parsed.type, json::ValueType::Integer);
    EXPECT_NO_THROW(parsed.access<json::JsonNumber>());
    EXPECT_ANY_THROW(parsed.access<json::JsonString>());
    EXPECT_EQ(10, parsed.access<json::JsonNumber>().value);

    in = "\n -10   \n\n\t\n";
    parsed = json::parse(in);

    EXPECT_FALSE(parsed.empty());
    EXPECT_EQ(parsed.type, json::ValueType::Integer);
    EXPECT_NO_THROW(parsed.access<json::JsonNumber>());
    EXPECT_ANY_THROW(parsed.access<json::JsonString>());
    EXPECT_EQ(-10, parsed.access<json::JsonNumber>().value);
}

TEST(ParseValue, String) {
    auto in = "\"string\"";
    auto parsed = json::parse(in);

    EXPECT_FALSE(parsed.empty());
    EXPECT_EQ(parsed.type, json::ValueType::String);
    EXPECT_NO_THROW(parsed.access<json::JsonString>());
    EXPECT_ANY_THROW(parsed.access<json::JsonNumber>());
    EXPECT_EQ(std::string("string"), parsed.access<json::JsonString>().value);

    in = " \n  \"string\"\n      ";
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

    in = "\n   false\n      ";
    parsed = json::parse(in);

    EXPECT_FALSE(parsed.empty());
    EXPECT_EQ(parsed.type, json::ValueType::Boolean);
    EXPECT_NO_THROW(parsed.access<json::JsonBoolean>());
    EXPECT_ANY_THROW(parsed.access<json::JsonString>());
    EXPECT_EQ(false, parsed.access<json::JsonBoolean>().value);

    in = " future ";

    EXPECT_THROW(parsed = json::parse(in), std::invalid_argument);
}

} // ns test
