#pragma once

#include <string>

namespace json {

enum class TokenType {
    NULLT,  // null
    STR,    // string
    INT,    // integer
    BOOL,   // boolean
    ARR,    // array
};

struct Token {
    Token(TokenType t, const std::string& v);

    TokenType type;
    std::string value;
};

} // ns json
