#pragma once

#include <flutter/encodable_value.h>

#include <string>
#include <memory>
#include <optional>

#include "NotificationScheduleModel.h"

class NotificationCalendarModel : public NotificationScheduleModel {
 public:
   /// Field number for get and set indicating the era, e.g., AD or BC in the Julian calendar
   std::optional<int> era;
   /// Field number for get and set indicating the year.
   std::optional<int> year;
   /// Field number for get and set indicating the month.
   std::optional<int> month;
   /// Field number for get and set indicating the day number within the current year (1-12).
   std::optional<int> day;
   /// Field number for get and set indicating the hour of the day (0-23).
   std::optional<int> hour;
   /// Field number for get and set indicating the minute within the hour (0-59).
   std::optional<int> minute;
   /// Field number for get and set indicating the second within the minute (0-59).
   std::optional<int> second;
   /// Field number for get and set indicating the millisecond within the second.
   std::optional<int> millisecond;
   /// Field number for get and set indicating the day of the week.
   std::optional<int> weekday;
   /// Field number for get and set indicating the count of weeks of the month.
   std::optional<int> weekOfMonth;
   /// Field number for get and set indicating the weeks of the year.
   std::optional<int> weekOfYear;

   virtual void FromMap(const flutter::EncodableMap& arguments);

   virtual flutter::EncodableValue ToMap() const;

   virtual std::string ToJson() const;

   virtual void FromJson(const std::string& json);

   virtual void Validate() const;

   virtual std::chrono::milliseconds GetNextValidDate(std::chrono::milliseconds fixedNowDate);

 private:
   std::string weekdayName;
};