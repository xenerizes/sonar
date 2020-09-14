#pragma once

#include <string>
#include <any>
#include <utility>

namespace json {

struct json {
    template <class T>
    explicit json(const T& t) : object(std::make_any<T>(t)) { }

    std::any object;
};

json parse(const std::string& in);

} // ns json
