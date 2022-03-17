#include "NotificationPrivacy.h"

std::string NotificationPrivacyToString(NotificationPrivacy notificationPrivacy) {
    switch(notificationPrivacy) {
        case NotificationPrivacy::Secret:
            return "Secret";
        case NotificationPrivacy::Private:
            return "Private";
        case NotificationPrivacy::Public:
            return "Public";
    }

    return "";
}