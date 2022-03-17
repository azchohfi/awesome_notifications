#pragma once

#include <flutter/encodable_value.h>

#include <string>
#include <map>
#include <memory>

#include "NotificationContentModel.h"
#include "../../definitions.h"
#include "../../utils/JsonUtils.h"
#include "../../utils/IntegerUtils.h"

NotificationContentModel::NotificationContentModel() {
}

void NotificationContentModel::FromMap(const flutter::EncodableMap& arguments) {
    auto notificationId = GetValueOrDefault<int>(arguments, Definitions::NOTIFICATION_ID);
    id = notificationId.has_value() ? notificationId.value() : IntegerUtils::GenerateNextRandomId();

    auto notificationCreatedDate = MapUtils::ExtractValue<std::string>(arguments, Definitions::NOTIFICATION_CREATED_DATE);
    createdDate = notificationCreatedDate.has_value() ? notificationCreatedDate.value() : DateUtils::GetUTCDate();

    displayedDate = MapUtils::ExtractValue<std::string>(arguments, Definitions::NOTIFICATION_DISPLAYED_DATE);

    createdLifeCycle = GetEnumValueOrDefault<NotificationLifeCycle>(arguments, Definitions::NOTIFICATION_CREATED_LIFECYCLE);

    displayedLifeCycle = GetEnumValueOrDefault<NotificationLifeCycle>(arguments, Definitions::NOTIFICATION_DISPLAYED_LIFECYCLE);

    createdSource = GetEnumValueOrDefault<NotificationSource>(arguments, Definitions::NOTIFICATION_CREATED_SOURCE);

    channelKey = GetValueOrDefault<std::string>(arguments, Definitions::NOTIFICATION_CHANNEL_KEY).value();
    color = GetValueOrDefault<int64_t>(arguments, Definitions::NOTIFICATION_COLOR, 0);
    backgroundColor = GetValueOrDefault<int64_t>(arguments, Definitions::NOTIFICATION_BACKGROUND_COLOR, 0);

    title = GetValueOrDefault<std::string>(arguments, Definitions::NOTIFICATION_TITLE, "");
    body  = GetValueOrDefault<std::string>(arguments, Definitions::NOTIFICATION_BODY, "");
    summary = GetValueOrDefault<std::string>(arguments, Definitions::NOTIFICATION_SUMMARY, "");

    playSound = GetValueOrDefault<bool>(arguments, Definitions::NOTIFICATION_PLAY_SOUND, false);
    customSound = GetValueOrDefault<std::string>(arguments, Definitions::NOTIFICATION_CUSTOM_SOUND, "");

    wakeUpScreen = GetValueOrDefault<bool>(arguments, Definitions::NOTIFICATION_WAKE_UP_SCREEN, false);
    fullScreenIntent = GetValueOrDefault<bool>(arguments, Definitions::NOTIFICATION_FULL_SCREEN_INTENT, false);

    showWhen = GetValueOrDefault<bool>(arguments, Definitions::NOTIFICATION_SHOW_WHEN, false);
    locked = GetValueOrDefault<bool>(arguments, Definitions::NOTIFICATION_LOCKED, false);

    displayOnForeground = GetValueOrDefault<bool>(arguments, Definitions::NOTIFICATION_DISPLAY_ON_FOREGROUND, false);
    displayOnBackground = GetValueOrDefault<bool>(arguments, Definitions::NOTIFICATION_DISPLAY_ON_BACKGROUND, false);

    hideLargeIconOnExpand = GetValueOrDefault<bool>(arguments, Definitions::NOTIFICATION_HIDE_LARGE_ICON_ON_EXPAND, false);

    notificationLayout =
            GetEnumValueOrDefault<NotificationLayout>(arguments, Definitions::NOTIFICATION_LAYOUT);

    privacy =
            GetEnumValueOrDefault<NotificationPrivacy>(arguments, Definitions::NOTIFICATION_PRIVACY);

    category =
            GetEnumValueOrDefault<NotificationCategory>(arguments, Definitions::NOTIFICATION_CATEGORY);

    privateMessage = GetValueOrDefault<std::string>(arguments, Definitions::NOTIFICATION_PRIVATE_MESSAGE, "");

    icon  = GetValueOrDefault<std::string>(arguments, Definitions::NOTIFICATION_ICON, "");
    largeIcon  = GetValueOrDefault<std::string>(arguments, Definitions::NOTIFICATION_LARGE_ICON, "");
    bigPicture = GetValueOrDefault<std::string>(arguments, Definitions::NOTIFICATION_BIG_PICTURE, "");

    payload = GetValueOrDefault<flutter::EncodableMap>(arguments, Definitions::NOTIFICATION_PAYLOAD, flutter::EncodableMap());

    autoDismissible = GetValueOrDefault<bool>(arguments, Definitions::NOTIFICATION_AUTO_DISMISSIBLE, false);

    progress    = GetValueOrDefault<int>(arguments, Definitions::NOTIFICATION_PROGRESS, 0);

    groupKey = GetValueOrDefault<std::string>(arguments, Definitions::NOTIFICATION_GROUP_KEY);

    ticker = GetValueOrDefault<std::string>(arguments, Definitions::NOTIFICATION_TICKER, "");

    messages = MapToMessages(GetValueOrDefault<flutter::EncodableList>(arguments, Definitions::NOTIFICATION_MESSAGES, flutter::EncodableList()));

    roundedLargeIcon = GetValueOrDefault<bool>(arguments, Definitions::NOTIFICATION_ROUNDED_LARGE_ICON, false);
    roundedBigPicture = GetValueOrDefault<bool>(arguments, Definitions::NOTIFICATION_ROUNDED_BIG_PICTURE, false);
}

