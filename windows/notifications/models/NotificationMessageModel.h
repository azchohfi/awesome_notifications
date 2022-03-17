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
    virtual void FromMap(const flutter::EncodableMap& arguments);
    virtual void FromJson(const std::string& json);

    virtual flutter::EncodableValue ToMap() const;

    virtual std::string ToJson() const;

    virtual void Validate() const;

};