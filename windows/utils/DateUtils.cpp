#include "../notifications/exceptions/AwesomeNotificationException.h"

#include <chrono>
#include <string>
#include <exception>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>

#include "../definitions.h"

DateUtils::DateUtils() {
}

/*
Date DateUtils::StringToDate(std::string dateTime, std::string fromTimeZone) {
    try {
        TimeZone timeZone = TimeZone.getTimeZone(fromTimeZone);

        if(timeZone == null)
            throw AwesomeNotificationException("Invalid time zone");

        SimpleDateFormat simpleDateFormat = new SimpleDateFormat(Definitions::DATE_FORMAT, Locale.US);
        simpleDateFormat.setTimeZone(timeZone);

        return simpleDateFormat.parse(dateTime);
    } catch (std::exception& e) {
        //e.printStackTrace();
        throw AwesomeNotificationException("Invalid date");
    }
}

std::string DateUtils::DateToString(Date dateTime, std::string fromTimeZone) {
    TimeZone timeZone = TimeZone.getTimeZone(fromTimeZone);

    if(timeZone == null)
        throw AwesomeNotificationException("Invalid time zone");

    SimpleDateFormat simpleDateFormat = new SimpleDateFormat(Definitions::DATE_FORMAT, Locale.US);
    simpleDateFormat.setTimeZone(timeZone);

    return simpleDateFormat.format(dateTime);
}

std::string DateUtils::GetLocalDate(std::string fromTimeZone) {
    TimeZone timeZone = (fromTimeZone == null) ?
            localTimeZone :
            TimeZone.getTimeZone(fromTimeZone);

    if(timeZone == null)
        throw AwesomeNotificationException("Invalid time zone");

    Calendar calendar = Calendar.getInstance();
    calendar.setTimeZone(timeZone);

    SimpleDateFormat simpleDateFormat = new SimpleDateFormat(Definitions::DATE_FORMAT, Locale.US);
    simpleDateFormat.setTimeZone(timeZone);

    return simpleDateFormat.format(calendar.getTime());
}

Date DateUtils::ShiftToTimeZone(Date date, TimeZone timeZone) {
    timeZone = (timeZone == null) ? utcTimeZone : timeZone;

    Calendar calendar = Calendar.getInstance();
    calendar.setTime(date);
    calendar.setTimeZone(timeZone);

    SimpleDateFormat simpleDateFormat = new SimpleDateFormat(Definitions::DATE_FORMAT, Locale.US);
    simpleDateFormat.setTimeZone(timeZone);

    return calendar.getTime();
}
*/

std::string DateUtils::GetUTCDate() {
    time_t now;
	struct tm tm;

	time ( &now );
	//localtime_s( &tm, &now );

    std::stringstream ss;

    gmtime_s(&tm, &now);
    tm.tm_isdst = -1;
    //auto utc = std::mktime(&tm);
    char buf[30];
    std::strftime(buf, sizeof(buf), Definitions::DATE_FORMAT.c_str(), &tm);
    ss << buf;
    //auto utc_field = *gmtime_s(&tm, &utc);
    //std::strftime(buf, sizeof(buf), Definitions::DATE_FORMAT, &utc_field);
    //ss << buf;

    return ss.str();
}

std::string DateUtils::GetLocalTimeZoneString() {
    time_t now;
	struct tm tm;

	time ( &now );
	localtime_s( &tm, &now );

    std::stringstream ss;
    ss << std::put_time(&tm, "%Z");
    return ss.str();
}

std::string DateUtils::GetLocalTimeZoneId() {
    time_t now;
	struct tm tm;

	time ( &now );
	localtime_s( &tm, &now );

    std::stringstream ss;
    ss << std::put_time(&tm, "%z");
    return ss.str();
}

/*
Date DateUtils::GetUTCDateTime() {
    Calendar calendar = Calendar.getInstance();
    calendar.setTimeZone(utcTimeZone);
    return calendar.getTime();
}

Date DateUtils::GetLocalDateTime(std::string fromTimeZone) {
    TimeZone timeZone;

    if(fromTimeZone == null)
        timeZone = localTimeZone;
    else
        timeZone = TimeZone.getTimeZone(fromTimeZone);

    if(timeZone == null)
        throw AwesomeNotificationException("Invalid time zone");

    Calendar calendar = Calendar.getInstance();
    calendar.setTimeZone(timeZone);
    return calendar.getTime();
}
*/