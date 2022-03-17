#pragma once

#include <flutter/encodable_value.h>

#include <string>
#include <map>

#include "notifications/enums/NotificationImportance.h"
#include "notifications/enums/NotificationLayout.h"
#include "notifications/enums/GroupSort.h"
#include "notifications/enums/GroupAlertBehaviour.h"
#include "notifications/enums/NotificationPrivacy.h"
#include "notifications/enums/ActionButtonType.h"
#include "notifications/enums/DefaultRingtoneType.h"
#include "utils/DateUtils.h"

class Definitions {
 private:
    Definitions(){};
 public:
    static inline std::string BROADCAST_FCM_TOKEN = "me.carda.awesome_notifications.services.firebase.TOKEN";
    static inline std::string EXTRA_BROADCAST_FCM_TOKEN = "token";
    static inline std::string EXTRA_ANDROID_MEDIA_BUTTON = "android.intent.action.MEDIA_BUTTON";

    static inline std::string MEDIA_VALID_NETWORK = "^https?:\\/\\/"; //(www)?(\\.?[a-zA-Z0-9@:%.\\-_\\+~#=]{2),256}\\/?)+(\\?\\S+)$
    static inline std::string MEDIA_VALID_FILE = "^file?:\\/\\/";
    static inline std::string MEDIA_VALID_ASSET = "^asset?:\\/\\/";
    static inline std::string MEDIA_VALID_RESOURCE = "^resource?:\\/\\/";

    static inline std::string BADGE_COUNT = "badgeCount";
    static inline std::string INITIALIZE_DEBUG_MODE = "debug";
    static inline std::string INITIALIZE_DEFAULT_ICON = "defaultIcon";
    static inline std::string INITIALIZE_CHANNELS = "initializeChannels";
    static inline std::string INITIALIZE_CHANNEL_GROUPS = "initializeChannelGroups";

    static inline std::string BROADCAST_CREATED_NOTIFICATION   = "broadcast.awesome_notifications.CREATED_NOTIFICATION";
    static inline std::string BROADCAST_DISPLAYED_NOTIFICATION = "broadcast.awesome_notifications.DISPLAYED_NOTIFICATION";
    static inline std::string BROADCAST_DISMISSED_NOTIFICATION = "broadcast.awesome_notifications.DISMISSED_NOTIFICATION";
    static inline std::string BROADCAST_MEDIA_BUTTON = "broadcast.awesome_notifications.MEDIA_BUTTON";
    static inline std::string BROADCAST_KEEP_ON_TOP ="broadcast.awesome_notifications.KEEP_ON_TOP";
    static inline std::string EXTRA_BROADCAST_MESSAGE = "notification";

    static inline std::string NOTIFICATION_MODEL_CONTENT = "content";
    static inline std::string NOTIFICATION_MODEL_SCHEDULE = "schedule";
    static inline std::string NOTIFICATION_MODEL_BUTTONS = "actionButtons";

    static inline std::string SHARED_DEFAULTS = "defaults";
    static inline std::string SHARED_MANAGER = "sharedManager";
    static inline std::string SHARED_CHANNELS = "channels";
    static inline std::string SHARED_CREATED = "created";
    static inline std::string SHARED_CHANNEL_GROUP = "channelGroup";
    static inline std::string SHARED_DISPLAYED = "displayed";
    static inline std::string SHARED_DISMISSED = "dismissed";
    static inline std::string SHARED_SCHEDULED_NOTIFICATIONS = "schedules";

    static inline std::string CHANNEL_FLUTTER_PLUGIN = "awesome_notifications";

    static inline std::string CHANNEL_METHOD_INITIALIZE = "initialize";
    static inline std::string CHANNEL_METHOD_GET_DRAWABLE_DATA = "getDrawableData";
    static inline std::string CHANNEL_METHOD_ENABLE_WAKELOCK = "enableWakelock";
    static inline std::string CHANNEL_METHOD_CREATE_NOTIFICATION = "createNewNotification";

