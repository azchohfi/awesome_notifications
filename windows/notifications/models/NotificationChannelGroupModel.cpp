#include "../exceptions/AwesomeNotificationException.h"
#include "NotificationChannelGroupModel.h"

void NotificationChannelGroupModel::FromMap(const flutter::EncodableMap& arguments) {
    channelGroupName = GetValueOrDefault<std::string>(arguments, Definitions::NOTIFICATION_CHANNEL_GROUP_NAME, "");
    channelGroupKey = GetValueOrDefault<std::string>(arguments, Definitions::NOTIFICATION_CHANNEL_GROUP_KEY, "");
}

flutter::EncodableValue NotificationChannelGroupModel::ToMap() const {
    flutter::EncodableMap returnedObject;

    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_CHANNEL_GROUP_NAME), flutter::EncodableValue(this->channelGroupName)));
    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_CHANNEL_GROUP_KEY), flutter::EncodableValue(this->channelGroupKey)));

    return returnedObject;
}

std::string NotificationChannelGroupModel::ToJson() const {
    return TemplateToJson();
}

void NotificationChannelGroupModel::FromJson(const std::string& json) {
    if(json.empty()) {
        return;
    }

    flutter::EncodableMap map = JsonUtils::FromJson(json);
    FromMap(map);
}

void NotificationChannelGroupModel::Validate() const {
    if(channelGroupName.empty())
        throw AwesomeNotificationException("Channel group name cannot be null or empty");

    if(channelGroupKey.empty())
        throw AwesomeNotificationException("Channel group key cannot be null or empty");
}
