#include "MediaUtils.h"

#include <regex>

bool MediaUtils::MatchMediaType(std::string regex, std::string mediaPath){
    return MatchMediaType(regex, mediaPath, true);
}

bool MediaUtils::MatchMediaType(std::string regex, std::string mediaPath, bool filterEmpty){
    std::regex r(regex, std::regex_constants::icase);
    std::string s;
    size_t index = mediaPath.find(regex, 0);
    if (index != std::string::npos) {
        s = mediaPath.replace(index, 0, "");
    }

    return std::regex_search(mediaPath, r) && (!filterEmpty || !s.empty());
}

MediaSource MediaUtils::GetMediaSourceType(std::string mediaPath) {

    if (!mediaPath.empty()) {

        if (MatchMediaType(Definitions::MEDIA_VALID_NETWORK, mediaPath, false)) {
            return MediaSource::Network;
        }

        if (MatchMediaType(Definitions::MEDIA_VALID_FILE, mediaPath)) {
            return MediaSource::File;
        }

        if (MatchMediaType(Definitions::MEDIA_VALID_RESOURCE, mediaPath)) {
            return MediaSource::Resource;
        }

        if (MatchMediaType(Definitions::MEDIA_VALID_ASSET, mediaPath)) {
            return MediaSource::Asset;
        }

    }
    return MediaSource::Unknown;
}

std::string MediaUtils::CleanMediaPath(std::string mediaPath) {
    if (!mediaPath.empty()) {
        std::regex pattern(Definitions::MEDIA_VALID_NETWORK, std::regex_constants::icase);
        std::regex pattern2(R"(^(asset://)(.*))", std::regex_constants::icase);
        std::regex pattern3(R"(^(file://)(.*))", std::regex_constants::icase);
        std::regex pattern4(R"(^(resource://)(.*))", std::regex_constants::icase);
        std::smatch m;

        if(std::regex_search(mediaPath, pattern)) {
            return mediaPath;
        }

        if(std::regex_search(mediaPath, m, pattern2)) {
            return m[2];
        }

        if(std::regex_search(mediaPath, m, pattern3)) {
            return std::string("/") + m[2].str();
        }

        if(std::regex_search(mediaPath, m, pattern4)) {
            return m[2];
        }
    }
    return std::string();
}