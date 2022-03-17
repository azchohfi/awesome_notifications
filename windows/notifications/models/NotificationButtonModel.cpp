#include "NotificationButtonModel.h"

#include "../../utils/JsonUtils.h"

NotificationButtonModel::NotificationButtonModel() {

}

void NotificationButtonModel::FromMap(const flutter::EncodableMap& arguments) {
    key        = GetValueOrDefault<std::string>(arguments, Definitions::NOTIFICATION_BUTTON_KEY, "");
    icon       = GetValueOrDefault<std::string>(arguments, Definitions::NOTIFICATION_BUTTON_ICON, "");
    label      = GetValueOrDefault<std::string>(arguments, Definitions::NOTIFICATION_BUTTON_LABEL, "");
    color      = GetValueOrDefault<int>(arguments, Definitions::NOTIFICATION_COLOR, 0);

    buttonType = GetEnumValueOrDefault<ActionButtonType>(arguments, Definitions::NOTIFICATION_BUTTON_TYPE);

    enabled    = GetValueOrDefault<bool>(arguments, Definitions::NOTIFICATION_ENABLED, false);
    isDangerousOption = GetValueOrDefault<bool>(arguments, Definitions::NOTIFICATION_IS_DANGEROUS_OPTION, false);
    autoDismissible   = GetValueOrDefault<bool>(arguments, Definitions::NOTIFICATION_AUTO_DISMISSIBLE, false);
    showInCompactView = GetValueOrDefault<bool>(arguments, Definitions::NOTIFICATION_SHOW_IN_COMPACT_VIEW, false);
}

flutter::EncodableValue NotificationButtonModel::ToMap() const {
    flutter::EncodableMap returnedObject;

    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_BUTTON_KEY), flutter::EncodableValue(key)));
    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_BUTTON_ICON), flutter::EncodableValue(icon)));
    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_BUTTON_LABEL), flutter::EncodableValue(label)));
    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_COLOR), flutter::EncodableValue(color)));

    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_BUTTON_TYPE),
            flutter::EncodableValue(ActionButtonTypeToString(buttonType.has_value() ? buttonType.value() : ActionButtonType::Default))));

    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_ENABLED), flutter::EncodableValue(enabled)));
    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_AUTO_DISMISSIBLE), flutter::EncodableValue(autoDismissible)));
    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_SHOW_IN_COMPACT_VIEW), flutter::EncodableValue(showInCompactView)));
    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_IS_DANGEROUS_OPTION), flutter::EncodableValue(isDangerousOption)));

    return returnedObject;
}

std::string NotificationButtonModel::ToJson() const {
    return TemplateToJson();
}

void NotificationButtonModel::FromJson(const std::string& json) {
    if(json.empty()) {
        return;
    }

    flutter::EncodableMap map = JsonUtils::FromJson(json);
    FromMap(map);
}

void NotificationButtonModel::Validate() const {
    if (key.empty())
        throw AwesomeNotificationException("Button action key cannot be null or empty");

    if (label.empty())
        throw AwesomeNotificationException("Button label cannot be null or empty");
}
