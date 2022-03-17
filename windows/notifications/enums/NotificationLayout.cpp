#include "NotificationLayout.h"

std::string NotificationLayoutToString(NotificationLayout notificationLayout) {
    switch(notificationLayout) {
        case NotificationLayout::Default:
            return "Default";
        case NotificationLayout::BigPicture:
            return "BigPicture";
        case NotificationLayout::BigText:
            return "BigText";
        case NotificationLayout::Inbox:
            return "Inbox";
        case NotificationLayout::ProgressBar:
            return "ProgressBar";
        case NotificationLayout::Messaging:
            return "Messaging";
        case NotificationLayout::MessagingGroup:
            return "MessagingGroup";
        case NotificationLayout::MediaPlayer:
            return "MediaPlayer";
        case NotificationLayout::PhoneCall:
            return "PhoneCall";
    }
    
    return "Default";
}