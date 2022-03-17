#pragma once

#include <flutter/encodable_value.h>

#include <string>

class JsonUtils {
 public:
   static flutter::EncodableMap FromJson(const std::string& jsonData);

   static std::string ToJson(const flutter::EncodableMap& model);

 private:
   JsonUtils();
};