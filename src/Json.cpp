#include "Json.h"
#include "include/Scanner.h"
#include "include/Token.h"

namespace json {

Json::Json()
    : type(ValueType::Empty)
{ }

Json::Json(ValueType t, JsonValuePtr val)
    : type(t)
    , valuePtr(std::move(val))
{ }

bool Json::empty() const
{
    return ValueType::Empty == type;
}


} // ns json
