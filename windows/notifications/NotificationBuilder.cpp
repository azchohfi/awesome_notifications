#include "NotificationBuilder.h"

#include "../utils/IntegerUtils.h"
#include "../utils/HtmlUtils.h"
#include "../utils/StringUtils.h"
#include "../utils/BitmapUtils.h"
#include "managers/DefaultsManager.h"

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

    NotificationChannelModel channel;
/*
    
    NotificationChannelModel channel = ChannelManager::GetChannelByKey(notificationModel.content->channelKey);

    if (channel == null || !ChannelManager::IsChannelEnabled(notificationModel.content->channelKey))
        throw new AwesomeNotificationException("Channel '" + notificationModel.content->channelKey + "' does not exist or is disabled");
        */

    std::wstring toastTag = L"<toast>";
    std::wstring builder = LR"(<visual>
    <binding template="ToastGeneric">)";
    std::wstring actions = L"";

    /*
    NotificationCompat.Builder builder = new NotificationCompat.Builder(notificationModel.content->channelKey);

    NotificationChannel androidChannel = ChannelManager::GetAndroidChannel(channel.channelKey);
    builder.setChannelId(androidChannel.getId());

    setRemoteHistory(notificationModel, builder);

    setGrouping(notificationModel, channel, builder);

    setVisibility(notificationModel, channel, builder);
    setShowWhen(notificationModel, builder);
*/
    SetLayout(notificationModel, channel, builder);
    SetTitle(notificationModel, channel, builder);
    SetBody(notificationModel, builder);
    /*

    setAutoCancel(notificationModel, builder);
    setTicker(notificationModel, builder);
    setOnlyAlertOnce(notificationModel, channel, builder);

    setLockedNotification(notificationModel, channel, builder);
    */
    SetImportance(channel, toastTag);
    /*
    setCategory(notificationModel, builder);

    setSound(notificationModel, channel, builder);
    setVibrationPattern(channel, builder);
    setLights(channel, builder);
*/
    SetSmallIcon(notificationModel, channel, builder);
    SetLargeIcon(notificationModel, builder);
    /*
    setLayoutColor(notificationModel, channel, builder);
    */
    CreateActionButtons(notificationModel, channel, actions);
    /*

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

    */

    builder += L"</binding></visual>";
    builder += actions;
    builder += L"</toast>";

    builder = toastTag + builder;

    winrt::Microsoft::Windows::AppNotifications::AppNotification toast(builder);

    toast.Tag(L"Tag");
    toast.Group(L"Group");

    return toast;
}

void NotificationBuilder::SetImportance(const NotificationChannelModel& channel, std::wstring& toast) {
    if (channel.importance == NotificationImportance::Max) {
        toast = LR"(<toast scenario="urgent">)";
    }
}

void NotificationBuilder::SetBody(const NotificationModel& notificationModel, std::wstring& builder) {
    builder += L"<text>";
    builder += HtmlUtils::FromHtml(notificationModel.content->body);
    builder += L"</text>";
}

void NotificationBuilder::SetTitle(const NotificationModel& notificationModel, const NotificationChannelModel& channelModel, std::wstring& builder) {
    if (!notificationModel.content->title.empty()) {
        builder += L"<text>";
        builder += HtmlUtils::FromHtml(notificationModel.content->title);
        builder += L"</text>";
    }
}

