#include "NotificationSource.h"

std::string NotificationSourceToString(NotificationSource notificationSource) {
    switch(notificationSource) {
        case NotificationSource::Local:
            return "Local";
        case NotificationSource::Schedule:
            return "Schedule";
        case NotificationSource::Firebase:
            return "Firebase";
        case NotificationSource::OneSignal:
            return "OneSignal";
    }
    
    return "Local";
}