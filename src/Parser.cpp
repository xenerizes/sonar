#include "Parser.h"
#include "Scanner.h"

namespace json {

Json parse(const std::string& in)
{
    Scanner scanner(in);
    auto t = scanner.getToken();
    if (!t.has_value()) return {};
    switch (t.value().type) {
        case TokenType::NULLT:
            return Json(std::make_unique<JsonNull>(t.value()));
        case TokenType::INT:
            return Json(std::make_unique<JsonNumber>(t.value()));
        case TokenType::STR:
            return Json(std::make_unique<JsonString>(t.value()));
        case TokenType::BOOL:
            return Json(std::make_unique<JsonBoolean>(t.value()));
        case TokenType::ARR:
            return Json(std::make_unique<JsonArray>());
    }
    return {};
}

} // ns json
