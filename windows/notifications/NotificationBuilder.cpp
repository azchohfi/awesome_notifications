#include "NotificationBuilder.h"

#include "../utils/IntegerUtils.h"

winrt::Microsoft::Windows::AppNotifications::AppNotification NotificationBuilder::CreateNotification(const NotificationModel& notificationModel) {

    NotificationChannelModel channelModel;
    /*
    NotificationChannelModel channelModel = ChannelManager::GetChannelByKey(notificationModel.content->channelKey);
    if(channelModel == null)
        throw AwesomeNotificationException("Channel '" + notificationModel.content->channelKey + "' does not exist or is disabled");
    */

    if (notificationModel.content->id < 0)
        notificationModel.content->id = IntegerUtils::GenerateNextRandomId();

    notificationModel.content->groupKey = GetGroupKey(notificationModel.content, channelModel);

    return GetNotificationBuilderFromModel(notificationModel);
}

std::optional<std::string> NotificationBuilder::GetGroupKey(std::shared_ptr<NotificationContentModel> contentModel, const NotificationChannelModel& channelModel) {
    return !contentModel->groupKey.has_value() ?
            contentModel->groupKey : channelModel.groupKey;
}

winrt::Microsoft::Windows::AppNotifications::AppNotification NotificationBuilder::GetNotificationBuilderFromModel(const NotificationModel& notificationModel) {

/*
    NotificationChannelModel channel = ChannelManager::GetChannelByKey(notificationModel.content->channelKey);

    if (channel == null || !ChannelManager::IsChannelEnabled(notificationModel.content->channelKey))
        throw new AwesomeNotificationException("Channel '" + notificationModel.content->channelKey + "' does not exist or is disabled");

    NotificationCompat.Builder builder = new NotificationCompat.Builder(notificationModel.content->channelKey);

    NotificationChannel androidChannel = ChannelManager::GetAndroidChannel(channel.channelKey);
    builder.setChannelId(androidChannel.getId());

    setSmallIcon(notificationModel, channel, builder);

    setRemoteHistory(notificationModel, builder);

    setGrouping(notificationModel, channel, builder);

    setVisibility(notificationModel, channel, builder);
    setShowWhen(notificationModel, builder);

    setLayout(notificationModel, channel, builder);

    setTitle(notificationModel, channel, builder);
    setBody(notificationModel, builder);

    setAutoCancel(notificationModel, builder);
    setTicker(notificationModel, builder);
    setOnlyAlertOnce(notificationModel, channel, builder);

    setLockedNotification(notificationModel, channel, builder);
    setImportance(channel, builder);
    setCategory(notificationModel, builder);

    setSound(notificationModel, channel, builder);
    setVibrationPattern(channel, builder);
    setLights(channel, builder);

    setSmallIcon(notificationModel, channel, builder);
    setLargeIcon(notificationModel, builder);
    setLayoutColor(notificationModel, channel, builder);

    createActionButtons(notificationModel, channel, builder);

    PendingIntent pendingActionIntent = getPendingActionIntent(notificationModel, channel);
    PendingIntent pendingDismissIntent = getPendingDismissIntent(notificationModel, channel);

    setFullScreenIntent(pendingActionIntent, notificationModel, builder);

    setBadge(notificationModel, channel, builder);

    setNotificationPendingIntents(notificationModel, pendingActionIntent, pendingDismissIntent, builder);

    Notification androidNotification = builder.build();
    if(androidNotification.extras == null)
        androidNotification.extras = new Bundle();

    updateTrackingExtras(notificationModel, channel, androidNotification.extras);

    setWakeUpScreen(notificationModel);
    setCriticalAlert(channel);
    setCategoryFlags(notificationModel, androidNotification);

    return androidNotification;
    */

    winrt::Microsoft::Windows::AppNotifications::AppNotification toast(LR"(<toast>
<visual>
    <binding template="ToastGeneric">
        <text>Hello World</text>
        <text>This is a simple toast message</text>
    </binding>
    </visual>
</toast>)");

    toast.Tag(L"Tag");
    toast.Group(L"Group");

    return toast;
}