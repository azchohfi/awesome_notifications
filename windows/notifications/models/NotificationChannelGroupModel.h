#pragma once

#include <flutter/encodable_value.h>

#include "AbstractModel.h"

#include <string>

class NotificationChannelGroupModel : public AbstractModel {
 public:
    std::string channelGroupName;
    std::string channelGroupKey;

    NotificationChannelGroupModel(){}

    void FromMap(const flutter::EncodableMap& arguments);

    flutter::EncodableValue ToMap() const;

    std::string ToJson() const;

    void FromJson(const std::string& json);

    void Validate() const;
};
