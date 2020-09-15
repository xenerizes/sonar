#pragma once

#include <memory>

#include "State.h"
#include "Token.h"
#include "Source.h"

namespace json {

struct Scanner {
    explicit Scanner(const std::string& source);

    std::optional<Token> getToken();
    bool final() const;

private:
    Source source;
    StatePtr state;
};

} // ns json
