#pragma once

#include <optional>
#include <string>

enum class NotificationPrivacy {

    /**
     * Notification visibility: Do not reveal any part of this notification on a secure lockscreen.
     */
    Secret,

    /**
     * Notification visibility: Show this notification on all lockscreens, but conceal sensitive or
     * private information on secure lockscreens.
     */
    Private,

    /**
     * Notification visibility: Show this notification on every lockscreens.
     */
    Public
};

std::string NotificationPrivacyToString(NotificationPrivacy notificationPrivacy);

// static int ToWindowsPrivacy(std::optional<NotificationPrivacy> importance){
//     switch (!importance ? NotificationPrivacy::Private : importance.value()){
//         case NotificationPrivacy::Secret:
//             return -1;
//             //return Notification.VISIBILITY_SECRET;
//         case NotificationPrivacy::Public:
//             return -1;
//             //return Notification.VISIBILITY_PUBLIC;
//         case NotificationPrivacy::Private:
//         default:
//             return -1;
//             //return Notification.VISIBILITY_PRIVATE;
//     }
// }