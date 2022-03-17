#include <flutter/encodable_value.h>

#include <string>
#include <map>

#include "NotificationScheduleModel.h"
#include "NotificationCalendarModel.h"
#include "../../definitions.h"

void NotificationScheduleModel::FromMap(const flutter::EncodableMap& arguments) {
    timeZone = GetValueOrDefault<std::string>(arguments, Definitions::NOTIFICATION_SCHEDULE_TIMEZONE, "");

    createdDate = MapUtils::ExtractValue<std::string>(arguments, Definitions::NOTIFICATION_CREATED_DATE)
            .value_or(DateUtils::GetUTCDate());

    repeats = GetValueOrDefault<bool>(arguments, Definitions::NOTIFICATION_SCHEDULE_REPEATS, false);
    allowWhileIdle = GetValueOrDefault<bool>(arguments, Definitions::NOTIFICATION_ALLOW_WHILE_IDLE, false);

    preciseAlarm = GetValueOrDefault<bool>(arguments, Definitions::NOTIFICATION_SCHEDULE_PRECISE_ALARM, false);
}

flutter::EncodableValue NotificationScheduleModel::ToMap() const {
    flutter::EncodableMap returnedObject;
    
    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_SCHEDULE_TIMEZONE), flutter::EncodableValue(timeZone)));
    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_CREATED_DATE), flutter::EncodableValue(createdDate)));

    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_SCHEDULE_REPEATS), flutter::EncodableValue(repeats)));
    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_ALLOW_WHILE_IDLE), flutter::EncodableValue(allowWhileIdle)));

    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_SCHEDULE_PRECISE_ALARM), flutter::EncodableValue(preciseAlarm)));
    
    return returnedObject;
}

bool NotificationScheduleModel::HasNextValidDate() {
/*
    TimeZone timeZone = StringUtils.isNullOrEmpty(this.timeZone) ?
            DateUtils.localTimeZone :
            TimeZone.getTimeZone(this.timeZone);

    if (timeZone == null)
        throw new AwesomeNotificationException("Invalid time zone");

    if(createdDate == null && !repeats)
        return false;

    Date referenceDate = repeats ?
            DateUtils.getLocalDateTime(this.timeZone) :
            DateUtils.stringToDate(createdDate, this.timeZone);

    Calendar nextSchedule = getNextValidDate(referenceDate);
    if(nextSchedule == null)
        return false;

    Date nextValidDate = nextSchedule.getTime();
    return nextValidDate != null && nextValidDate.compareTo(DateUtils.getLocalDateTime(this.timeZone)) >= 0;
    */
    return false;
}

std::shared_ptr<NotificationScheduleModel> NotificationScheduleModel::GetScheduleModelFromMap(const flutter::EncodableMap& map) {
    if(map.empty()) {
        return nullptr;
    }

    if(
        map.find(flutter::EncodableValue(Definitions::NOTIFICATION_CRONTAB_EXPRESSION)) != map.end() ||
        map.find(flutter::EncodableValue(Definitions::NOTIFICATION_PRECISE_SCHEDULES)) != map.end() ||
        map.find(flutter::EncodableValue(Definitions::NOTIFICATION_EXPIRATION_DATE_TIME)) != map.end()
    ){
        /*
        auto notificationCrontabModel = std::make_shared<NotificationCrontabModel>();
        notificationCrontabModel->FromMap(map);
        return notificationCrontabModel;
        */
    }

    if(
        map.find(flutter::EncodableValue(Definitions::NOTIFICATION_SCHEDULE_SECOND)) != map.end() ||
        map.find(flutter::EncodableValue(Definitions::NOTIFICATION_SCHEDULE_MINUTE)) != map.end() ||
        map.find(flutter::EncodableValue(Definitions::NOTIFICATION_SCHEDULE_HOUR)) != map.end() ||
        map.find(flutter::EncodableValue(Definitions::NOTIFICATION_SCHEDULE_DAY)) != map.end() ||
        map.find(flutter::EncodableValue(Definitions::NOTIFICATION_SCHEDULE_MONTH)) != map.end() ||
        map.find(flutter::EncodableValue(Definitions::NOTIFICATION_SCHEDULE_YEAR)) != map.end() ||
        map.find(flutter::EncodableValue(Definitions::NOTIFICATION_SCHEDULE_ERA)) != map.end() ||
        map.find(flutter::EncodableValue(Definitions::NOTIFICATION_SCHEDULE_MILLISECOND)) != map.end() ||
        map.find(flutter::EncodableValue(Definitions::NOTIFICATION_SCHEDULE_WEEKDAY)) != map.end() ||
        map.find(flutter::EncodableValue(Definitions::NOTIFICATION_SCHEDULE_WEEKOFMONTH)) != map.end() ||
        map.find(flutter::EncodableValue(Definitions::NOTIFICATION_SCHEDULE_WEEKOFYEAR)) != map.end()
    ){
        auto notificationCalendarModel = std::make_shared<NotificationCalendarModel>();
        notificationCalendarModel->FromMap(map);
        return notificationCalendarModel;
    }

    if(map.find(flutter::EncodableValue(Definitions::NOTIFICATION_SCHEDULE_INTERVAL)) != map.end()){
        /*
        auto notificationIntervalModel = std::make_shared<NotificationIntervalModel>();
        notificationIntervalModel->FromMap(map);
        return notificationIntervalModel;
        */
    }

    return nullptr;
}