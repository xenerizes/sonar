#include "Json.h"
#include "include/Scanner.h"
#include "include/Token.h"

namespace json {

JsonNull::JsonNull(const json::Token& t)
    : JsonValue(ValueType::Null)
{ }

JsonNumber::JsonNumber(const json::Token& t)
    : JsonValue(ValueType::Integer)
    , value(std::stoi(t.value))
{ }

JsonString::JsonString(const json::Token& t)
    : JsonValue(ValueType::String)
    , value(t.value)
{ }

JsonBoolean::JsonBoolean(const json::Token& t)
    : JsonValue(ValueType::Boolean)
    , value(true)
{
    if (t.value == "true") value = true;
    else if (t.value == "false") value = false;
    else throw std::invalid_argument("Unknown boolean value: " + t.value);
}

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
