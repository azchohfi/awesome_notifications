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
    const static inline std::string BROADCAST_FCM_TOKEN = "me.carda.awesome_notifications.services.firebase.TOKEN";
    const static inline std::string EXTRA_BROADCAST_FCM_TOKEN = "token";
    const static inline std::string EXTRA_ANDROID_MEDIA_BUTTON = "android.intent.action.MEDIA_BUTTON";

    const static inline std::string MEDIA_VALID_NETWORK = R"(^https?://)"; //(www)?(\\.?[a-zA-Z0-9@:%.\\-_\\+~#=]{2),256}\\/?)+(\\?\\S+)$
    const static inline std::string MEDIA_VALID_FILE = R"(^file?://)";
    const static inline std::string MEDIA_VALID_ASSET = R"(^asset?://)";
    const static inline std::string MEDIA_VALID_RESOURCE = R"(^resource?:)";

    const static inline std::string BADGE_COUNT = "badgeCount";
    const static inline std::string INITIALIZE_DEBUG_MODE = "debug";
    const static inline std::string INITIALIZE_DEFAULT_ICON = "defaultIcon";
    const static inline std::string INITIALIZE_CHANNELS = "initializeChannels";
    const static inline std::string INITIALIZE_CHANNEL_GROUPS = "initializeChannelGroups";

    const static inline std::string BROADCAST_CREATED_NOTIFICATION   = "broadcast.awesome_notifications.CREATED_NOTIFICATION";
    const static inline std::string BROADCAST_DISPLAYED_NOTIFICATION = "broadcast.awesome_notifications.DISPLAYED_NOTIFICATION";
    const static inline std::string BROADCAST_DISMISSED_NOTIFICATION = "broadcast.awesome_notifications.DISMISSED_NOTIFICATION";
    const static inline std::string BROADCAST_MEDIA_BUTTON = "broadcast.awesome_notifications.MEDIA_BUTTON";
    const static inline std::string BROADCAST_KEEP_ON_TOP ="broadcast.awesome_notifications.KEEP_ON_TOP";
    const static inline std::string EXTRA_BROADCAST_MESSAGE = "notification";

    const static inline std::string NOTIFICATION_MODEL_CONTENT = "content";
    const static inline std::string NOTIFICATION_MODEL_SCHEDULE = "schedule";
    const static inline std::string NOTIFICATION_MODEL_BUTTONS = "actionButtons";

    const static inline std::string SHARED_DEFAULTS = "defaults";
    const static inline std::string SHARED_MANAGER = "sharedManager";
    const static inline std::string SHARED_CHANNELS = "channels";
    const static inline std::string SHARED_CREATED = "created";
    const static inline std::string SHARED_CHANNEL_GROUP = "channelGroup";
    const static inline std::string SHARED_DISPLAYED = "displayed";
    const static inline std::string SHARED_DISMISSED = "dismissed";
    const static inline std::string SHARED_SCHEDULED_NOTIFICATIONS = "schedules";

    const static inline std::string CHANNEL_FLUTTER_PLUGIN = "awesome_notifications";

    const static inline std::string CHANNEL_METHOD_INITIALIZE = "initialize";
    const static inline std::string CHANNEL_METHOD_GET_DRAWABLE_DATA = "getDrawableData";
    const static inline std::string CHANNEL_METHOD_ENABLE_WAKELOCK = "enableWakelock";
    const static inline std::string CHANNEL_METHOD_CREATE_NOTIFICATION = "createNewNotification";

    const static inline std::string CHANNEL_METHOD_GET_UTC_TIMEZONE_IDENTIFIER = "getUtcTimeZoneIdentifier";
    const static inline std::string CHANNEL_METHOD_GET_LOCAL_TIMEZONE_IDENTIFIER = "getLocalTimeZoneIdentifier";

    const static inline std::string CHANNEL_METHOD_GET_FCM_TOKEN = "getFirebaseToken";
    const static inline std::string CHANNEL_METHOD_NEW_FCM_TOKEN = "newTokenReceived";
    const static inline std::string CHANNEL_METHOD_IS_FCM_AVAILABLE = "isFirebaseAvailable";

    const static inline std::string CHANNEL_METHOD_SET_NOTIFICATION_CHANNEL = "setNotificationChannel";
    const static inline std::string CHANNEL_METHOD_REMOVE_NOTIFICATION_CHANNEL = "removeNotificationChannel";

    const static inline std::string CHANNEL_METHOD_SHOW_NOTIFICATION_PAGE = "showNotificationPage";
    const static inline std::string CHANNEL_METHOD_SHOW_ALARM_PAGE = "showAlarmPage";
    const static inline std::string CHANNEL_METHOD_SHOW_GLOBAL_DND_PAGE = "showGlobalDndPage";
    const static inline std::string CHANNEL_METHOD_IS_NOTIFICATION_ALLOWED = "isNotificationAllowed";
    const static inline std::string CHANNEL_METHOD_REQUEST_NOTIFICATIONS = "requestNotifications";
    const static inline std::string CHANNEL_METHOD_CHECK_PERMISSIONS = "checkPermissions";
    const static inline std::string CHANNEL_METHOD_SHOULD_SHOW_RATIONALE = "shouldShowRationale";

    const static inline std::string CHANNEL_METHOD_GET_BADGE_COUNT = "getBadgeCount";
    const static inline std::string CHANNEL_METHOD_SET_BADGE_COUNT = "setBadgeCount";
    const static inline std::string CHANNEL_METHOD_INCREMENT_BADGE_COUNT = "incBadgeCount";
    const static inline std::string CHANNEL_METHOD_DECREMENT_BADGE_COUNT = "decBadgeCount";
    const static inline std::string CHANNEL_METHOD_RESET_BADGE = "resetBadge";

    const static inline std::string CHANNEL_METHOD_GET_NEXT_DATE = "getNextDate";
    const static inline std::string CHANNEL_METHOD_DISMISS_NOTIFICATION = "dismissNotification";
    const static inline std::string CHANNEL_METHOD_CANCEL_NOTIFICATION = "cancelNotification";
    const static inline std::string CHANNEL_METHOD_CANCEL_SCHEDULE = "cancelSchedule";
    const static inline std::string CHANNEL_METHOD_DISMISS_NOTIFICATIONS_BY_CHANNEL_KEY = "dismissNotificationsByChannelKey";
    const static inline std::string CHANNEL_METHOD_CANCEL_NOTIFICATIONS_BY_CHANNEL_KEY = "cancelNotificationsByChannelKey";
    const static inline std::string CHANNEL_METHOD_CANCEL_SCHEDULES_BY_CHANNEL_KEY = "cancelSchedulesByChannelKey";
    const static inline std::string CHANNEL_METHOD_DISMISS_NOTIFICATIONS_BY_GROUP_KEY = "dismissNotificationsByGroupKey";
    const static inline std::string CHANNEL_METHOD_CANCEL_NOTIFICATIONS_BY_GROUP_KEY = "cancelNotificationsByGroupKey";
    const static inline std::string CHANNEL_METHOD_CANCEL_SCHEDULES_BY_GROUP_KEY = "cancelSchedulesByGroupKey";
    const static inline std::string CHANNEL_METHOD_DISMISS_ALL_NOTIFICATIONS = "dismissAllNotifications";
    const static inline std::string CHANNEL_METHOD_CANCEL_ALL_SCHEDULES = "cancelAllSchedules";
    const static inline std::string CHANNEL_METHOD_CANCEL_ALL_NOTIFICATIONS = "cancelAllNotifications";

    const static inline std::string CHANNEL_METHOD_NOTIFICATION_CREATED = "notificationCreated";
    const static inline std::string CHANNEL_METHOD_NOTIFICATION_DISPLAYED = "notificationDisplayed";
    const static inline std::string CHANNEL_METHOD_NOTIFICATION_DISMISSED = "notificationDismissed";
    const static inline std::string CHANNEL_METHOD_RECEIVED_ACTION = "receivedAction";
    const static inline std::string CHANNEL_METHOD_MEDIA_BUTTON = "mediaButton";

    const static inline std::string CHANNEL_METHOD_START_FOREGROUND = "startForeground";
    const static inline std::string CHANNEL_METHOD_STOP_FOREGROUND = "stopForeground";

    const static inline std::string CHANNEL_METHOD_LIST_ALL_SCHEDULES = "listAllSchedules";
    const static inline std::string CHANNEL_FORCE_UPDATE = "forceUpdate";

    const static inline std::string FIREBASE_ENABLED = "FIREBASE_ENABLED";
    const static inline std::string SELECT_NOTIFICATION = "SELECT_NOTIFICATION";
    const static inline std::string DISMISSED_NOTIFICATION = "DISMISSED_NOTIFICATION";
    const static inline std::string MEDIA_BUTTON = "MEDIA_BUTTON";
    const static inline std::string NOTIFICATION_BUTTON_ACTION_PREFIX = "ACTION_NOTIFICATION";

    const static inline std::string SHARED_PREFERENCES_CHANNEL_MANAGER = "channel_manager";

    const static inline std::string DATE_FORMAT = "%Y-%m-%d %X";

    const static inline std::string NOTIFICATION_ICON_RESOURCE_ID = "iconResourceId";

    const static inline std::string NOTIFICATION_SCHEDULE_CREATED_DATE = "createdDate";
    const static inline std::string NOTIFICATION_SCHEDULE_ERA = "era";
    const static inline std::string NOTIFICATION_SCHEDULE_TIMEZONE = "timeZone";
    const static inline std::string NOTIFICATION_SCHEDULE_PRECISE_ALARM = "preciseAlarm";
    const static inline std::string NOTIFICATION_SCHEDULE_YEAR = "year";
    const static inline std::string NOTIFICATION_SCHEDULE_MONTH = "month";
    const static inline std::string NOTIFICATION_SCHEDULE_DAY = "day";
    const static inline std::string NOTIFICATION_SCHEDULE_HOUR = "hour";
    const static inline std::string NOTIFICATION_SCHEDULE_MINUTE = "minute";
    const static inline std::string NOTIFICATION_SCHEDULE_SECOND = "second";
    const static inline std::string NOTIFICATION_SCHEDULE_MILLISECOND = "millisecond";
    const static inline std::string NOTIFICATION_SCHEDULE_WEEKDAY = "weekday";
    const static inline std::string NOTIFICATION_SCHEDULE_WEEKOFMONTH = "weekOfMonth";
    const static inline std::string NOTIFICATION_SCHEDULE_WEEKOFYEAR = "weekOfYear";
    const static inline std::string NOTIFICATION_SCHEDULE_INTERVAL = "interval";
    const static inline std::string NOTIFICATION_SCHEDULE_REPEATS = "repeats";

    const static inline std::string NOTIFICATION_CREATED_SOURCE = "createdSource";
    const static inline std::string NOTIFICATION_CREATED_LIFECYCLE = "createdLifeCycle";
    const static inline std::string NOTIFICATION_DISPLAYED_LIFECYCLE = "displayedLifeCycle";
    const static inline std::string NOTIFICATION_DISMISSED_LIFECYCLE = "dismissedLifeCycle";
    const static inline std::string NOTIFICATION_ACTION_LIFECYCLE = "actionLifeCycle";
    const static inline std::string NOTIFICATION_CREATED_DATE = "createdDate";
    const static inline std::string NOTIFICATION_ACTION_DATE = "actionDate";
    const static inline std::string NOTIFICATION_DISPLAYED_DATE = "displayedDate";
    const static inline std::string NOTIFICATION_DISMISSED_DATE = "dismissedDate";

    const static inline std::string NOTIFICATION_ID = "id";
    const static inline std::string NOTIFICATION_RANDOM_ID = "randomId";
    const static inline std::string NOTIFICATION_LAYOUT = "notificationLayout";
    const static inline std::string NOTIFICATION_TITLE = "title";
    const static inline std::string NOTIFICATION_BODY = "body";
    const static inline std::string NOTIFICATION_TIMESTAMP = "timestamp";
    const static inline std::string NOTIFICATION_SUMMARY = "summary";
    const static inline std::string NOTIFICATION_SHOW_WHEN = "showWhen";
    const static inline std::string NOTIFICATION_BUTTON_KEY_PRESSED = "buttonKeyPressed";
    const static inline std::string NOTIFICATION_BUTTON_KEY_INPUT = "buttonKeyInput";
    const static inline std::string NOTIFICATION_JSON = "notificationJson";

    const static inline std::string NOTIFICATION_MESSAGES = "messages";
    const static inline std::string NOTIFICATION_BUTTON_KEY = "key";
    const static inline std::string NOTIFICATION_BUTTON_ICON = "icon";
    const static inline std::string NOTIFICATION_BUTTON_LABEL = "label";
    const static inline std::string NOTIFICATION_BUTTON_TYPE = "buttonType";

    const static inline std::string NOTIFICATION_PAYLOAD = "payload";
    const static inline std::string NOTIFICATION_INITIAL_FIXED_DATE = "fixedDate";

    const static inline std::string NOTIFICATION_ROUNDED_LARGE_ICON = "roundedLargeIcon";
    const static inline std::string NOTIFICATION_ROUNDED_BIG_PICTURE = "roundedBigPicture";

    const static inline std::string NOTIFICATION_INITIAL_DATE_TIME = "initialDateTime";
    const static inline std::string NOTIFICATION_EXPIRATION_DATE_TIME = "expirationDateTime";
    const static inline std::string NOTIFICATION_CRONTAB_EXPRESSION = "crontabExpression";
    const static inline std::string NOTIFICATION_PRECISE_SCHEDULES = "preciseSchedules";
    const static inline std::string NOTIFICATION_ENABLED = "enabled";
    const static inline std::string NOTIFICATION_AUTO_DISMISSIBLE = "autoDismissible";
    const static inline std::string NOTIFICATION_IS_DANGEROUS_OPTION = "isDangerousOption";
    const static inline std::string NOTIFICATION_PERMISSIONS = "permissions";

    const static inline std::string NOTIFICATION_SHOW_IN_COMPACT_VIEW = "showInCompactView";
    const static inline std::string NOTIFICATION_LOCKED = "locked";
    const static inline std::string NOTIFICATION_DISPLAY_ON_FOREGROUND = "displayOnForeground";
    const static inline std::string NOTIFICATION_DISPLAY_ON_BACKGROUND = "displayOnBackground";
    const static inline std::string NOTIFICATION_ICON = "icon";
    const static inline std::string NOTIFICATION_FULL_SCREEN_INTENT = "fullScreenIntent";
    const static inline std::string NOTIFICATION_WAKE_UP_SCREEN = "wakeUpScreen";
    const static inline std::string NOTIFICATION_PLAY_SOUND = "playSound";
    const static inline std::string NOTIFICATION_SOUND_SOURCE = "soundSource";
    const static inline std::string NOTIFICATION_ENABLE_VIBRATION = "enableVibration";
    const static inline std::string NOTIFICATION_VIBRATION_PATTERN = "vibrationPattern";
    const static inline std::string NOTIFICATION_GROUP_KEY = "groupKey";
    const static inline std::string NOTIFICATION_GROUP_SORT = "groupSort";
    const static inline std::string NOTIFICATION_GROUP_ALERT_BEHAVIOR = "groupAlertBehavior";
    const static inline std::string NOTIFICATION_PRIVACY = "privacy";
    const static inline std::string NOTIFICATION_CATEGORY = "category";
    const static inline std::string NOTIFICATION_CUSTOM_SOUND = "customSound";
    const static inline std::string NOTIFICATION_DEFAULT_PRIVACY = "defaultPrivacy";
    const static inline std::string NOTIFICATION_DEFAULT_RINGTONE_TYPE = "defaultRingtoneType";
    const static inline std::string NOTIFICATION_PRIVATE_MESSAGE = "privateMessage";
    const static inline std::string NOTIFICATION_ONLY_ALERT_ONCE = "onlyAlertOnce";
    const static inline std::string NOTIFICATION_CHANNEL_KEY = "channelKey";
    const static inline std::string NOTIFICATION_CHANNEL_NAME = "channelName";
    const static inline std::string NOTIFICATION_CHANNEL_DESCRIPTION = "channelDescription";
    const static inline std::string NOTIFICATION_CHANNEL_SHOW_BADGE = "channelShowBadge";
    const static inline std::string NOTIFICATION_CHANNEL_GROUP_NAME = "channelGroupName";
    const static inline std::string NOTIFICATION_CHANNEL_GROUP_KEY = "channelGroupKey";
    const static inline std::string NOTIFICATION_CHANNEL_CRITICAL_ALERTS = "criticalAlerts";
    const static inline std::string NOTIFICATION_IMPORTANCE = "importance";
    const static inline std::string NOTIFICATION_COLOR = "color";
    const static inline std::string NOTIFICATION_BACKGROUND_COLOR = "backgroundColor";
    const static inline std::string NOTIFICATION_DEFAULT_COLOR = "defaultColor";
    const static inline std::string NOTIFICATION_APP_ICON = "defaultIcon";
    const static inline std::string NOTIFICATION_LARGE_ICON = "largeIcon";
    const static inline std::string NOTIFICATION_BIG_PICTURE = "bigPicture";
    const static inline std::string NOTIFICATION_HIDE_LARGE_ICON_ON_EXPAND = "hideLargeIconOnExpand";
    const static inline std::string NOTIFICATION_PROGRESS = "progress";
    const static inline std::string NOTIFICATION_ENABLE_LIGHTS = "enableLights";
    const static inline std::string NOTIFICATION_LED_COLOR = "ledColor";
    const static inline std::string NOTIFICATION_LED_ON_MS = "ledOnMs";
    const static inline std::string NOTIFICATION_LED_OFF_MS = "ledOffMs";
    const static inline std::string NOTIFICATION_TICKER = "ticker";
    const static inline std::string NOTIFICATION_ALLOW_WHILE_IDLE = "allowWhileIdle";

    const static inline flutter::EncodableMap initialValues = {
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