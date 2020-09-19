#include "gtest/gtest.h"
#include "Parser.h"

namespace test {

TEST(ParseArray, Empty) {
    auto in = "[]";
    auto parsed = json::parse(in);

    EXPECT_FALSE(parsed.empty());
    EXPECT_EQ(parsed.type, json::ValueType::Array);
    EXPECT_NO_THROW(parsed.access<json::JsonArray>());
    EXPECT_ANY_THROW(parsed.access<json::JsonString>());
    EXPECT_TRUE(parsed.access<json::JsonArray>().arr.empty());
}

} //ns test
