#pragma once

#include <flutter/encodable_value.h>

#include <string>
#include <chrono>

#include "AbstractModel.h"

class NotificationScheduleModel : public AbstractModel {
 public:
    std::string timeZone;
    std::string createdDate;

    /// Specify false to deliver the notification one time. Specify true to reschedule the notification request each time the notification is delivered.
    bool repeats;
    bool allowWhileIdle;
    bool preciseAlarm;

    void FromMap(const flutter::EncodableMap& arguments) override;

    flutter::EncodableValue ToMap() const override;

    virtual std::chrono::milliseconds GetNextValidDate(std::chrono::milliseconds fixedNowDate) = 0;

    bool HasNextValidDate();

    static std::shared_ptr<NotificationScheduleModel> GetScheduleModelFromMap(const flutter::EncodableMap& map);
};
