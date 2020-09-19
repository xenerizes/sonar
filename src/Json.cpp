#include "Json.h"
#include "include/Scanner.h"
#include "include/Token.h"

namespace json {

Json::Json()
    : type(ValueType::Empty)
{ }

Json::Json(JsonValuePtr val)
    : type(val ? val->type : ValueType::Empty)
    , valuePtr(std::move(val))
{ }

bool Json::empty() const
{
    return ValueType::Empty == type;
}


} // ns json
