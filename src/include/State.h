#pragma once

#include <memory>

#include "Token.h"
#include "Source.h"

namespace json {

struct State;
using StatePtr = std::unique_ptr<State>;

struct State {
    virtual std::optional<Token> parseToken(Source& source, std::string& token_str) = 0;
    virtual StatePtr next() = 0;
};

} // ns json
