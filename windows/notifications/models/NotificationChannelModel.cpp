#include "NotificationChannelModel.h"

#include "../exceptions/AwesomeNotificationException.h"
#include "../../utils/StringUtils.h"

void NotificationChannelModel::RefreshIconResource() {
    /*
    if(iconResourceId == null && icon != nullptr){
        if(MediaUtils.getMediaSourceType(icon) == MediaSource.Resource) {

            int resourceIndex = BitmapUtils.getDrawableResourceId(icon);
            if (resourceIndex > 0) {
                iconResourceId = resourceIndex;
            } else {
                iconResourceId = null;
            }
        }
    }
    */
}

bool NotificationChannelModel::IsChannelEnabled() {
    return importance.has_value() && importance.value() != NotificationImportance::None;
}

std::string NotificationChannelModel::GetChannelHashKey(bool fullHashObject) {

    RefreshIconResource();

    if(fullHashObject){
        std::string jsonData = this->ToJson();
        return StringUtils::DigestString(jsonData);
    }

    NotificationChannelModel channelCopied = this->Clone();
    channelCopied.channelName = "";
    channelCopied.channelDescription = "";
    channelCopied.groupKey = nullptr;

    std::string jsonData = channelCopied.ToJson();
    return channelKey + "_" + StringUtils::DigestString(jsonData);
}

// bool equals(@Nullable Object obj) {
//     if(super.equals(obj)) return true;
//     if(!(obj instanceof NotificationChannelModel)) return false;
//     NotificationChannelModel other = (NotificationChannelModel) obj;