flutter::EncodableValue NotificationContentModel::ToMap() const {
    flutter::EncodableMap returnedObject;

    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_ID), flutter::EncodableValue(this->id)));
    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_RANDOM_ID), flutter::EncodableValue(this->isRandomId)));
    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_TITLE), flutter::EncodableValue(this->title)));
    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_BODY), flutter::EncodableValue(this->body)));
    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_SUMMARY), flutter::EncodableValue(this->summary)));

    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_SHOW_WHEN), flutter::EncodableValue(this->showWhen)));
    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_WAKE_UP_SCREEN), flutter::EncodableValue(this->wakeUpScreen)));
    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_FULL_SCREEN_INTENT), flutter::EncodableValue(this->fullScreenIntent)));

    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_LOCKED), flutter::EncodableValue(this->locked)));

    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_PLAY_SOUND), flutter::EncodableValue(this->playSound)));
    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_CUSTOM_SOUND), flutter::EncodableValue(this->customSound)));

    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_TICKER), flutter::EncodableValue(this->ticker)));
    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_PAYLOAD), flutter::EncodableValue(this->payload)));
    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_AUTO_DISMISSIBLE), flutter::EncodableValue(this->autoDismissible)));

    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_LAYOUT),
            flutter::EncodableValue(NotificationLayoutToString(this->notificationLayout.has_value() ? this->notificationLayout.value() : NotificationLayout::Default))));

    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_CREATED_SOURCE),
            flutter::EncodableValue(NotificationSourceToString(createdSource.has_value() ? this->createdSource.value() : NotificationSource::Local))));

    if (this->createdLifeCycle.has_value())
        returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_CREATED_LIFECYCLE),
                flutter::EncodableValue(NotificationLifeCycleToString(this->createdLifeCycle.value()))));

    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_DISPLAYED_LIFECYCLE),
        flutter::EncodableValue(this->displayedLifeCycle.has_value() ? NotificationLifeCycleToString(this->displayedLifeCycle.value()) : nullptr)));

    if (this->displayedDate.has_value())
        returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_DISPLAYED_DATE), flutter::EncodableValue(this->displayedDate.value())));
    if (this->createdDate.has_value())
        returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_CREATED_DATE), flutter::EncodableValue(this->createdDate.value())));

    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_CHANNEL_KEY), flutter::EncodableValue(this->channelKey)));

    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_ROUNDED_LARGE_ICON), flutter::EncodableValue(this->roundedLargeIcon)));
    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_ROUNDED_BIG_PICTURE), flutter::EncodableValue(this->roundedBigPicture)));

    if(this->category.has_value())
        returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_CATEGORY),
            flutter::EncodableValue(NotificationCategoryToString(this->category.value()))));

    if(this->autoDismissible)
        returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_AUTO_DISMISSIBLE), flutter::EncodableValue(this->autoDismissible)));

    if(this->displayOnForeground)
        returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_DISPLAY_ON_FOREGROUND), flutter::EncodableValue(this->displayOnForeground)));

    if(this->displayOnBackground)
        returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_DISPLAY_ON_BACKGROUND), flutter::EncodableValue(this->displayOnBackground)));

    if(this->color)
        returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_COLOR), flutter::EncodableValue(this->color)));
    if(this->backgroundColor)
        returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_BACKGROUND_COLOR), flutter::EncodableValue(this->backgroundColor)));

    if(!this->icon.empty())
        returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_ICON), flutter::EncodableValue(this->icon)));

    if(!this->largeIcon.empty())
        returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_LARGE_ICON), flutter::EncodableValue(this->largeIcon)));

    if(!this->bigPicture.empty())
        returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_BIG_PICTURE), flutter::EncodableValue(this->bigPicture)));

    if(this->progress)
        returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_PROGRESS), flutter::EncodableValue(this->progress)));

    if(this->groupKey.has_value())
        returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_GROUP_KEY), flutter::EncodableValue(this->groupKey.value())));

    if(this->privacy.has_value())
        returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_PRIVACY),
            flutter::EncodableValue(NotificationPrivacyToString(this->privacy.value()))));

    if(!this->privateMessage.empty())
        returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_PRIVATE_MESSAGE), flutter::EncodableValue(this->privateMessage)));

    if(!this->messages.empty())
        returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_MESSAGES), flutter::EncodableValue(MessagesToMap(this->messages))));

    return returnedObject;
}