void NotificationBuilder::CreateActionButtons(const NotificationModel& notificationModel, const NotificationChannelModel& channel, std::wstring& actions) {

    if (notificationModel.actionButtons.empty()) return;

    actions += L"<actions>";

    for (NotificationButtonModel buttonProperties : notificationModel.actionButtons) {

        // // If reply is not available, do not show it
        // if (
        //     android.os.Build.VERSION.SDK_INT < Build.VERSION_CODES.N &&
        //     buttonProperties.buttonType == ActionButtonType.InputField
        // ){
        //     continue;
        // }

        /*
        Intent actionIntent = buildNotificationIntentFromModel(
                Definitions::NOTIFICATION_BUTTON_ACTION_PREFIX + "_" + buttonProperties.key,
                notificationModel,
                channel,
                buttonProperties.buttonType == ActionButtonType::DisabledAction ||
                buttonProperties.buttonType == ActionButtonType::KeepOnTop ?
                                KeepOnTopActionReceiver.class : getNotificationTargetActivityClass()
        );

        actionIntent.putExtra(Definitions::NOTIFICATION_AUTO_DISMISSIBLE, buttonProperties.autoDismissible);
        actionIntent.putExtra(Definitions::NOTIFICATION_SHOW_IN_COMPACT_VIEW, buttonProperties.showInCompactView);
        actionIntent.putExtra(Definitions::NOTIFICATION_ENABLED, buttonProperties.enabled);
        actionIntent.putExtra(Definitions::NOTIFICATION_BUTTON_TYPE, buttonProperties.buttonType.toString());
        actionIntent.putExtra(Definitions::NOTIFICATION_BUTTON_KEY, buttonProperties.key);

        PendingIntent actionPendingIntent = null;

        if (buttonProperties.enabled) {

            if (
                buttonProperties.buttonType == ActionButtonType::KeepOnTop ||
                buttonProperties.buttonType == ActionButtonType::DisabledAction
            ) {

                actionPendingIntent = PendingIntent.getBroadcast(
                        notificationModel.content.id,
                        actionIntent,
                        PendingIntent.FLAG_IMMUTABLE | PendingIntent.FLAG_UPDATE_CURRENT
                );

            } else if (buttonProperties.buttonType == ActionButtonType.InputField) {

                actionPendingIntent = PendingIntent.getActivity(
                        notificationModel.content.id,
                        actionIntent,
                        PendingIntent.FLAG_MUTABLE | PendingIntent.FLAG_UPDATE_CURRENT
                );

            } else {

                actionPendingIntent = PendingIntent.getActivity(
                        notificationModel.content.id,
                        actionIntent,
                        PendingIntent.FLAG_IMMUTABLE | PendingIntent.FLAG_UPDATE_CURRENT
                );
            }
        }
        
        int iconResource = 0;
        if (!buttonProperties.icon.empty()) {
            iconResource = BitmapUtils.getDrawableResourceId(buttonProperties.icon);
        }
        */
        if (
            buttonProperties.buttonType == ActionButtonType::InputField
        ){
            /*
            RemoteInput remoteInput = new RemoteInput.Builder(buttonProperties.key)
                    .setLabel(buttonProperties.label)
                    .build();

            NotificationCompat.Action replyAction = new NotificationCompat.Action.Builder(
                    iconResource, buttonProperties.label, actionPendingIntent)
                    .addRemoteInput(remoteInput)
                    .build();
            */

            actions += LR"(<input id=")" + StringUtils::ToWString(buttonProperties.key) + LR"(" type="text" placeHolderContent=")" + HtmlUtils::FromHtml(buttonProperties.label) + LR"("/>)";
            std::string arguments = Definitions::NOTIFICATION_BUTTON_ACTION_PREFIX + "_" + buttonProperties.key;
            actions += LR"(<action content=")" + HtmlUtils::FromHtml(buttonProperties.label) + LR"(" 
                arguments=")" + StringUtils::ToWString(arguments) + LR"(" hint-inputId=")" + StringUtils::ToWString(buttonProperties.key) + LR"(" />)";
        } else {
            std::string arguments = Definitions::NOTIFICATION_BUTTON_ACTION_PREFIX + "_" + buttonProperties.key;
            actions += LR"(<action content=")" + HtmlUtils::FromHtml(buttonProperties.label) + LR"(" 
                arguments=")" + StringUtils::ToWString(arguments) + LR"("/>)";

            /*
            actions.addAction(
                iconResource,
                HtmlCompat.fromHtml(
                    buttonProperties.isDangerousOption ?
                        "<font color=\"16711680\">" + buttonProperties.label + "</font>" :
                        (
                            buttonProperties.color != null ?
                                "<font color=\"" + buttonProperties.color.toString() + "\">" + buttonProperties.label + "</font>":
                                buttonProperties.label
                        ),
                    HtmlCompat.FROM_HTML_MODE_LEGACY
                ),
                actionPendingIntent);
            */
        }
    }

    actions += L"</actions>";
}

void NotificationBuilder::SetSmallIcon(const NotificationModel& notificationModel, const NotificationChannelModel& channelModel, std::wstring& builder) {
    if (!notificationModel.content->icon.empty()) {
        //builder.setSmallIcon(BitmapUtils.getDrawableResourceId(notificationModel.content.icon));
    } else if (!channelModel.icon.empty()) {
        //builder.setSmallIcon(BitmapUtils.getDrawableResourceId(channelModel.icon));
    } else {
        std::string defaultIcon = DefaultsManager::GetDefaultIconByKey();

        /*
        if (defaultIcon.empty()) {

            int defaultResource = context.getResources().getIdentifier(
                    "ic_launcher",
                    "mipmap",
                    context.getPackageName()
            );

            if (defaultResource > 0) {
                builder.setSmallIcon(defaultResource);
            }
        } else {
            int resourceIndex = BitmapUtils.getDrawableResourceId(defaultIcon);
            if (resourceIndex > 0) {
                builder.setSmallIcon(resourceIndex);
            }
        }
        */
    }
}