//     return
//         CompareUtils.assertEqualObjects(other.iconResourceId, this->iconResourceId) &&
//         CompareUtils.assertEqualObjects(other.defaultColor, this->defaultColor) &&
//         CompareUtils.assertEqualObjects(other.channelKey, this->channelKey) &&
//         CompareUtils.assertEqualObjects(other.channelName, this->channelName) &&
//         CompareUtils.assertEqualObjects(other.channelDescription, this->channelDescription) &&
//         CompareUtils.assertEqualObjects(other.channelShowBadge, this->channelShowBadge) &&
//         CompareUtils.assertEqualObjects(other.importance, this->importance) &&
//         CompareUtils.assertEqualObjects(other.playSound, this->playSound) &&
//         CompareUtils.assertEqualObjects(other.soundSource, this->soundSource) &&
//         CompareUtils.assertEqualObjects(other.enableVibration, this->enableVibration) &&
//         CompareUtils.assertEqualObjects(other.vibrationPattern, this->vibrationPattern) &&
//         CompareUtils.assertEqualObjects(other.enableLights, this->enableLights) &&
//         CompareUtils.assertEqualObjects(other.ledColor, this->ledColor) &&
//         CompareUtils.assertEqualObjects(other.ledOnMs, this->ledOnMs) &&
//         CompareUtils.assertEqualObjects(other.ledOffMs, this->ledOffMs) &&
//         CompareUtils.assertEqualObjects(other.groupKey, this->groupKey) &&
//         CompareUtils.assertEqualObjects(other.locked, this->locked) &&
//         CompareUtils.assertEqualObjects(other.criticalAlerts, this->criticalAlerts) &&
//         CompareUtils.assertEqualObjects(other.onlyAlertOnce, this->onlyAlertOnce) &&
//         CompareUtils.assertEqualObjects(other.defaultPrivacy, this->defaultPrivacy) &&
//         CompareUtils.assertEqualObjects(other.defaultRingtoneType, this->defaultRingtoneType) &&
//         CompareUtils.assertEqualObjects(other.groupSort, this->groupSort) &&
//         CompareUtils.assertEqualObjects(other.groupAlertBehavior, this->groupAlertBehavior);
// }
void NotificationChannelModel::FromMap(const flutter::EncodableMap& arguments) {

    iconResourceId = GetValueOrDefault<int>(arguments, Definitions::NOTIFICATION_ICON_RESOURCE_ID, 0);
    icon           = GetValueOrDefault<std::string>(arguments, Definitions::NOTIFICATION_ICON, "");

/*
    if(icon != nullptr) {
        if(MediaUtils.getMediaSourceType(icon) != MediaSource.Resource){
            icon = null;
        }
    }
    */

    defaultColor = GetValueOrDefault<int64_t>(arguments, Definitions::NOTIFICATION_DEFAULT_COLOR, 0);

    channelKey         = GetValueOrDefault<std::string>(arguments, Definitions::NOTIFICATION_CHANNEL_KEY, "");
    channelName        = GetValueOrDefault<std::string>(arguments, Definitions::NOTIFICATION_CHANNEL_NAME, "");
    channelDescription = GetValueOrDefault<std::string>(arguments, Definitions::NOTIFICATION_CHANNEL_DESCRIPTION, "");
    channelShowBadge   = GetValueOrDefault<bool>(arguments, Definitions::NOTIFICATION_CHANNEL_SHOW_BADGE, false);

    channelGroupKey    = GetValueOrDefault<std::string>(arguments, Definitions::NOTIFICATION_CHANNEL_GROUP_KEY, "");

    playSound = GetValueOrDefault<bool>(arguments, Definitions::NOTIFICATION_PLAY_SOUND, false);
    soundSource = GetValueOrDefault<std::string>(arguments, Definitions::NOTIFICATION_SOUND_SOURCE, "");

    criticalAlerts   = GetValueOrDefault<bool>(arguments, Definitions::NOTIFICATION_CHANNEL_CRITICAL_ALERTS, false);

    enableVibration  = GetValueOrDefault<bool>(arguments, Definitions::NOTIFICATION_ENABLE_VIBRATION, false);
    //vibrationPattern = GetValueOrDefault<>(arguments, Definitions::NOTIFICATION_VIBRATION_PATTERN, int64_t[].class);

    ledColor     = GetValueOrDefault<int>(arguments, Definitions::NOTIFICATION_LED_COLOR, 0);
    enableLights = GetValueOrDefault<bool>(arguments, Definitions::NOTIFICATION_ENABLE_LIGHTS, false);
    ledOnMs      = GetValueOrDefault<int>(arguments, Definitions::NOTIFICATION_LED_ON_MS, 0);
    ledOffMs     = GetValueOrDefault<int>(arguments, Definitions::NOTIFICATION_LED_OFF_MS, 0);

    importance = GetEnumValueOrDefault<NotificationImportance>(arguments, Definitions::NOTIFICATION_IMPORTANCE);

    groupSort = GetEnumValueOrDefault<GroupSort>(arguments, Definitions::NOTIFICATION_GROUP_SORT);

    groupAlertBehavior = GetEnumValueOrDefault<GroupAlertBehaviour>(arguments, Definitions::NOTIFICATION_GROUP_ALERT_BEHAVIOR);

    defaultPrivacy = GetEnumValueOrDefault<NotificationPrivacy>(arguments, Definitions::NOTIFICATION_DEFAULT_PRIVACY);

    defaultRingtoneType = GetEnumValueOrDefault<DefaultRingtoneType>(arguments, Definitions::NOTIFICATION_DEFAULT_RINGTONE_TYPE);

    groupKey = GetValueOrDefault<std::string>(arguments, Definitions::NOTIFICATION_GROUP_KEY);

    locked = GetValueOrDefault<bool>(arguments, Definitions::NOTIFICATION_LOCKED, false);
    onlyAlertOnce = GetValueOrDefault<bool>(arguments, Definitions::NOTIFICATION_ONLY_ALERT_ONCE, false);
}

