#pragma once

#include <string>

#include "../notifications/enums/MediaSource.h"
#include "../definitions.h"

class MediaUtils {
 private:
    MediaUtils();

 protected:

    static bool MatchMediaType(std::string regex, std::string mediaPath);
    static bool MatchMediaType(std::string regex, std::string mediaPath, bool filterEmpty);

 public:

    static MediaSource GetMediaSourceType(std::string mediaPath);
    static std::string CleanMediaPath(std::string mediaPath);
};
