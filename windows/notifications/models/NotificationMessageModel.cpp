#pragma once

#include <flutter/encodable_value.h>

#include <string>
#include <map>
#include <chrono>
#include <memory>

#include "NotificationMessageModel.h"
#include "NotificationButtonModel.h"
#include "../../utils/JsonUtils.h"

NotificationMessageModel::NotificationMessageModel() {

}

NotificationMessageModel::NotificationMessageModel(std::string title, std::string message, std::string largeIcon) {
    this->title = title;
    this->message = message;
    this->largeIcon = largeIcon;
    this->timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void NotificationMessageModel::FromMap(const flutter::EncodableMap& arguments) {
    title   = GetValueOrDefault<std::string>(arguments, Definitions::NOTIFICATION_TITLE).value();
    message = GetValueOrDefault<std::string>(arguments, Definitions::NOTIFICATION_MESSAGES).value();
    largeIcon = GetValueOrDefault<std::string>(arguments, Definitions::NOTIFICATION_LARGE_ICON).value();
    timestamp = GetValueOrDefault<int64_t>(arguments, Definitions::NOTIFICATION_TIMESTAMP).value();
}

flutter::EncodableValue NotificationMessageModel::ToMap() const {
    flutter::EncodableMap returnedObject;

    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_TITLE), flutter::EncodableValue(title)));
    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_MESSAGES), flutter::EncodableValue(message)));
    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_LARGE_ICON), flutter::EncodableValue(largeIcon)));
    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_TIMESTAMP), flutter::EncodableValue(timestamp)));

    return returnedObject;
}

std::string NotificationMessageModel::ToJson() const {
    return TemplateToJson();
}

void NotificationMessageModel::FromJson(const std::string& json) {
    if(json.empty()) {
        return;
    }

    flutter::EncodableMap map = JsonUtils::FromJson(json);
    FromMap(map);
}

void NotificationMessageModel::Validate() const {
}