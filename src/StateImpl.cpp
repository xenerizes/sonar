#include "include/StateImpl.h"
#include "include/Token.h"

namespace json {

StatePtr StateStart::next()
{
    return std::move(n);
}

std::optional<Token> StateStart::parseToken(Source& s, std::string& token_str)
{
    auto c = s.getChar();
    while (c.has_value() && std::isspace(c.value())) {
        c = s.getChar();
    }
    if (!c) return std::nullopt;
    switch (c.value()) {
        case '\"':
            n = std::make_unique<StateString>();
            break;
        case 't':
        case 'f':
            token_str += c.value();
            n = std::make_unique<StateBool>();
            break;
        case '-':
        default:
            token_str += c.value();
            n = std::make_unique<StateInt>();
            break;
    }
    return std::nullopt;
}

StatePtr StateFin::next()
{
    return nullptr;
}

std::optional<Token> StateFin::parseToken(json::Source& s, std::string& token_str)
{
    return std::nullopt;
}

StatePtr StateInt::next()
{
    return std::make_unique<StateFin>();
}

std::optional<Token> StateInt::parseToken(Source& s, std::string& token_str)
{
    for (auto c = s.getChar(); c.has_value() && std::isdigit(c.value()); c = s.getChar()) {
        token_str += c.value();
    }
    if (token_str.empty()) return std::nullopt;
    return Token(TokenType::INT, token_str);
}

StatePtr StateString::next()
{
    return std::make_unique<StateFin>();
}

std::optional<Token> StateString::parseToken(json::Source& s, std::string& token_str)
{
    for (auto c = s.getChar(); c.has_value() && c.value() != '\"'; c = s.getChar()) {
        token_str += c.value();
    }
    return Token(TokenType::STR, token_str);
}

StatePtr StateBool::next()
{
    return std::make_unique<StateFin>();
}

std::optional<Token> StateBool::parseToken(json::Source& s, std::string& token_str)
{
    for (auto c = s.getChar(); c.has_value() && std::isalpha(c.value()); c = s.getChar()) {
        token_str += c.value();
    }
    return Token(TokenType::BOOL, token_str);
}

} // ns json
