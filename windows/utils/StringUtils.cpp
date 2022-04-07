#include "StringUtils.h"

std::string StringUtils::DigestString(const std::string& str) {
   // TODO
   return str;
}

std::wstring StringUtils::ToWString(const std::string& str){
   return std::wstring(str.begin(), str.end());
}