    static inline std::string CHANNEL_METHOD_GET_UTC_TIMEZONE_IDENTIFIER = "getUtcTimeZoneIdentifier";
    static inline std::string CHANNEL_METHOD_GET_LOCAL_TIMEZONE_IDENTIFIER = "getLocalTimeZoneIdentifier";

    static inline std::string CHANNEL_METHOD_GET_FCM_TOKEN = "getFirebaseToken";
    static inline std::string CHANNEL_METHOD_NEW_FCM_TOKEN = "newTokenReceived";
    static inline std::string CHANNEL_METHOD_IS_FCM_AVAILABLE = "isFirebaseAvailable";

    static inline std::string CHANNEL_METHOD_SET_NOTIFICATION_CHANNEL = "setNotificationChannel";
    static inline std::string CHANNEL_METHOD_REMOVE_NOTIFICATION_CHANNEL = "removeNotificationChannel";

    static inline std::string CHANNEL_METHOD_SHOW_NOTIFICATION_PAGE = "showNotificationPage";
    static inline std::string CHANNEL_METHOD_SHOW_ALARM_PAGE = "showAlarmPage";
    static inline std::string CHANNEL_METHOD_SHOW_GLOBAL_DND_PAGE = "showGlobalDndPage";
    static inline std::string CHANNEL_METHOD_IS_NOTIFICATION_ALLOWED = "isNotificationAllowed";
    static inline std::string CHANNEL_METHOD_REQUEST_NOTIFICATIONS = "requestNotifications";
    static inline std::string CHANNEL_METHOD_CHECK_PERMISSIONS = "checkPermissions";
    static inline std::string CHANNEL_METHOD_SHOULD_SHOW_RATIONALE = "shouldShowRationale";

    static inline std::string CHANNEL_METHOD_GET_BADGE_COUNT = "getBadgeCount";
    static inline std::string CHANNEL_METHOD_SET_BADGE_COUNT = "setBadgeCount";
    static inline std::string CHANNEL_METHOD_INCREMENT_BADGE_COUNT = "incBadgeCount";
    static inline std::string CHANNEL_METHOD_DECREMENT_BADGE_COUNT = "decBadgeCount";
    static inline std::string CHANNEL_METHOD_RESET_BADGE = "resetBadge";

    static inline std::string CHANNEL_METHOD_GET_NEXT_DATE = "getNextDate";
    static inline std::string CHANNEL_METHOD_DISMISS_NOTIFICATION = "dismissNotification";
    static inline std::string CHANNEL_METHOD_CANCEL_NOTIFICATION = "cancelNotification";
    static inline std::string CHANNEL_METHOD_CANCEL_SCHEDULE = "cancelSchedule";
    static inline std::string CHANNEL_METHOD_DISMISS_NOTIFICATIONS_BY_CHANNEL_KEY = "dismissNotificationsByChannelKey";
    static inline std::string CHANNEL_METHOD_CANCEL_NOTIFICATIONS_BY_CHANNEL_KEY = "cancelNotificationsByChannelKey";
    static inline std::string CHANNEL_METHOD_CANCEL_SCHEDULES_BY_CHANNEL_KEY = "cancelSchedulesByChannelKey";
    static inline std::string CHANNEL_METHOD_DISMISS_NOTIFICATIONS_BY_GROUP_KEY = "dismissNotificationsByGroupKey";
    static inline std::string CHANNEL_METHOD_CANCEL_NOTIFICATIONS_BY_GROUP_KEY = "cancelNotificationsByGroupKey";
    static inline std::string CHANNEL_METHOD_CANCEL_SCHEDULES_BY_GROUP_KEY = "cancelSchedulesByGroupKey";
    static inline std::string CHANNEL_METHOD_DISMISS_ALL_NOTIFICATIONS = "dismissAllNotifications";
    static inline std::string CHANNEL_METHOD_CANCEL_ALL_SCHEDULES = "cancelAllSchedules";
    static inline std::string CHANNEL_METHOD_CANCEL_ALL_NOTIFICATIONS = "cancelAllNotifications";

