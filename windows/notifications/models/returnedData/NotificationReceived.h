#pragma once

#include <flutter/encodable_value.h>

#include <string>

#include "../NotificationContentModel.h"

// Just created because of Json process
class NotificationReceived : public NotificationContentModel {
 public:
    NotificationReceived(){}

    NotificationReceived(std::shared_ptr<NotificationContentModel> contentModel);

    virtual void FromMap(const flutter::EncodableMap& arguments);

    virtual flutter::EncodableValue ToMap() const;

    virtual std::string ToJson() const;

    virtual void FromJson(const std::string& json);
};
