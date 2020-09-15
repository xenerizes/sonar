#pragma once

#include <string>
#include <optional>

namespace json {

struct Source {
    explicit Source(const std::string& s);

    std::optional<char> getChar();
    bool eof() const;

private:
    std::string source;
    size_t pos;
};

}