    static inline std::string CHANNEL_METHOD_NOTIFICATION_CREATED = "notificationCreated";
    static inline std::string CHANNEL_METHOD_NOTIFICATION_DISPLAYED = "notificationDisplayed";
    static inline std::string CHANNEL_METHOD_NOTIFICATION_DISMISSED = "notificationDismissed";
    static inline std::string CHANNEL_METHOD_RECEIVED_ACTION = "receivedAction";
    static inline std::string CHANNEL_METHOD_MEDIA_BUTTON = "mediaButton";

    static inline std::string CHANNEL_METHOD_START_FOREGROUND = "startForeground";
    static inline std::string CHANNEL_METHOD_STOP_FOREGROUND = "stopForeground";

    static inline std::string CHANNEL_METHOD_LIST_ALL_SCHEDULES = "listAllSchedules";
    static inline std::string CHANNEL_FORCE_UPDATE = "forceUpdate";

    static inline std::string FIREBASE_ENABLED = "FIREBASE_ENABLED";
    static inline std::string SELECT_NOTIFICATION = "SELECT_NOTIFICATION";
    static inline std::string DISMISSED_NOTIFICATION = "DISMISSED_NOTIFICATION";
    static inline std::string MEDIA_BUTTON = "MEDIA_BUTTON";
    static inline std::string NOTIFICATION_BUTTON_ACTION_PREFIX = "ACTION_NOTIFICATION";

    static inline std::string SHARED_PREFERENCES_CHANNEL_MANAGER = "channel_manager";

    static inline std::string DATE_FORMAT = "%Y-%m-%d %X";

    static inline std::string NOTIFICATION_ICON_RESOURCE_ID = "iconResourceId";

    static inline std::string NOTIFICATION_SCHEDULE_CREATED_DATE = "createdDate";
    static inline std::string NOTIFICATION_SCHEDULE_ERA = "era";
    static inline std::string NOTIFICATION_SCHEDULE_TIMEZONE = "timeZone";
    static inline std::string NOTIFICATION_SCHEDULE_PRECISE_ALARM = "preciseAlarm";
    static inline std::string NOTIFICATION_SCHEDULE_YEAR = "year";
    static inline std::string NOTIFICATION_SCHEDULE_MONTH = "month";
    static inline std::string NOTIFICATION_SCHEDULE_DAY = "day";
    static inline std::string NOTIFICATION_SCHEDULE_HOUR = "hour";
    static inline std::string NOTIFICATION_SCHEDULE_MINUTE = "minute";
    static inline std::string NOTIFICATION_SCHEDULE_SECOND = "second";
    static inline std::string NOTIFICATION_SCHEDULE_MILLISECOND = "millisecond";
    static inline std::string NOTIFICATION_SCHEDULE_WEEKDAY = "weekday";
    static inline std::string NOTIFICATION_SCHEDULE_WEEKOFMONTH = "weekOfMonth";
    static inline std::string NOTIFICATION_SCHEDULE_WEEKOFYEAR = "weekOfYear";
    static inline std::string NOTIFICATION_SCHEDULE_INTERVAL = "interval";
    static inline std::string NOTIFICATION_SCHEDULE_REPEATS = "repeats";

    static inline std::string NOTIFICATION_CREATED_SOURCE = "createdSource";
    static inline std::string NOTIFICATION_CREATED_LIFECYCLE = "createdLifeCycle";
    static inline std::string NOTIFICATION_DISPLAYED_LIFECYCLE = "displayedLifeCycle";
    static inline std::string NOTIFICATION_DISMISSED_LIFECYCLE = "dismissedLifeCycle";
    static inline std::string NOTIFICATION_ACTION_LIFECYCLE = "actionLifeCycle";
    static inline std::string NOTIFICATION_CREATED_DATE = "createdDate";
    static inline std::string NOTIFICATION_ACTION_DATE = "actionDate";
    static inline std::string NOTIFICATION_DISPLAYED_DATE = "displayedDate";
    static inline std::string NOTIFICATION_DISMISSED_DATE = "dismissedDate";

