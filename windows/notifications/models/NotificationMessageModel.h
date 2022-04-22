#pragma once

#include <flutter/encodable_value.h>

#include <string>
#include <map>
#include <memory>

#include "AbstractModel.h"
#include "../../definitions.h"

class NotificationMessageModel : public AbstractModel {
 public:
    std::string title;
    std::string message;
    std::string largeIcon;
    long long timestamp;

    NotificationMessageModel();
    NotificationMessageModel(std::string title, std::string message, std::string largeIcon);
    void FromMap(const flutter::EncodableMap& arguments) override;
    void FromJson(const std::string& json) override;

    flutter::EncodableValue ToMap() const override;

    std::string ToJson() const override;

    void Validate() const override;

};