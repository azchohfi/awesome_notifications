#include <string>
#include <algorithm>
#include <string.h>

#include "NotificationCategory.h"

NotificationCategory NotificationCategoryFromString(std::string s) {
    auto cstr = s.c_str();
    if(_stricmp(cstr, "alarm") == 0)
        return NotificationCategory::Alarm;
    else if(_stricmp(cstr, "call") == 0)
        return NotificationCategory::Call;
    else if(_stricmp(cstr, "email") == 0)
        return NotificationCategory::Email;
    else if(_stricmp(cstr, "err") == 0)
        return NotificationCategory::Error;
    else if(_stricmp(cstr, "event") == 0)
        return NotificationCategory::Event;
    else if(_stricmp(cstr, "location_sharing") == 0)
        return NotificationCategory::LocalSharing;
    else if(_stricmp(cstr, "msg") == 0)
        return NotificationCategory::Message;
    else if(_stricmp(cstr, "missed_call" ) == 0)
        return NotificationCategory::MissedCall;
    else if(_stricmp(cstr, "navigation") == 0)
        return NotificationCategory::Navigation;
    else if(_stricmp(cstr, "progress") == 0)
        return NotificationCategory::Progress;
    else if(_stricmp(cstr, "promo") == 0)
        return NotificationCategory::Promo;
    else if(_stricmp(cstr, "recommendation") == 0)
        return NotificationCategory::Recommendation;
    else if(_stricmp(cstr, "reminder") == 0)
        return NotificationCategory::Reminder;
    else if(_stricmp(cstr, "service") == 0)
        return NotificationCategory::Service;
    else if(_stricmp(cstr, "social") == 0)
        return NotificationCategory::Social;
    else if(_stricmp(cstr, "status") == 0)
        return NotificationCategory::Status;
    else if(_stricmp(cstr, "stopwatch" ) == 0)
        return NotificationCategory::StopWatch;
    else if(_stricmp(cstr, "transport") == 0)
        return NotificationCategory::Transport;
    else if(_stricmp(cstr, "workout") == 0)
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