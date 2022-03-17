#pragma once

#include <flutter/encodable_value.h>

#include <string>
#include <optional>

#include "NotificationReceived.h"
#include "../NotificationContentModel.h"
#include "../../enums/ActionButtonType.h"
#include "../../enums/NotificationLifeCycle.h"

class ActionReceived : public NotificationReceived {
 public:
    std::optional<std::string> buttonKeyPressed;
    std::optional<std::string> buttonKeyInput;

    ActionButtonType actionButtonType;

    // The value autoDismiss must return as original. Because
    // of that, this variable is being used as temporary
    bool shouldAutoDismiss = true;

    std::optional<NotificationLifeCycle> actionLifeCycle;
    std::optional<NotificationLifeCycle> dismissedLifeCycle;
    std::optional<std::string> actionDate;
    std::optional<std::string> dismissedDate;

    ActionReceived(){}

    ActionReceived(NotificationContentModel contentModel);

    virtual flutter::EncodableValue ToMap() const;

    virtual void FromMap(const flutter::EncodableMap& arguments);

    virtual std::string ToJson() const;

    virtual void FromJson(const std::string& json);
};
