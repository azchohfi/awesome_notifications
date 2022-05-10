#pragma once

#include <string>

enum class NotificationSource {
    Local,
    Schedule,
    Firebase,
    OneSignal
};

std::string NotificationSourceToString(NotificationSource notificationSource);

constexpr std::initializer_list<NotificationSource> All_NotificationSource = { NotificationSource::Local, NotificationSource::Schedule, NotificationSource::Firebase, NotificationSource::OneSignal };