flutter::EncodableList NotificationContentModel::MessagesToMap(std::vector<NotificationMessageModel> messages) {
    flutter::EncodableList returnedMessages;

    if(!messages.empty()) {
        for (auto &messageModel : messages) {
            returnedMessages.push_back(messageModel.ToMap());
        }
    }
    return returnedMessages;
}

std::vector<NotificationMessageModel> NotificationContentModel::MapToMessages(flutter::EncodableList messagesData) {
    std::vector<NotificationMessageModel> messages;

    if(!messagesData.empty()) {
        for(auto &messageData : messagesData) {
            if (const auto* mapValue = std::get_if<flutter::EncodableMap>(&messageData)) {
                NotificationMessageModel messageModel;
                messageModel.FromMap(*mapValue);
                messages.push_back(messageModel);
            }
        }
    }
    return messages;
}

std::string NotificationContentModel::ToJson() const {
    return TemplateToJson();
}

void NotificationContentModel::FromJson(const std::string& json) {
    if(json.empty()) {
        return;
    }

    flutter::EncodableMap map = JsonUtils::FromJson(json);
    FromMap(map);
}

void NotificationContentModel::Validate() const {
    /*
    if(ChannelManager.getChannelByKey(channelKey) == null)
        throw new AwesomeNotificationException("Notification channel '"+channelKey+"' does not exist.");
    */

    ValidateIcon();

    if (notificationLayout.has_value()) {
        switch (notificationLayout.value()) {

            case NotificationLayout::Default:
                break;

            case NotificationLayout::BigPicture:
                ValidateBigPicture();
                break;

            case NotificationLayout::BigText:
                break;

            case NotificationLayout::Inbox:
                break;

            case NotificationLayout::Messaging:
                break;
        }
    }

    ValidateLargeIcon();
}

void NotificationContentModel::ValidateIcon() const {
/*
    if(!StringUtils.isNullOrEmpty(icon)){
        if(
            BitmapUtils.getMediaSourceType(icon) != MediaSource.Resource ||
            !BitmapUtils.isValidBitmap(icon)
        ){
            throw AwesomeNotificationException("Small icon ('"+icon+"') must be a valid media native resource type.");
        }
    }
    */
}

void NotificationContentModel::ValidateBigPicture() const {
    /*
    if(
        (StringUtils.isNullOrEmpty(largeIcon) && StringUtils.isNullOrEmpty(bigPicture)) ||
        (!StringUtils.isNullOrEmpty(largeIcon) && !BitmapUtils.isValidBitmap(largeIcon)) ||
        (!StringUtils.isNullOrEmpty(bigPicture) && !BitmapUtils.isValidBitmap(bigPicture))
    ){
        throw AwesomeNotificationException("Invalid big picture '"+bigPicture+"' or large icon '"+largeIcon+"'");
    }
    */
}

void NotificationContentModel::ValidateLargeIcon() const {
    /*
    if(
            (!StringUtils.isNullOrEmpty(largeIcon) && !BitmapUtils.isValidBitmap(largeIcon))
    )
        throw AwesomeNotificationException("Invalid large icon '"+largeIcon+"'");
    */
}