    static inline std::string NOTIFICATION_ID = "id";
    static inline std::string NOTIFICATION_RANDOM_ID = "randomId";
    static inline std::string NOTIFICATION_LAYOUT = "notificationLayout";
    static inline std::string NOTIFICATION_TITLE = "title";
    static inline std::string NOTIFICATION_BODY = "body";
    static inline std::string NOTIFICATION_TIMESTAMP = "timestamp";
    static inline std::string NOTIFICATION_SUMMARY = "summary";
    static inline std::string NOTIFICATION_SHOW_WHEN = "showWhen";
    static inline std::string NOTIFICATION_BUTTON_KEY_PRESSED = "buttonKeyPressed";
    static inline std::string NOTIFICATION_BUTTON_KEY_INPUT = "buttonKeyInput";
    static inline std::string NOTIFICATION_JSON = "notificationJson";

    static inline std::string NOTIFICATION_MESSAGES = "messages";
    static inline std::string NOTIFICATION_BUTTON_KEY = "key";
    static inline std::string NOTIFICATION_BUTTON_ICON = "icon";
    static inline std::string NOTIFICATION_BUTTON_LABEL = "label";
    static inline std::string NOTIFICATION_BUTTON_TYPE = "buttonType";

    static inline std::string NOTIFICATION_PAYLOAD = "payload";
    static inline std::string NOTIFICATION_INITIAL_FIXED_DATE = "fixedDate";

    static inline std::string NOTIFICATION_ROUNDED_LARGE_ICON = "roundedLargeIcon";
    static inline std::string NOTIFICATION_ROUNDED_BIG_PICTURE = "roundedBigPicture";

    static inline std::string NOTIFICATION_INITIAL_DATE_TIME = "initialDateTime";
    static inline std::string NOTIFICATION_EXPIRATION_DATE_TIME = "expirationDateTime";
    static inline std::string NOTIFICATION_CRONTAB_EXPRESSION = "crontabExpression";
    static inline std::string NOTIFICATION_PRECISE_SCHEDULES = "preciseSchedules";
    static inline std::string NOTIFICATION_ENABLED = "enabled";
    static inline std::string NOTIFICATION_AUTO_DISMISSIBLE = "autoDismissible";
    static inline std::string NOTIFICATION_IS_DANGEROUS_OPTION = "isDangerousOption";
    static inline std::string NOTIFICATION_PERMISSIONS = "permissions";

