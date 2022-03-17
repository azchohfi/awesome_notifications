#include "NotificationLifeCycle.h"

std::string NotificationLifeCycleToString(NotificationLifeCycle notificationLifeCycle) {
    switch(notificationLifeCycle) {
        case NotificationLifeCycle::Foreground:
            return "Foreground";
    case NotificationLifeCycle::Background:
        return "Background";
    case NotificationLifeCycle::AppKilled:
        return "AppKilled";
    }
    
    return "Foreground";
}