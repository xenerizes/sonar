#include "Json.h"
#include "include/Scanner.h"
#include "include/Token.h"

namespace json {

Json::Json()
    : type(ValueType::Empty)
{ }

Json::Json(const std::string& t)
    : type(ValueType::String)
    , value(t)
{ }

Json::Json(int t)
    : type(ValueType::Integer)
    , value(t)
{ }

Json::Json(bool t)
    : type(ValueType::Boolean)
    , value(t)
{ }

Json parse(const std::string& in)
{
    Scanner scanner(in);
    auto t = scanner.getToken();
    if (!t.has_value()) return {};
    switch (t.value().type) {
        case TokenType::INT:
            try {
                auto integer = std::stoi(t.value().value);
                return Json(integer);
            } catch (std::invalid_argument&) {
                throw std::invalid_argument("Could not convert to integer: " +
                                            t.value().value);
            } catch (std::out_of_range&) {
                throw std::out_of_range("Integer out of range");
            }
        case TokenType::STR:
            return Json(t.value().value);
        case TokenType::TRUE:
            return Json(true);
        case TokenType::FALSE:
            return Json(false);
    }
    return {};
}

} // ns json
