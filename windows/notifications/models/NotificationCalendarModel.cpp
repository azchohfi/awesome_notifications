#include <string>
#include <memory>

#include "NotificationCalendarModel.h"
#include "NotificationScheduleModel.h"
#include "../../definitions.h"
#include "../../utils/JsonUtils.h"

void NotificationCalendarModel::FromMap(const flutter::EncodableMap& arguments) {
    NotificationScheduleModel::FromMap(arguments);

    era = GetValueOrDefault<int>(arguments, Definitions::NOTIFICATION_SCHEDULE_ERA);
    year = GetValueOrDefault<int>(arguments, Definitions::NOTIFICATION_SCHEDULE_YEAR);
    month = GetValueOrDefault<int>(arguments, Definitions::NOTIFICATION_SCHEDULE_MONTH);
    day = GetValueOrDefault<int>(arguments, Definitions::NOTIFICATION_SCHEDULE_DAY);
    hour = GetValueOrDefault<int>(arguments, Definitions::NOTIFICATION_SCHEDULE_HOUR);
    minute = GetValueOrDefault<int>(arguments, Definitions::NOTIFICATION_SCHEDULE_MINUTE);
    second = GetValueOrDefault<int>(arguments, Definitions::NOTIFICATION_SCHEDULE_SECOND);
    millisecond = GetValueOrDefault<int>(arguments, Definitions::NOTIFICATION_SCHEDULE_MILLISECOND);
    weekday = GetValueOrDefault<int>(arguments, Definitions::NOTIFICATION_SCHEDULE_WEEKDAY);
    weekOfMonth = GetValueOrDefault<int>(arguments, Definitions::NOTIFICATION_SCHEDULE_WEEKOFMONTH);
    weekOfYear = GetValueOrDefault<int>(arguments, Definitions::NOTIFICATION_SCHEDULE_WEEKOFYEAR);

    if(era.has_value() && era < 0){ era.reset(); }
    if(year.has_value() && year < 0){ year.reset(); }
    if(month.has_value() && month < 0){ month.reset(); }
    if(day.has_value() && day < 0){ day.reset(); }
    if(hour.has_value() && hour < 0){ hour.reset(); }
    if(minute.has_value() && minute < 0){ minute.reset(); }
    if(second.has_value() && second < 0){ second.reset(); }
    if(millisecond.has_value() && millisecond < 0){ millisecond.reset(); }
    if(weekday.has_value() && weekday < 0){ weekday.reset(); }
    if(weekOfMonth.has_value() && weekOfMonth < 0){ weekOfMonth.reset(); }
    if(weekOfYear.has_value() && weekOfYear < 0){ weekOfYear.reset(); }

    if(weekday.has_value())
        weekday = weekday == 7 ? 1 : (weekday.value() + 1);
}

flutter::EncodableValue OptionalIntToEncodable(std::optional<int> val) {
    return flutter::EncodableValue(val.has_value() ? val.value() : 0);
}

flutter::EncodableValue NotificationCalendarModel::ToMap() const {
    flutter::EncodableMap returnedObject = std::get<flutter::EncodableMap>(NotificationScheduleModel::ToMap());

    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_SCHEDULE_TIMEZONE), flutter::EncodableValue(timeZone)));
    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_SCHEDULE_ERA), OptionalIntToEncodable(era)));
    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_SCHEDULE_YEAR), OptionalIntToEncodable(year)));
    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_SCHEDULE_MONTH), OptionalIntToEncodable(month)));
    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_SCHEDULE_DAY), OptionalIntToEncodable(day)));
    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_SCHEDULE_HOUR), OptionalIntToEncodable(hour)));
    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_SCHEDULE_MINUTE), OptionalIntToEncodable(minute)));
    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_SCHEDULE_SECOND), OptionalIntToEncodable(second)));
    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_SCHEDULE_MILLISECOND), OptionalIntToEncodable(millisecond)));
    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_SCHEDULE_WEEKOFMONTH), OptionalIntToEncodable(weekOfMonth)));
    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_SCHEDULE_WEEKOFYEAR), OptionalIntToEncodable(weekOfYear)));

    if(weekday.has_value()) {
        returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_SCHEDULE_WEEKDAY), 
            flutter::EncodableValue(weekday == 1 ? 7 : (weekday.value() - 1))));
    } else {
        returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_SCHEDULE_WEEKDAY), 
            flutter::EncodableValue(nullptr)));
    }

    return returnedObject;
}

std::string NotificationCalendarModel::ToJson() const {
    return TemplateToJson();
}

void NotificationCalendarModel::FromJson(const std::string& json) {
    if(json.empty()) {
        return;
    }

    flutter::EncodableMap map = JsonUtils::FromJson(json);
    FromMap(map);
}

static inline bool IsBetween(std::optional<int> value, int min, int max) {
    return value >= min && value <= max;
}

void NotificationCalendarModel::Validate() const {

    if(
        !era.has_value() &&
        !year.has_value() &&
        !month.has_value() &&
        !day.has_value() &&
        !hour.has_value() &&
        !minute.has_value() &&
        !second.has_value() &&
        !millisecond.has_value() &&
        !weekday.has_value() &&
        !weekOfMonth.has_value() &&
        !weekOfYear.has_value()
    )
        throw AwesomeNotificationException("At least one parameter is required");

    if(!(
        (!era.has_value() || IsBetween(era, 0, 99999)) &&
        (!year.has_value() || IsBetween(year, 0, 99999)) &&
        (!month.has_value() || IsBetween(month, 1, 12)) &&
        (!day.has_value() || IsBetween(day, 1, 31)) &&
        (!hour.has_value() || IsBetween(hour, 0, 23)) &&
        (!minute.has_value() || IsBetween(minute, 0, 59)) &&
        (!second.has_value() || IsBetween(second, 0, 59)) &&
        (!millisecond.has_value() || IsBetween(millisecond, 0, 999)) &&
        (!weekday.has_value() || IsBetween(weekday, 1, 7)) &&
        (!weekOfMonth.has_value() || IsBetween(weekOfMonth, 1, 6)) &&
        (!weekOfYear.has_value() || IsBetween(weekOfYear, 1, 53))
    ))
        throw AwesomeNotificationException("Calendar values are invalid");
}

std::chrono::milliseconds NotificationCalendarModel::GetNextValidDate(std::chrono::milliseconds fixedNowDate) {
    /*
    std::string cronExpression =
            (second == nullptr ? "*" : second.toString()) + " " +
            (minute == null ? "*" : minute.toString()) + " " +
            (hour == null ? "*" : hour.toString()) + " " +
            (weekday != null ? "?" : (day == null ? "*" : day.toString())) + " " +
            (month == null ? "*" : month.toString()) + " " +
            (weekday == null ? "?" : weekday.toString()) + " " +
            (year == null ? "*" : year.toString());

    TimeZone timeZone = StringUtils.isNullOrEmpty(this.timeZone) ?
            DateUtils.localTimeZone :
            TimeZone.getTimeZone(this.timeZone);

    if (timeZone == null)
        throw new AwesomeNotificationException("Invalid time zone");

    return CronUtils.getNextCalendar(null, cronExpression, fixedNowDate, timeZone );
*/
    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(duration);
}