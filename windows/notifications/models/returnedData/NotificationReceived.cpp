#include "NotificationReceived.h"

NotificationReceived::NotificationReceived(std::shared_ptr<NotificationContentModel> contentModel) {
    /*
    if (contentModel == nullptr)
        throw NotificationModelException("Notification Received was lost");
    */
    this->id = contentModel->id;
    this->channelKey = contentModel->channelKey;
    this->groupKey = contentModel->groupKey;
    this->title = contentModel->title;
    this->body = contentModel->body;
    this->summary = contentModel->summary;
    this->showWhen = contentModel->showWhen;
    this->payload = contentModel->payload;
    this->largeIcon = contentModel->largeIcon;
    this->bigPicture = contentModel->bigPicture;
    this->hideLargeIconOnExpand = contentModel->hideLargeIconOnExpand;
    this->autoDismissible = contentModel->autoDismissible;
    this->color = contentModel->color;
    this->backgroundColor = contentModel->backgroundColor;
    this->progress = contentModel->progress;
    this->ticker = contentModel->ticker;
    this->locked = contentModel->locked;

    this->fullScreenIntent = contentModel->fullScreenIntent;
    this->wakeUpScreen = contentModel->wakeUpScreen;
    this->category = contentModel->category;

    this->notificationLayout = contentModel->notificationLayout;

    this->displayedLifeCycle = contentModel->displayedLifeCycle;
    this->displayedDate = contentModel->displayedDate;

    this->createdSource = contentModel->createdSource;
    this->createdLifeCycle = contentModel->createdLifeCycle;
    this->createdDate = contentModel->createdDate;
}

void NotificationReceived::FromMap(const flutter::EncodableMap& arguments) {
    NotificationContentModel::FromMap(arguments);
}

flutter::EncodableValue NotificationReceived::ToMap() const {
    return NotificationContentModel::ToMap();
}

std::string NotificationReceived::ToJson() const{
    return TemplateToJson();
}

void NotificationReceived::FromJson(const std::string& json) {
    if(json.empty()) {
        return;
    }

    flutter::EncodableMap map = JsonUtils::FromJson(json);
    FromMap(map);
}
