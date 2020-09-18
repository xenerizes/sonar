#pragma once

#include <string>
#include <any>
#include <utility>

namespace json {

enum class ValueType {
    Empty = 0,
    String,
    Integer,
    Boolean,
};

struct Json {
    Json();

    explicit Json(const std::string& t);
    explicit Json(int t);
    explicit Json(bool t);

    ValueType type;
    std::any value;
};

Json parse(const std::string& in);

} // ns json
