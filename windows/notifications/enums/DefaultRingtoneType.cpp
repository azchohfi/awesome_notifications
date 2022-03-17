#include "DefaultRingtoneType.h"

std::string DefaultRingtoneTypeToString(DefaultRingtoneType defaultRingtoneType) {
    switch(defaultRingtoneType) {
        case DefaultRingtoneType::Ringtone:
            return "Ringtone";
        case DefaultRingtoneType::Notification:
            return "Notification";
        case DefaultRingtoneType::Alarm:
            return "Alarm";
    }

    return "";
}