flutter::EncodableValue NotificationChannelModel::ToMap() const {
    flutter::EncodableMap returnedObject;

    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_ICON_RESOURCE_ID), flutter::EncodableValue(this->iconResourceId)));

    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_ICON), flutter::EncodableValue(this->icon)));

    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_DEFAULT_COLOR), flutter::EncodableValue(this->defaultColor)));
        returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_CHANNEL_KEY), flutter::EncodableValue(this->channelKey)));
        returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_CHANNEL_NAME), flutter::EncodableValue(this->channelName)));
        returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_CHANNEL_DESCRIPTION), flutter::EncodableValue(this->channelDescription)));
    //if(this->channelShowBadge != nullptr)
        returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_CHANNEL_SHOW_BADGE), flutter::EncodableValue(this->channelShowBadge)));

    //if(this->channelGroupKey != nullptr)
        returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_CHANNEL_GROUP_KEY), flutter::EncodableValue(this->channelGroupKey)));

    //if(this->playSound != nullptr)
        returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_PLAY_SOUND), flutter::EncodableValue(this->playSound)));
    //if(this->soundSource != nullptr)
        returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_SOUND_SOURCE), flutter::EncodableValue(this->soundSource)));

    //if(this->enableVibration != nullptr)
        returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_ENABLE_VIBRATION), flutter::EncodableValue(this->enableVibration)));
    //if(this->vibrationPattern != nullptr)
        returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_VIBRATION_PATTERN), flutter::EncodableValue(this->vibrationPattern)));

    //if(this->enableLights != nullptr)
        returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_ENABLE_LIGHTS), flutter::EncodableValue(this->enableLights)));
    //if(this->ledColor != nullptr)
        returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_LED_COLOR), flutter::EncodableValue(this->ledColor)));
    //if(this->ledOnMs != nullptr)
        returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_LED_ON_MS), flutter::EncodableValue(this->ledOnMs)));
    //if(this->ledOffMs != nullptr)
        returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_LED_OFF_MS), flutter::EncodableValue(this->ledOffMs)));

    if(this->groupKey)
        returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_GROUP_KEY), flutter::EncodableValue(this->groupKey.value())));

    if(this->groupSort.has_value())
        returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_GROUP_SORT), flutter::EncodableValue(GroupSortToString(this->groupSort.value()))));

    if(this->importance.has_value())
        returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_IMPORTANCE), flutter::EncodableValue(NotificationImportanceToString(this->importance.value()))));

    if(this->groupAlertBehavior.has_value())
        returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_GROUP_ALERT_BEHAVIOR), flutter::EncodableValue(GroupAlertBehaviourToString(this->groupAlertBehavior.value()))));

    if(this->defaultPrivacy.has_value())
        returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_DEFAULT_PRIVACY), flutter::EncodableValue(NotificationPrivacyToString(this->defaultPrivacy.value()))));

    if(this->defaultRingtoneType.has_value())
        returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_DEFAULT_RINGTONE_TYPE), flutter::EncodableValue(DefaultRingtoneTypeToString(this->defaultRingtoneType.value()))));

    //if(this->locked != nullptr)
        returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_LOCKED), flutter::EncodableValue(this->locked)));
    //if(this->onlyAlertOnce != nullptr)
        returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_ONLY_ALERT_ONCE), flutter::EncodableValue(this->onlyAlertOnce)));

    if(this->criticalAlerts)
        returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_CHANNEL_CRITICAL_ALERTS), flutter::EncodableValue(this->criticalAlerts)));

    return returnedObject;
}

std::string NotificationChannelModel::ToJson() const {
    return TemplateToJson();
}

void NotificationChannelModel::FromJson(const std::string& json) {
    if(json.empty()) {
        return;
    }

    flutter::EncodableMap map = JsonUtils::FromJson(json);
    FromMap(map);
}

void NotificationChannelModel::Validate() const {
    if(channelKey.empty())
        throw AwesomeNotificationException("Channel key cannot be null or empty");

    if(channelName.empty())
        throw AwesomeNotificationException("Channel name cannot be null or empty");

    if(channelDescription.empty())
        throw AwesomeNotificationException("Channel description cannot be null or empty");

/*
    if(BooleanUtils.getValue(playSound) && !StringUtils.isNullOrEmpty(soundSource))
        if(!AudioUtils.isValidAudio(soundSource))
            throw AwesomeNotificationException("Audio media is not valid");
            */
}

NotificationChannelModel NotificationChannelModel::Clone() {
    NotificationChannelModel cloned;

    cloned.iconResourceId = this->iconResourceId;
    cloned.defaultColor = this->defaultColor;
    cloned.channelKey = this->channelKey;
    cloned.channelName = this->channelName;
    cloned.channelDescription = this->channelDescription;
    cloned.channelShowBadge = this->channelShowBadge;
    cloned.importance = this->importance;
    cloned.playSound = this->playSound;
    cloned.soundSource = this->soundSource;
    cloned.enableVibration = this->enableVibration;
    cloned.vibrationPattern = this->vibrationPattern;
    cloned.enableLights = this->enableLights;
    cloned.ledColor = this->ledColor;
    cloned.ledOnMs = this->ledOnMs;
    cloned.ledOffMs = this->ledOffMs;
    cloned.groupKey = this->groupKey;
    cloned.locked = this->locked;
    cloned.onlyAlertOnce = this->onlyAlertOnce;
    cloned.defaultPrivacy = this->defaultPrivacy;
    cloned.defaultRingtoneType = this->defaultRingtoneType;
    cloned.groupSort = this->groupSort;
    cloned.groupAlertBehavior = this->groupAlertBehavior;
    cloned.criticalAlerts = this->criticalAlerts;

    return cloned;
}