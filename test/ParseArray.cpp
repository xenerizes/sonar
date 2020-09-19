#include "gtest/gtest.h"
#include "Parser.h"

namespace json {
namespace test {

TEST(ParseArray, Empty) {
    auto in = "[]";
    auto parsed = parse(in);

    EXPECT_FALSE(parsed.empty());
    EXPECT_EQ(parsed.type, ValueType::Array);
    EXPECT_NO_THROW(parsed.access<JsonArray>());
    EXPECT_ANY_THROW(parsed.access<JsonString>());
    EXPECT_TRUE(parsed.access<JsonArray>().arr.empty());
}

} // ns test
} // ns json
