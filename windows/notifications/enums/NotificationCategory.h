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

constexpr std::initializer_list<NotificationCategory> All_NotificationCategory = { NotificationCategory::Alarm, 
            NotificationCategory::Call, 
            NotificationCategory::Email, 
            NotificationCategory::Error, 
            NotificationCategory::Event, 
            NotificationCategory::LocalSharing, 
            NotificationCategory::Message, 
            NotificationCategory::MissedCall, 
            NotificationCategory::Navigation, 
            NotificationCategory::Progress, 
            NotificationCategory::Promo, 
            NotificationCategory::Recommendation, 
            NotificationCategory::Reminder, 
            NotificationCategory::Service, 
            NotificationCategory::Social, 
            NotificationCategory::Status, 
            NotificationCategory::StopWatch, 
            NotificationCategory::Transport, 
            NotificationCategory::Workout };