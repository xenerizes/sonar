#include "Json.h"
#include "include/Scanner.h"
#include "include/Token.h"

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
                return Json(integer);
            } catch (std::invalid_argument&) {
                throw std::invalid_argument("Could not convert to integer: " +
                                            t.value().value);
            } catch (std::out_of_range&) {
                throw std::out_of_range("Integer out of range");
            }
        case TokenType::STR:
            return Json(t.value().value);
    }
    return {};
}

} // ns json
