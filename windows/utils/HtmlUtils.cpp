#include "HtmlUtils.h"

#include <windows.h>

std::wstring HtmlUtils::FromHtml(const std::wstring& html) {
    if (html.empty()) {
        return html;
    }

    auto ret = AdaptFlutterColorsToCPP(html);

    std::wstring buffer;
    buffer.reserve(ret.size());
    for(size_t pos = 0; pos != ret.size(); ++pos) {
        switch(ret[pos]) {
            case '&':  buffer.append(L"&amp;");       break;
            case '\"': buffer.append(L"&quot;");      break;
            case '\'': buffer.append(L"&apos;");      break;
            case '<':  buffer.append(L"&lt;");        break;
            case '>':  buffer.append(L"&gt;");        break;
            default:   buffer.append(&ret[pos], 1); break;
        }
    }
    return buffer;
}

std::wstring HtmlUtils::FromHtml(const std::string& html) {
    int count = MultiByteToWideChar(CP_UTF8, 0, html.c_str(), (int)html.length(), NULL, 0);
    std::wstring wstr(count, 0);
    MultiByteToWideChar(CP_UTF8, 0, html.c_str(), (int)html.length(), &wstr[0], count);

    return FromHtml(wstr);
}

std::wstring HtmlUtils::AdaptFlutterColorsToCPP(std::wstring htmlText) {
    // TODO
    /*
    if(!StringUtils.isNullOrEmpty(htmlText)){
        final String regex = "(<(\\S+\\s+)*)(color=)('|\")([^'\"]+)('|\")((\\s+[^\\s>]+)*\\/?>)";

        final Pattern pattern = Pattern.compile(regex, Pattern.MULTILINE);
        final Matcher matcher = pattern.matcher(htmlText);

        Boolean converted = false;
        StringBuffer sb = new StringBuffer();

        while (matcher.find()) {
            try {
                String beforeBody = matcher.group(1);
                String tag = matcher.group(3);
                String quoteTypeStart = matcher.group(4);
                String colorValue = matcher.group(5);
                Long parsedLog = Long.parseLong(colorValue);
                String quoteTypeEnd = matcher.group(6);
                String afterBody = matcher.group(7);
                Integer parsedInt = parsedLog.intValue();
                matcher.appendReplacement(sb, beforeBody + tag + quoteTypeStart + parsedInt.toString() + quoteTypeEnd + afterBody);
                converted = true;
            } catch (Exception e) {

            }
        }

        if(converted){
            matcher.appendTail(sb);
            return sb.toString();
        }
    }
    */
    return htmlText;
}