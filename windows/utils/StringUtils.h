#pragma once

#include <string>

class StringUtils {
 public:
    static std::string DigestString(const std::string& str);
    static std::wstring ToWString(const std::string& str);

 private:
    StringUtils();
};