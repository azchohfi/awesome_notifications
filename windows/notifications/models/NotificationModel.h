#pragma once

#include <flutter/encodable_value.h>

#include <string>
#include <map>
#include <memory>

#include "AbstractModel.h"
#include "NotificationContentModel.h"
#include "NotificationScheduleModel.h"
#include "NotificationButtonModel.h"

class NotificationModel : public AbstractModel {
 public:
  virtual void FromMap(const flutter::EncodableMap& arguments);
  virtual void FromJson(const std::string& json);
  virtual flutter::EncodableValue ToMap() const;

  virtual std::string ToJson() const;

  virtual void Validate() const;

  bool groupSummary = false;
  std::string remoteHistory;

  std::shared_ptr<NotificationContentModel> content;
  std::shared_ptr<NotificationScheduleModel> schedule;
  std::vector<NotificationButtonModel> actionButtons;

  NotificationModel();
  NotificationModel(const AbstractModel& abstractModel);
  
  NotificationModel ClonePush() const;

 private:
  static std::shared_ptr<NotificationContentModel> ExtractNotificationContent(std::string reference, const flutter::EncodableMap* parameters);

  static std::shared_ptr<NotificationScheduleModel> ExtractNotificationSchedule(std::string reference, const flutter::EncodableMap* parameters);

  static std::optional<std::vector<NotificationButtonModel>> ExtractNotificationButtons(std::string reference, const flutter::EncodableMap* parameters);
};