#pragma once

#include <flutter/encodable_value.h>

#include "AbstractModel.h"

#include <string>

class NotificationChannelGroupModel : public AbstractModel {
 public:
    std::string channelGroupName;
    std::string channelGroupKey;

    NotificationChannelGroupModel(){}

    void FromMap(const flutter::EncodableMap& arguments) override;

    flutter::EncodableValue ToMap() const override;

    std::string ToJson() const override;

    void FromJson(const std::string& json) override;

    void Validate() const override;
};