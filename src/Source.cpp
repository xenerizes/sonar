#include <stdexcept>

#include "include/Source.h"

namespace json {

Source::Source(const std::string& s)
    : source(s)
    , pos(0)
{ }

std::optional<char> Source::getChar()
{
    return eof() ? std::nullopt : std::optional{source[pos++]};
}

bool Source::eof() const
{
    return pos == source.length();
}

} // ns json
