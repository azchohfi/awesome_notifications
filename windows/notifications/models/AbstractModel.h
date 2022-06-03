#pragma once

#include <flutter/encodable_value.h>

#include <string>
#include <optional>
#include <map>
#include <memory>
#include <functional>
#include <algorithm>
#include <iostream>
#include <exception>
#include "../../utils/JsonUtils.h"
#include "../../utils/MapUtils.h"
#include "../../definitions.h"

class AbstractModel {
 public:
    virtual ~AbstractModel();

    virtual flutter::EncodableValue ToMap() const = 0;
    virtual std::string ToJson() const = 0;

    template<typename T>
    std::unique_ptr<T> OnlyFromValidMap(const flutter::EncodableMap& arguments) const {
        // Set default values
        FromMap(arguments);

        try {
            Validate();
            return std::make_unique<T>(this);
        } catch (std::exception e) {
            //e.printStackTrace();
            return nullptr;
        }
    }

    virtual void Validate() const = 0;

    virtual void FromMap(const flutter::EncodableMap& arguments) = 0;
    virtual void FromJson(const std::string& json) = 0;

 protected:

    std::string TemplateToJson() const;

    template<typename T>
    static std::optional<T> GetValueOrDefault(const flutter::EncodableMap& arguments, std::string reference) {
        auto value = MapUtils::ExtractValue<T>(arguments, reference);

        if(value)
            return value;

        return MapUtils::ExtractValue<T>(Definitions::initialValues, reference);
    }

    template<typename T>
    static T GetValueOrDefault(const flutter::EncodableMap& arguments, std::string reference, T def) {
        auto value = MapUtils::ExtractValue<T>(arguments, reference);

        if(value)
            return value.value();

        return def;
    }

    template<typename T>
    static std::optional<T> GetEnumValueOrDefault(const flutter::EncodableMap& arguments, std::string reference, std::initializer_list<T> all, std::function<std::string(T)> toString) {
        std::optional<std::string> key = MapUtils::ExtractValue<std::string>(arguments, reference);
        std::optional<T> defaultValue = MapUtils::ExtractEnumValue<T>(Definitions::initialValues, reference);
        if (!key.has_value()) {
            return defaultValue;
        }

        std::string str = key.value();
        std::transform(str.begin(), str.end(), str.begin(), [](int c) -> char { return static_cast<char>(::tolower(c)); });

        for (const auto enumValue : all) {
            std::string str2 = toString(enumValue);
            std::transform(str2.begin(), str2.end(), str2.begin(), [](int c) -> char { return static_cast<char>(::tolower(c)); });
            
            if(str.compare(str2) == 0) {
                return enumValue;
            }
        }

        return defaultValue;
    }

    AbstractModel();

};