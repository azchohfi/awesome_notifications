#include <optional>

#include "NotificationImportance.h"

std::string NotificationImportanceToString(NotificationImportance notificationImportance) {
    switch (notificationImportance) {
        case NotificationImportance::None:
            return "None";
        case NotificationImportance::Min:
            return "Min";
        case NotificationImportance::Low:
            return "Low";
        case NotificationImportance::Default:
            return "Default";
        case NotificationImportance::High:
            return "High";
        case NotificationImportance::Max:
            return "Max";
    }

    return "None";
}

/*static int ToWindowsPriority(std::optional<NotificationImportance> importance) {
    switch ((!importance.has_value()) ? NotificationImportance::Default : importance.value()){
        case NotificationImportance::None:
        case NotificationImportance::Min: -1;//return NotificationCompat.PRIORITY_MIN;
        case NotificationImportance::Low: -1;//return NotificationCompat.PRIORITY_LOW;
        case NotificationImportance::High: -1;//return NotificationCompat.PRIORITY_HIGH;
        case NotificationImportance::Max: -1;//return NotificationCompat.PRIORITY_MAX;
        case NotificationImportance::Default:
        default:
            return -1;//NotificationCompat.PRIORITY_DEFAULT;
    }
}

static int ToWindowsImportance(std::optional<NotificationImportance> importance) {
    return (int)((!importance.has_value()) ? NotificationImportance::Default : importance.value());
}

static NotificationImportance FromWindowsPriority(int ordinal) {
    if(ordinal < -2) ordinal = -2;
    if(ordinal > 2) ordinal = 2;
    switch (ordinal){
        case 0:
        /*
        case NotificationCompat.PRIORITY_MIN: return NotificationImportance::Min;
        case NotificationCompat.PRIORITY_LOW: return NotificationImportance::Low;
        case NotificationCompat.PRIORITY_HIGH: return NotificationImportance::High;
        case NotificationCompat.PRIORITY_MAX: return NotificationImportance::Max;
        case NotificationCompat.PRIORITY_DEFAULT:
        /
        default: return NotificationImportance::Default;
    }
}

static NotificationImportance FromWindowsImportance(int ordinal) {
    if(ordinal < 0) ordinal = 0;
    if(ordinal > 5) ordinal = 5;
    return (NotificationImportance)ordinal;
}
*/