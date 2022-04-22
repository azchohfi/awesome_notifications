#pragma once

#include <flutter/encodable_value.h>

#include <string>
#include <map>
#include <optional>
#include <vector>
#include <memory>

#include "AbstractModel.h"
#include "NotificationMessageModel.h"
#include "../enums/NotificationPrivacy.h"
#include "../enums/NotificationLayout.h"
#include "../enums/NotificationCategory.h"
#include "../enums/NotificationSource.h"
#include "../enums/NotificationLifeCycle.h"

class NotificationContentModel : public AbstractModel {
public:
    bool isRefreshNotification = false;
    bool isRandomId = false;

    int id;
    std::string channelKey;
    std::string title;
    std::string body;
    std::string summary;
    bool showWhen;
    std::vector<NotificationMessageModel> messages;
    flutter::EncodableMap payload;
    std::optional<std::string> groupKey;
    std::string customSound;
    bool playSound;
    std::string icon;
    std::string largeIcon;
    bool locked;
    std::string bigPicture;
    bool wakeUpScreen;
    bool fullScreenIntent;
    bool hideLargeIconOnExpand;
    bool autoDismissible;
    bool displayOnForeground;
    bool displayOnBackground;
    int64_t color;
    int64_t backgroundColor;
    int progress;
    std::string ticker;

    std::optional<NotificationPrivacy> privacy;
    std::string privateMessage;

    std::optional<NotificationLayout> notificationLayout;

    NotificationCategory notificationCategory;

    std::optional<NotificationSource> createdSource;
    std::optional<NotificationLifeCycle> createdLifeCycle;
    std::optional<NotificationLifeCycle> displayedLifeCycle;
    std::optional<NotificationCategory> category;

    std::optional<std::string> createdDate;
    std::optional<std::string> displayedDate;

    bool roundedLargeIcon;
    bool roundedBigPicture;

    NotificationContentModel();

    void FromMap(const flutter::EncodableMap& arguments) override;

    flutter::EncodableValue ToMap() const override;

    static flutter::EncodableList MessagesToMap(std::vector<NotificationMessageModel> messages);

    static std::vector<NotificationMessageModel> MapToMessages(flutter::EncodableList messagesData);

    std::string ToJson() const override;

    void FromJson(const std::string& json) override;

    void Validate() const override;

 private:

    void ValidateIcon() const;

    void ValidateBigPicture() const;

    void ValidateLargeIcon() const;
};