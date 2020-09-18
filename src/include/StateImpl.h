#pragma once

#include "State.h"
#include "Source.h"

namespace json {

struct StateStart final : public State {
    std::optional<Token> parseToken(Source& s, std::string& token_str) override;
    StatePtr next() override;

private:
    StatePtr n;
};

struct StateFin final : public State {
    std::optional<Token> parseToken(Source& s, std::string& token_str) override;
    StatePtr next() override;
};

struct StateInt final : public State {
    std::optional<Token> parseToken(Source& s, std::string& token_str) override;
    StatePtr next() override;
};

struct StateString final : public State {
    std::optional<Token> parseToken(Source& s, std::string& token_str) override;
    StatePtr next() override;
};

struct StateBool final : public State {
    std::optional<Token> parseToken(Source& s, std::string& token_str) override;
    StatePtr next() override;
};

} // ns json
