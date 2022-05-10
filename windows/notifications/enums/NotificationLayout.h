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

constexpr std::initializer_list<NotificationLayout> All_NotificationLayout = { NotificationLayout::Default,
                                                                                NotificationLayout::BigPicture,
                                                                                NotificationLayout::BigText,
                                                                                NotificationLayout::Inbox,
                                                                                NotificationLayout::ProgressBar,
                                                                                NotificationLayout::Messaging,
                                                                                NotificationLayout::MessagingGroup,
                                                                                NotificationLayout::MediaPlayer,
                                                                                NotificationLayout::PhoneCall };