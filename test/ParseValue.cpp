#include "gtest/gtest.h"
#include "Parser.h"

namespace json {
namespace test {

TEST(ParseValue, Empty) {
    auto in = "";
    auto parsed = parse(in);

    EXPECT_TRUE(parsed.empty());
    EXPECT_FALSE(parsed.valuePtr);
    EXPECT_ANY_THROW(parsed.access<JsonString>());

    in = "     \t\n    \n";
    parsed = parse(in);

    EXPECT_TRUE(parsed.empty());
    EXPECT_FALSE(parsed.valuePtr);
    EXPECT_ANY_THROW(parsed.access<JsonString>());
}

TEST(ParseValue, Null) {
    auto in = "null";
    auto parsed = parse(in);

    EXPECT_FALSE(parsed.empty());
    EXPECT_EQ(parsed.type, ValueType::Null);
    EXPECT_NO_THROW(parsed.access<JsonNull>());
    EXPECT_ANY_THROW(parsed.access<JsonString>());

    in = "     \t\nnull    \n";
    parsed = parse(in);

    EXPECT_FALSE(parsed.empty());
    EXPECT_TRUE(parsed.valuePtr);
    EXPECT_EQ(parsed.type, ValueType::Null);
    EXPECT_NO_THROW(parsed.access<JsonNull>());
    EXPECT_ANY_THROW(parsed.access<JsonString>());
}

TEST(ParseValue, Int) {
    auto in = "10";
    auto parsed = parse(in);

    EXPECT_FALSE(parsed.empty());
    EXPECT_EQ(parsed.type, ValueType::Integer);
    EXPECT_NO_THROW(parsed.access<JsonNumber>());
    EXPECT_ANY_THROW(parsed.access<JsonString>());
    EXPECT_EQ(10, parsed.access<JsonNumber>().value);

    in = "\n -10   \n\n\t\n";
    parsed = parse(in);

    EXPECT_FALSE(parsed.empty());
    EXPECT_EQ(parsed.type, ValueType::Integer);
    EXPECT_NO_THROW(parsed.access<JsonNumber>());
    EXPECT_ANY_THROW(parsed.access<JsonString>());
    EXPECT_EQ(-10, parsed.access<JsonNumber>().value);
}

TEST(ParseValue, String) {
    auto in = "\"string\"";
    auto parsed = parse(in);

    EXPECT_FALSE(parsed.empty());
    EXPECT_EQ(parsed.type, ValueType::String);
    EXPECT_NO_THROW(parsed.access<JsonString>());
    EXPECT_ANY_THROW(parsed.access<JsonNumber>());
    EXPECT_EQ(std::string("string"), parsed.access<JsonString>().value);

    in = " \n  \"string\"\n      ";
    parsed = parse(in);
    EXPECT_FALSE(parsed.empty());
    EXPECT_EQ(parsed.type, ValueType::String);
    EXPECT_NO_THROW(parsed.access<JsonString>());
    EXPECT_ANY_THROW(parsed.access<JsonNumber>());
    EXPECT_EQ(std::string("string"), parsed.access<JsonString>().value);
}

TEST(ParseValue, Bool) {
    auto in = "true";
    auto parsed = parse(in);

    EXPECT_FALSE(parsed.empty());
    EXPECT_EQ(parsed.type, ValueType::Boolean);
    EXPECT_NO_THROW(parsed.access<JsonBoolean>());
    EXPECT_ANY_THROW(parsed.access<JsonString>());
    EXPECT_EQ(true, parsed.access<JsonBoolean>().value);

    in = "\n   false\n      ";
    parsed = parse(in);

    EXPECT_FALSE(parsed.empty());
    EXPECT_EQ(parsed.type, ValueType::Boolean);
    EXPECT_NO_THROW(parsed.access<JsonBoolean>());
    EXPECT_ANY_THROW(parsed.access<JsonString>());
    EXPECT_EQ(false, parsed.access<JsonBoolean>().value);

    in = " future ";

    EXPECT_THROW(parsed = parse(in), std::invalid_argument);
}

} // ns test
} //ns json
