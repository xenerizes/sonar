#pragma once

#include <string>
#include <any>
#include <utility>
#include <memory>
#include <stdexcept>

namespace json {

enum class ValueType {
    Empty = 0,
    String,
    Integer,
    Boolean,
};

struct JsonValue {
    JsonValue() : type(ValueType::Empty) { }
    explicit JsonValue(ValueType t) : type(t) { }
    virtual ~JsonValue() = default;

    ValueType type;
};

struct JsonNumber : public JsonValue {
    template <class T, typename std::enable_if<
        std::is_integral_v<std::decay_t<T>>, T>::type = 0>
    explicit JsonNumber(T in)
        : JsonValue(ValueType::Integer)
        , value(in)
    { }

    int value;
};

struct JsonBoolean : public JsonValue {
    template <class T, typename std::enable_if<
        std::is_integral_v<std::decay_t<T>>, T>::type = 0>
    explicit JsonBoolean(T in)
        : JsonValue(ValueType::Boolean)
        , value(in)
    { }

    bool value;
};

struct JsonString : public JsonValue {
    explicit JsonString(const char* in)
    : JsonValue(ValueType::String)
    , value(in)
    { }

    explicit JsonString(std::string in)
        : JsonValue(ValueType::String)
        , value(std::move(in))
    { }

    std::string value;
};

using JsonValuePtr = std::unique_ptr<JsonValue>;

struct Json {
    Json();
    Json(ValueType t, JsonValuePtr val);
    ~Json() = default;

    Json(Json&&) = default;
    Json& operator=(Json&&) = default;

    template<class T>//, std::enable_if_t<
        //std::is_base_of_v<JsonValue, std::decay_t<T>>, T> = 0>
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
