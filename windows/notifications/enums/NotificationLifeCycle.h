#pragma once

#include <string>

enum class NotificationLifeCycle {
    Foreground,
    Background,
    AppKilled
};

std::string NotificationLifeCycleToString(NotificationLifeCycle notificationLifeCycle);