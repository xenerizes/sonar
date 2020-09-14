#include "gtest/gtest.h"
#include "json.h"

namespace test {

TEST(Value, Int) {
    auto in = "10";
    auto parsed = json::parse(in);

    EXPECT_TRUE(parsed.object.has_value());
    EXPECT_TRUE(nullptr != std::any_cast<std::string>(&parsed.object));
}

} // ns test
