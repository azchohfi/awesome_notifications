#pragma once

#include <string>

class HtmlUtils {
 public:
    static std::wstring FromHtml(const std::wstring& html);
    static std::wstring FromHtml(const std::string& html);

    static std::wstring AdaptFlutterColorsToCPP(std::wstring htmlText);

 private:
    HtmlUtils();
};