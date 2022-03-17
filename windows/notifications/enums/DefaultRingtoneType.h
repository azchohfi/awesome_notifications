#pragma once

#include <string>

enum class DefaultRingtoneType {
    Ringtone,
    Notification,
    Alarm
};

std::string DefaultRingtoneTypeToString(DefaultRingtoneType defaultRingtoneType);