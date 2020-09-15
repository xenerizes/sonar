#pragma once

#include <string>
#include <any>
#include <utility>

namespace json {

struct Json {
    Json() noexcept = default;
    template <class T>
    explicit Json(const T& t) : object(std::make_any<T>(t)) { }

    std::any object;
};

Json parse(const std::string& in);

} // ns json
