#include <string>

#include "NotificationCategory.h"

NotificationCategory NotificationCategoryFromString(std::string s) {
    if(s.compare("alarm") == 0)
        return NotificationCategory::Alarm;
    else if(s.compare("call") == 0)
        return NotificationCategory::Call;
    else if(s.compare("email") == 0)
        return NotificationCategory::Email;
    else if(s.compare("err") == 0)
        return NotificationCategory::Error;
    else if(s.compare("event") == 0)
        return NotificationCategory::Event;
    else if(s.compare("location_sharing") == 0)
        return NotificationCategory::LocalSharing;
    else if(s.compare("msg") == 0)
        return NotificationCategory::Message;
    else if(s.compare("missed_call" ) == 0)
        return NotificationCategory::MissedCall;
    else if(s.compare("navigation") == 0)
        return NotificationCategory::Navigation;
    else if(s.compare("progress") == 0)
        return NotificationCategory::Progress;
    else if(s.compare("promo") == 0)
        return NotificationCategory::Promo;
    else if(s.compare("recommendation") == 0)
        return NotificationCategory::Recommendation;
    else if(s.compare("reminder") == 0)
        return NotificationCategory::Reminder;
    else if(s.compare("service") == 0)
        return NotificationCategory::Service;
    else if(s.compare("social") == 0)
        return NotificationCategory::Social;
    else if(s.compare("status") == 0)
        return NotificationCategory::Status;
    else if(s.compare("stopwatch" ) == 0)
        return NotificationCategory::StopWatch;
    else if(s.compare("transport") == 0)
        return NotificationCategory::Transport;
    else if(s.compare("workout") == 0)
        return NotificationCategory::Workout;

    return NotificationCategory::Message; // ?
}

std::string NotificationCategoryToString(NotificationCategory notificationCategory) {
    switch(notificationCategory) {
        case NotificationCategory::Alarm:
            return "alarm";
        case NotificationCategory::Call:
            return "call";
        case NotificationCategory::Email:
            return "email";
        case NotificationCategory::Error:
            return "err";
        case NotificationCategory::Event:
            return "event";
        case NotificationCategory::LocalSharing:
            return "location_sharing";
        case NotificationCategory::Message:
            return "msg";
        case NotificationCategory::MissedCall:
            return "missed_call" ;
        case NotificationCategory::Navigation:
            return "navigation";
        case NotificationCategory::Progress:
            return "progress";
        case NotificationCategory::Promo:
            return "promo";
        case NotificationCategory::Recommendation:
            return "recommendation";
        case NotificationCategory::Reminder:
            return "reminder";
        case NotificationCategory::Service:
            return "service";
        case NotificationCategory::Social:
            return "social";
        case NotificationCategory::Status:
            return "status";
        case NotificationCategory::StopWatch:
            return "stopwatch" ;
        case NotificationCategory::Transport:
            return "transport";
        case NotificationCategory::Workout:
            return "workout";
    }

    return "";
}