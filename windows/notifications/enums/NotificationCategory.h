#pragma once

#include <string>

enum class NotificationCategory {
    Alarm,
    Call,
    Email,
    Error,
    Event,
    LocalSharing,
    Message,
    MissedCall,
    Navigation,
    Progress,
    Promo,
    Recommendation,
    Reminder,
    Service,
    Social,
    Status,
    StopWatch,
    Transport,
    Workout
};

NotificationCategory NotificationCategoryFromString(std::string s);
std::string NotificationCategoryToString(NotificationCategory notificationCategory);