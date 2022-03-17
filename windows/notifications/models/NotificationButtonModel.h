#pragma once

#include <flutter/encodable_value.h>

#include <string>

#include "AbstractModel.h"
#include "../enums/ActionButtonType.h"

class NotificationButtonModel : public AbstractModel {
 public:
    std::string key;
    std::string icon;
    std::string label;
    int color;
    bool enabled;
    bool autoDismissible;
    bool showInCompactView;
    bool isDangerousOption;
    std::optional<ActionButtonType> buttonType;

    NotificationButtonModel();

    void FromMap(const flutter::EncodableMap& arguments);

    flutter::EncodableValue ToMap() const;

    std::string ToJson() const;

    void FromJson(const std::string& json);

    virtual void Validate() const;
};
