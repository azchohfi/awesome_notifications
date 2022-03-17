#pragma once

#include <string>

enum class NotificationLayout {
    Default,
    BigPicture,
    BigText,
    Inbox,
    ProgressBar,
    Messaging,
    MessagingGroup,
    MediaPlayer,
    PhoneCall
};

std::string NotificationLayoutToString(NotificationLayout notificationLayout);