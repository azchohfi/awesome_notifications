#pragma once

#include <string>

enum class NotificationLifeCycle {
    Foreground,
    Background,
    AppKilled
};

std::string NotificationLifeCycleToString(NotificationLifeCycle notificationLifeCycle);

constexpr std::initializer_list<NotificationLifeCycle> All_NotificationLifeCycle = { NotificationLifeCycle::Foreground, NotificationLifeCycle::Background, NotificationLifeCycle::AppKilled };