    static inline std::string NOTIFICATION_SHOW_IN_COMPACT_VIEW = "showInCompactView";
    static inline std::string NOTIFICATION_LOCKED = "locked";
    static inline std::string NOTIFICATION_DISPLAY_ON_FOREGROUND = "displayOnForeground";
    static inline std::string NOTIFICATION_DISPLAY_ON_BACKGROUND = "displayOnBackground";
    static inline std::string NOTIFICATION_ICON = "icon";
    static inline std::string NOTIFICATION_FULL_SCREEN_INTENT = "fullScreenIntent";
    static inline std::string NOTIFICATION_WAKE_UP_SCREEN = "wakeUpScreen";
    static inline std::string NOTIFICATION_PLAY_SOUND = "playSound";
    static inline std::string NOTIFICATION_SOUND_SOURCE = "soundSource";
    static inline std::string NOTIFICATION_ENABLE_VIBRATION = "enableVibration";
    static inline std::string NOTIFICATION_VIBRATION_PATTERN = "vibrationPattern";
    static inline std::string NOTIFICATION_GROUP_KEY = "groupKey";
    static inline std::string NOTIFICATION_GROUP_SORT = "groupSort";
    static inline std::string NOTIFICATION_GROUP_ALERT_BEHAVIOR = "groupAlertBehavior";
    static inline std::string NOTIFICATION_PRIVACY = "privacy";
    static inline std::string NOTIFICATION_CATEGORY = "category";
    static inline std::string NOTIFICATION_CUSTOM_SOUND = "customSound";
    static inline std::string NOTIFICATION_DEFAULT_PRIVACY = "defaultPrivacy";
    static inline std::string NOTIFICATION_DEFAULT_RINGTONE_TYPE = "defaultRingtoneType";
    static inline std::string NOTIFICATION_PRIVATE_MESSAGE = "privateMessage";
    static inline std::string NOTIFICATION_ONLY_ALERT_ONCE = "onlyAlertOnce";
    static inline std::string NOTIFICATION_CHANNEL_KEY = "channelKey";
    static inline std::string NOTIFICATION_CHANNEL_NAME = "channelName";
    static inline std::string NOTIFICATION_CHANNEL_DESCRIPTION = "channelDescription";
    static inline std::string NOTIFICATION_CHANNEL_SHOW_BADGE = "channelShowBadge";
    static inline std::string NOTIFICATION_CHANNEL_GROUP_NAME = "channelGroupName";
    static inline std::string NOTIFICATION_CHANNEL_GROUP_KEY = "channelGroupKey";
    static inline std::string NOTIFICATION_CHANNEL_CRITICAL_ALERTS = "criticalAlerts";
    static inline std::string NOTIFICATION_IMPORTANCE = "importance";
    static inline std::string NOTIFICATION_COLOR = "color";
    static inline std::string NOTIFICATION_BACKGROUND_COLOR = "backgroundColor";
    static inline std::string NOTIFICATION_DEFAULT_COLOR = "defaultColor";
    static inline std::string NOTIFICATION_APP_ICON = "defaultIcon";
    static inline std::string NOTIFICATION_LARGE_ICON = "largeIcon";
    static inline std::string NOTIFICATION_BIG_PICTURE = "bigPicture";
    static inline std::string NOTIFICATION_HIDE_LARGE_ICON_ON_EXPAND = "hideLargeIconOnExpand";
    static inline std::string NOTIFICATION_PROGRESS = "progress";
    static inline std::string NOTIFICATION_ENABLE_LIGHTS = "enableLights";
    static inline std::string NOTIFICATION_LED_COLOR = "ledColor";
    static inline std::string NOTIFICATION_LED_ON_MS = "ledOnMs";
    static inline std::string NOTIFICATION_LED_OFF_MS = "ledOffMs";
    static inline std::string NOTIFICATION_TICKER = "ticker";
    static inline std::string NOTIFICATION_ALLOW_WHILE_IDLE = "allowWhileIdle";

