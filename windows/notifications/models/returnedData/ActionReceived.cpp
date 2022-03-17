#include "ActionReceived.h"

ActionReceived::ActionReceived(NotificationContentModel contentModel) {

    this->id = contentModel.id;
    this->channelKey = contentModel.channelKey;
    this->title = contentModel.title;
    this->body = contentModel.body;
    this->summary = contentModel.summary;
    this->showWhen = contentModel.showWhen;
    this->payload = contentModel.payload;
    this->largeIcon = contentModel.largeIcon;
    this->bigPicture = contentModel.bigPicture;
    this->hideLargeIconOnExpand = contentModel.hideLargeIconOnExpand;
    this->autoDismissible = contentModel.autoDismissible;
    this->color = contentModel.color;
    this->backgroundColor = contentModel.backgroundColor;
    this->progress = contentModel.progress;
    this->ticker = contentModel.ticker;
    this->locked = contentModel.locked;

    this->fullScreenIntent = contentModel.fullScreenIntent;
    this->wakeUpScreen = contentModel.wakeUpScreen;
    this->category = contentModel.category;

    this->notificationLayout = contentModel.notificationLayout;

    this->displayOnBackground = contentModel.displayOnBackground;
    this->displayOnForeground = contentModel.displayOnForeground;

    this->displayedLifeCycle = contentModel.displayedLifeCycle;
    this->displayedDate = contentModel.displayedDate;

    this->createdSource = contentModel.createdSource;
    this->createdLifeCycle = contentModel.createdLifeCycle;
    this->createdDate = contentModel.createdDate;

    this->shouldAutoDismiss = this->autoDismissible;
}

flutter::EncodableValue ActionReceived::ToMap() const {
    flutter::EncodableMap returnedObject = std::get<flutter::EncodableMap>(NotificationReceived::ToMap());

    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_ACTION_LIFECYCLE),
            flutter::EncodableValue(this->actionLifeCycle.has_value() ? NotificationLifeCycleToString(this->actionLifeCycle.value()) : nullptr)));

    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_DISMISSED_LIFECYCLE),
            flutter::EncodableValue(this->dismissedLifeCycle.has_value() ? NotificationLifeCycleToString(this->dismissedLifeCycle.value()) : nullptr)));

    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_BUTTON_KEY_PRESSED), flutter::EncodableValue(this->buttonKeyPressed.has_value() ? this->buttonKeyPressed.value() : nullptr)));
    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_BUTTON_KEY_INPUT), flutter::EncodableValue(this->buttonKeyInput.has_value() ? this->buttonKeyInput.value() : nullptr)));
    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_ACTION_DATE), flutter::EncodableValue(this->actionDate.has_value() ? this->actionDate.value() : nullptr)));
    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_DISMISSED_DATE), flutter::EncodableValue(this->dismissedDate.has_value() ? this->dismissedDate.value() : nullptr)));

    return returnedObject;
}

void ActionReceived::FromMap(const flutter::EncodableMap& arguments) {
    NotificationReceived::FromMap(arguments);

    buttonKeyPressed = MapUtils::ExtractValue<std::string>(arguments, Definitions::NOTIFICATION_BUTTON_KEY_PRESSED);
    buttonKeyInput = MapUtils::ExtractValue<std::string>(arguments, Definitions::NOTIFICATION_BUTTON_KEY_INPUT);
    actionDate    = MapUtils::ExtractValue<std::string>(arguments, Definitions::NOTIFICATION_ACTION_DATE);
    dismissedDate = MapUtils::ExtractValue<std::string>(arguments, Definitions::NOTIFICATION_DISMISSED_DATE);

    actionLifeCycle = GetEnumValueOrDefault<NotificationLifeCycle>(arguments, Definitions::NOTIFICATION_ACTION_LIFECYCLE);
    dismissedLifeCycle = GetEnumValueOrDefault<NotificationLifeCycle>(arguments, Definitions::NOTIFICATION_DISMISSED_LIFECYCLE);
}

std::string ActionReceived::ToJson() const {
    return TemplateToJson();
}

void ActionReceived::FromJson(const std::string& json) {
    NotificationReceived::FromJson(json);
}
