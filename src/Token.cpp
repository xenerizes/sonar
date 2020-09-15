#include "include/Token.h"

namespace json {

Token::Token(TokenType t, const std::string& v)
    : type(t)
    , value(v)
{ }

} // ns json