    static inline flutter::EncodableMap initialValues = {
        {flutter::EncodableValue(Definitions::FIREBASE_ENABLED), flutter::EncodableValue(true)},
        {flutter::EncodableValue(Definitions::NOTIFICATION_SCHEDULE_REPEATS), flutter::EncodableValue(true)},
        {flutter::EncodableValue(Definitions::NOTIFICATION_ID), flutter::EncodableValue(0)},
        {flutter::EncodableValue(Definitions::NOTIFICATION_IMPORTANCE), flutter::EncodableValue((int)NotificationImportance::Default)},
        {flutter::EncodableValue(Definitions::NOTIFICATION_LAYOUT), flutter::EncodableValue((int)NotificationLayout::Default)},
        {flutter::EncodableValue(Definitions::NOTIFICATION_GROUP_SORT), flutter::EncodableValue((int)GroupSort::Desc)},
        {flutter::EncodableValue(Definitions::NOTIFICATION_GROUP_ALERT_BEHAVIOR), flutter::EncodableValue((int)GroupAlertBehaviour::All)},
        {flutter::EncodableValue(Definitions::NOTIFICATION_DEFAULT_PRIVACY), flutter::EncodableValue((int)NotificationPrivacy::Private)},
        //{flutter::EncodableValue(Definitions::NOTIFICATION_PRIVACY), flutter::EncodableValue(NotificationPrivacy.Private)},
        {flutter::EncodableValue(Definitions::NOTIFICATION_CHANNEL_KEY), flutter::EncodableValue("miscellaneous")},
        {flutter::EncodableValue(Definitions::NOTIFICATION_CHANNEL_DESCRIPTION), flutter::EncodableValue("Notifications")},
        {flutter::EncodableValue(Definitions::NOTIFICATION_CHANNEL_NAME), flutter::EncodableValue("Notifications")},
        {flutter::EncodableValue(Definitions::NOTIFICATION_CHANNEL_SHOW_BADGE), flutter::EncodableValue(false)},
        {flutter::EncodableValue(Definitions::NOTIFICATION_DISPLAY_ON_FOREGROUND), flutter::EncodableValue(true)},
        {flutter::EncodableValue(Definitions::NOTIFICATION_DISPLAY_ON_BACKGROUND), flutter::EncodableValue(true)},
        {flutter::EncodableValue(Definitions::NOTIFICATION_HIDE_LARGE_ICON_ON_EXPAND), flutter::EncodableValue(false)},
        {flutter::EncodableValue(Definitions::NOTIFICATION_ENABLED), flutter::EncodableValue(true)},
        {flutter::EncodableValue(Definitions::NOTIFICATION_SHOW_WHEN), flutter::EncodableValue(true)},
        {flutter::EncodableValue(Definitions::NOTIFICATION_BUTTON_TYPE), flutter::EncodableValue((int)ActionButtonType::Default)},
        {flutter::EncodableValue(Definitions::NOTIFICATION_PAYLOAD), std::monostate()},
        {flutter::EncodableValue(Definitions::NOTIFICATION_ENABLE_VIBRATION), flutter::EncodableValue(true)},
        {flutter::EncodableValue(Definitions::NOTIFICATION_DEFAULT_COLOR), flutter::EncodableValue((int64_t)0xFF000000)},
        {flutter::EncodableValue(Definitions::NOTIFICATION_LED_COLOR), flutter::EncodableValue((int64_t)0xFFFFFFFF)},
        {flutter::EncodableValue(Definitions::NOTIFICATION_ENABLE_LIGHTS), flutter::EncodableValue(true)},
        {flutter::EncodableValue(Definitions::NOTIFICATION_LED_OFF_MS), flutter::EncodableValue(700)},
        {flutter::EncodableValue(Definitions::NOTIFICATION_LED_ON_MS), flutter::EncodableValue(300)},
        {flutter::EncodableValue(Definitions::NOTIFICATION_PLAY_SOUND), flutter::EncodableValue(true)},
        {flutter::EncodableValue(Definitions::NOTIFICATION_AUTO_DISMISSIBLE), flutter::EncodableValue(true)},
        {flutter::EncodableValue(Definitions::NOTIFICATION_DEFAULT_RINGTONE_TYPE), flutter::EncodableValue((int)DefaultRingtoneType::Notification)},
        {flutter::EncodableValue(Definitions::NOTIFICATION_SCHEDULE_TIMEZONE), flutter::EncodableValue(DateUtils::GetLocalTimeZoneString())},
        {flutter::EncodableValue(Definitions::NOTIFICATION_TICKER), flutter::EncodableValue("ticker")},
        {flutter::EncodableValue(Definitions::NOTIFICATION_ALLOW_WHILE_IDLE), flutter::EncodableValue(false)},
        {flutter::EncodableValue(Definitions::NOTIFICATION_ONLY_ALERT_ONCE), flutter::EncodableValue(false)},
        {flutter::EncodableValue(Definitions::NOTIFICATION_SHOW_IN_COMPACT_VIEW), flutter::EncodableValue(true)},
        {flutter::EncodableValue(Definitions::NOTIFICATION_IS_DANGEROUS_OPTION), flutter::EncodableValue(false)},
        {flutter::EncodableValue(Definitions::NOTIFICATION_WAKE_UP_SCREEN), flutter::EncodableValue(false)},
        {flutter::EncodableValue(Definitions::NOTIFICATION_CHANNEL_CRITICAL_ALERTS), flutter::EncodableValue(false)},
        {flutter::EncodableValue(Definitions::NOTIFICATION_ROUNDED_LARGE_ICON), flutter::EncodableValue(false)},
        {flutter::EncodableValue(Definitions::NOTIFICATION_ROUNDED_BIG_PICTURE), flutter::EncodableValue(false)}
    };
};