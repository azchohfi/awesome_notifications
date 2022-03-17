#pragma once

#include "../notifications/exceptions/AwesomeNotificationException.h"

#include <chrono>
#include <string>
#include <exception>

class DateUtils {
 public:
    //static TimeZone utcTimeZone = TimeZone.getTimeZone("UTC");
    //static TimeZone localTimeZone = TimeZone.getDefault();

/*
    static Date StringToDate(std::string dateTime, std::string fromTimeZone);
    static std::string DateToString(Date dateTime, std::string fromTimeZone);
    static std::string GetLocalDate(std::string fromTimeZone);
    static Date ShiftToTimeZone(Date date, TimeZone timeZone);
    */

    static std::string GetUTCDate();
    static std::string GetLocalTimeZoneString();
    static std::string GetLocalTimeZoneId();
/*
    static Date GetUTCDateTime();

    static Date GetLocalDateTime(std::string fromTimeZone);
    */

 private:
    DateUtils();
};
