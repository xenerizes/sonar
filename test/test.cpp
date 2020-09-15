#include "gtest/gtest.h"
#include "Json.h"

namespace test {

TEST(ParseValue, Int) {
    auto in = "10";
    auto parsed = json::parse(in);

    EXPECT_TRUE(parsed.object.has_value());
    EXPECT_EQ(10, std::any_cast<int>(parsed.object));
}

TEST(ParseValue, String) {
    auto in = "\"string\"";
    auto parsed = json::parse(in);

    EXPECT_TRUE(parsed.object.has_value());
    EXPECT_TRUE(nullptr != std::any_cast<std::string>(&parsed.object));
}

} // ns test