void NotificationBuilder::SetLargeIcon(const NotificationModel& notificationModel, std::wstring& builder) {
    if (notificationModel.content->notificationLayout != NotificationLayout::BigPicture) {
        if (!notificationModel.content->largeIcon.empty()) {
            auto largeIcon = BitmapUtils::GetBitmapFromSource(
                    notificationModel.content->largeIcon,
                    notificationModel.content->roundedLargeIcon);
            if (!largeIcon.empty()) {
                auto crop = std::wstring(notificationModel.content->roundedLargeIcon ? L"circle" : L"default");
                builder += LR"(<image placement="appLogoOverride" hint-crop=")" + crop + LR"(" src=")" + largeIcon + LR"("/>)";
            }
        }
    }
}

void NotificationBuilder::SetLayout(const NotificationModel& notificationModel, const NotificationChannelModel& channelModel, std::wstring& builder) {
    if (!notificationModel.content->notificationLayout.has_value()) {
        return;
    }

    switch (notificationModel.content->notificationLayout.value()) {

        case NotificationLayout::BigPicture:
            if (SetBigPictureLayout(notificationModel.content, builder)) return;
            break;

        case NotificationLayout::BigText:
            //if (setBigTextStyle(notificationModel.content, builder)) return;
            break;

        case NotificationLayout::Inbox:
            //if (setInboxLayout(notificationModel.content, builder)) return;
            break;

        case NotificationLayout::Messaging:
            //if (setMessagingLayout(false, notificationModel.content, channelModel, builder)) return;
            break;

        case NotificationLayout::MessagingGroup:
            //if(setMessagingLayout(true, notificationModel.content, channelModel, builder)) return;
            break;

        case NotificationLayout::PhoneCall:
            //setPhoneCallLayout(notificationModel, builder);
            break;

        case NotificationLayout::MediaPlayer:
            //if (setMediaPlayerLayout(notificationModel.content, notificationModel.actionButtons, builder)) return;
            break;

        case NotificationLayout::ProgressBar:
            //setProgressLayout(notificationModel, builder);
            break;

        case NotificationLayout::Default:
            break;

        default:
            break;
    }
}

bool NotificationBuilder::SetBigPictureLayout(std::shared_ptr<NotificationContentModel> contentModel, std::wstring& builder) {

    std::wstring bigPicture, largeIcon;

    if (!contentModel->bigPicture.empty())
        bigPicture = BitmapUtils::GetBitmapFromSource(
                contentModel->bigPicture,
                contentModel->roundedBigPicture);

    if (contentModel->hideLargeIconOnExpand)
        largeIcon = !bigPicture.empty() ?
            bigPicture : (!contentModel->largeIcon.empty() ?
                BitmapUtils::GetBitmapFromSource(
                        contentModel->largeIcon,
                        contentModel->roundedLargeIcon
                ) : L"");
    else {
        bool areEqual =
                !contentModel->largeIcon.empty() &&
                contentModel->largeIcon == contentModel->bigPicture &&
                contentModel->roundedLargeIcon == contentModel->roundedBigPicture;

        if(areEqual)
            largeIcon = bigPicture;
        else if(!contentModel->largeIcon.empty())
            largeIcon =
                    BitmapUtils::GetBitmapFromSource(
                            contentModel->largeIcon,
                            contentModel->roundedLargeIcon);
    }

    if (!largeIcon.empty()) {
        builder += LR"(<image placement="appLogoOverride" hint-crop=")" + std::wstring(contentModel->roundedLargeIcon ? L"circle" : L"default") + LR"(" src=")" + largeIcon + LR"("/>)";
    }

    if (bigPicture.empty())
        return false;

    if (!contentModel->title.empty()) {
        auto contentTitle = HtmlUtils::FromHtml(contentModel->title);
        builder += LR"(<text>)" + contentTitle + LR"("</text>)";
    }

    builder += LR"(<image placement="hero" hint-crop=")" + std::wstring(contentModel->roundedBigPicture ? L"circle" : L"default") + LR"(" src=")" + bigPicture + LR"("/>)";

    if (!contentModel->body.empty()) {
        auto summaryText = HtmlUtils::FromHtml(contentModel->body);
        builder += LR"(<text>)" + summaryText + LR"("</text>)";
    }

    return true;
}