#pragma once

#include <string>
#include <vector>
#include <utility>
#include <memory>
#include <stdexcept>

namespace json {

enum class ValueType {
    Empty = 0,
    Null,
    String,
    Integer,
    Boolean,
    Array,
};

struct Token;

struct JsonValue {
    JsonValue() : type(ValueType::Empty) { }
    explicit JsonValue(ValueType t) : type(t) { }
    virtual ~JsonValue() = default;

    ValueType type;
};

using JsonValuePtr = std::unique_ptr<JsonValue>;

struct JsonNull : public JsonValue {
    explicit JsonNull(const Token& t);
};

struct JsonNumber : public JsonValue {
    explicit JsonNumber(const Token& t);

    int value;
};

struct JsonBoolean : public JsonValue {
    explicit JsonBoolean(const Token& t);

    bool value;
};

struct JsonString : public JsonValue {
    explicit JsonString(const Token& t);

    std::string value;
};

struct JsonArray : public JsonValue {
    JsonArray() : JsonValue(ValueType::Array) { }

    std::vector<JsonValuePtr> arr;
};

struct Json {
    Json();
    explicit Json(JsonValuePtr val);
    ~Json() = default;

    Json(Json&&) = default;
    Json& operator=(Json&&) = default;

    template<class T, typename std::enable_if<
        std::is_base_of_v<JsonValue, std::decay_t<T>>, T>::type* = nullptr>
    const std::decay_t<T>& access() const
    {
        if (empty()) {
            throw std::runtime_error("Tried to access empty data");
        }
        auto casted = dynamic_cast<std::decay_t<T>*>(valuePtr.get());
        if (!casted) {
            throw std::runtime_error("Tried to cast object of mismatched type");
        }
        return *casted;
    }

    bool empty() const;

    ValueType type;
    JsonValuePtr valuePtr;
};

} // ns json
