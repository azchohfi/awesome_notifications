#pragma once

#include <string>

enum class NotificationSource {
    Local,
    Schedule,
    Firebase,
    OneSignal
};

std::string NotificationSourceToString(NotificationSource notificationSource);