#pragma once

#include <flutter/encodable_value.h>

#include <string>
#include <map>
#include <optional>
#include <exception>

class MapUtils {
 private:
   static inline std::string TAG = "MapUtils";
   MapUtils() {}

 public:
   static bool IsNullOrEmptyKey(const flutter::EncodableMap& map, std::string key) {
      auto result_it = map.find(flutter::EncodableValue(key));
      if (map.empty() || result_it == map.end() || result_it->second.IsNull()) {
         return true;
      }

      if (const auto* stringValue = std::get_if<std::string>(&result_it->second)) {
         if ((*stringValue).empty()) {
               return true;
         }
      }

      if (const auto* mapValue = std::get_if<flutter::EncodableMap>(&result_it->second)) {
         if ((*mapValue).empty()) {
               return true;
         }
      }

      return false;
   }

   template<typename T>
   static std::optional<T> ExtractValue(const flutter::EncodableMap& map, std::string key)  {
      if(MapUtils::IsNullOrEmptyKey(map, key)) {
         return {};
      }

      try {
         auto result_it = map.find(flutter::EncodableValue(key));
         //auto& value = map[key];
         // Hexadecimal color conversion
         /*
         if(expectedClassName.equals("long") && value instanceof String){
            Pattern pattern = Pattern.compile("(0x|#)(\\w{2})?(\\w{6})", Pattern.CASE_INSENSITIVE);
            Matcher matcher = pattern.matcher((String) value);

            // 0x000000 hexadecimal color conversion
            if(matcher.find()) {
               String transparency = matcher.group(1);
               String textValue = (transparency == null ? "FF" : transparency) + matcher.group(2);
               Long finalValue = 0L;
               if(!StringUtils.isNullOrEmpty(textValue)){
                     finalValue += Long.parseLong(textValue, 16);
               }
               return Optional.of(expectedClass.cast(finalValue));
            }
         }
         */
         if(const auto* result = std::get_if<T>(&result_it->second)) {
            return *result;
         }
         /*if (std::holds_alternative<T>(&result_it->second)) {
            return std::get<T>(&result_it->second);
         }*/

         // if(value instanceof List && expectedClass.isArray()){
         //       switch (expectedClass.getComponentType().getSimpleName().toLowerCase()){
         //          case "double":  value = Doubles.toArray((List)value);  break;
         //          case "long":    value = Longs.toArray((List)value);   break;
         //          case "short":   value = Shorts.toArray((List)value);   break;
         //          case "integer":
         //          case "byte":
         //          case "float":   value = Floats.toArray((List)value);   break;
         //       }
         //       return Optional.of(expectedClass.cast(value));
         // }

         // if(expectedClass.isInstance(value)){
         //       return Optional.of(expectedClass.cast(value));
         // }

         // TODO REGRESSION TO PRIMITIVES. IS NOT SO NECESSARY, DUE MAPS AND GSON DO NOT USE THEN. ITS A OVERKILL SOLUTION
         /*if(expectedClass.isPrimitive()) {
               Class objectClass = value.getClass();
               if (!objectClass.isPrimitive()) {
                  Class primitiveObjectClass = (Class) objectClass.getField("TYPE").get(null);
                  if(expectedClass.equals(primitiveObjectClass)){
                     primitiveObjectClass.
                     return Optional.of(T.cast(value));
                  }
               }
         }*/
      }
      catch (std::exception&){
         //Log.d(TAG, key + " is not a type of " + Optional.class.getSimpleName());
      }

      return {};
   }

   template<typename T>
   static std::optional<T> ExtractEnumValue(const flutter::EncodableMap& map, std::string key)  {
      if(MapUtils::IsNullOrEmptyKey(map, key)) {
         return {};
      }

      try {
         auto result_it = map.find(flutter::EncodableValue(key));
         if(const auto* result = std::get_if<int>(&result_it->second)) {
            return (T)*result;
         }
      }
      catch (std::exception&){
         //Log.d(TAG, key + " is not a type of " + Optional.class.getSimpleName());
      }

      return {};
   }
};
