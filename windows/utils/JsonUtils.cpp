#include <flutter/encodable_value.h>

#include <string>

#include "JsonUtils.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

flutter::EncodableMap JsonUtils::FromJson(const std::string& jsonData) {
    //flutter::EncodableMap ret;
    return json::parse(jsonData);
    //return ret;
    /*
    Gson gson = new Gson();
    Type type = new TypeToken<Map<String, Object>>(){}.getType();
    return gson.fromJson(jsonData, type);
    */
}

std::string JsonUtils::ToJson(const flutter::EncodableMap& model) {
    //Gson gson = new Gson();
    //return gson.toJson(model);
    return "";
}

JsonUtils::JsonUtils() {
}