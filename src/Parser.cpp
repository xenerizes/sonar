#include "Parser.h"
#include "Scanner.h"

namespace json {

Json parse(const std::string& in)
{
    Scanner scanner(in);
    auto t = scanner.getToken();
    if (!t.has_value()) return {};
    switch (t.value().type) {
        case TokenType::INT:
            try {
                auto integer = std::stoi(t.value().value);
                return Json(ValueType::Integer, std::make_unique<JsonNumber>(integer));
            } catch (std::invalid_argument&) {
                throw std::invalid_argument("Could not convert to integer: " +
                                            t.value().value);
            } catch (std::out_of_range&) {
                throw std::out_of_range("Integer out of range");
            }
        case TokenType::STR:
            return Json(ValueType::String, std::make_unique<JsonString>(t.value().value));
        case TokenType::TRUE:
            return Json(ValueType::Boolean, std::make_unique<JsonBoolean>(true));
        case TokenType::FALSE:
            return Json(ValueType::Boolean, std::make_unique<JsonBoolean>(false));
    }
    return {};
}

} // ns json
