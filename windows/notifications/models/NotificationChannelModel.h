#pragma once

#include <flutter/encodable_value.h>

#include <string>
#include <optional>
#include <vector>

#include "AbstractModel.h"
#include "../enums/NotificationImportance.h"
#include "../enums/DefaultRingtoneType.h"
#include "../enums/GroupSort.h"
#include "../enums/GroupAlertBehaviour.h"
#include "../enums/NotificationPrivacy.h"

class NotificationChannelModel : public AbstractModel {
 public:
    std::string channelKey;
    std::string channelName;
    std::string channelDescription;
    bool channelShowBadge;

    std::string channelGroupKey;

    std::optional<NotificationImportance> importance;

    bool playSound;
    std::string soundSource;
    std::optional<DefaultRingtoneType> defaultRingtoneType;

    bool enableVibration;
    std::vector<int64_t> vibrationPattern;

    bool enableLights;
    int ledColor;
    int ledOnMs;
    int ledOffMs;

    std::optional<std::string> groupKey;
    std::optional<GroupSort> groupSort;
    std::optional<GroupAlertBehaviour> groupAlertBehavior;

    // Note: this is set on the Android to save details about the icon that should be used when re-hydrating delayed notifications when a device has been restarted.
    int iconResourceId;

    std::string  icon;
    int64_t defaultColor;

    bool locked;
    bool onlyAlertOnce;

    bool criticalAlerts;

    std::optional<NotificationPrivacy> defaultPrivacy;

    NotificationChannelModel(){}

    void RefreshIconResource();

    bool IsChannelEnabled();

    std::string GetChannelHashKey(bool fullHashObject);

    //bool equals(@Nullable Object obj);

    void FromMap(const flutter::EncodableMap& arguments) override;

    flutter::EncodableValue ToMap() const override;

    std::string ToJson() const override;

    void FromJson(const std::string& json) override;

    void Validate() const override;

    virtual NotificationChannelModel Clone();
};
