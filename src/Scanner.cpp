#include "include/Scanner.h"
#include "include/StateImpl.h"

namespace json {

Scanner::Scanner(const std::string& s)
    : source(s)
    , state(std::make_unique<StateStart>())
{ }

std::optional<Token> Scanner::getToken()
{
    std::optional<Token> t {};
    std::string token_str;
    while (!t.has_value() && !final()) {
        t = state->parseToken(source, token_str);
        state = state->next();
    }
    return t;
}

bool Scanner::final() const
{
    return !bool(state);
}

} // ns json
