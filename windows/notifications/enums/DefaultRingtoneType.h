#pragma once

#include <string>

enum class DefaultRingtoneType {
    Ringtone,
    Notification,
    Alarm
};

std::string DefaultRingtoneTypeToString(DefaultRingtoneType defaultRingtoneType);

constexpr std::initializer_list<DefaultRingtoneType> All_DefaultRingtoneType = { DefaultRingtoneType::Ringtone, DefaultRingtoneType::Notification, DefaultRingtoneType::Alarm };