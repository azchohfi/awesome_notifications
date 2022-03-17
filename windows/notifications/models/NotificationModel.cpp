#pragma once

#include <flutter/encodable_value.h>

#include <string>
#include <map>
#include <memory>
#include <vector>

#include "NotificationModel.h"
#include "../../definitions.h"
#include "../exceptions/AwesomeNotificationException.h"
#include "../../utils/JsonUtils.h"

NotificationModel::NotificationModel() {

}

NotificationModel::NotificationModel(const AbstractModel& abstractModel)
: AbstractModel(abstractModel) {
}

NotificationModel NotificationModel::ClonePush() const {
    NotificationModel clone;
    clone.FromMap(std::get<flutter::EncodableMap>(this->ToMap()));
    return clone;
}

void NotificationModel::FromMap(const flutter::EncodableMap& parameters) {
    content = ExtractNotificationContent(Definitions::NOTIFICATION_MODEL_CONTENT, &parameters);

    // required
    if(content == nullptr) {
        return;
    }

    schedule = ExtractNotificationSchedule(Definitions::NOTIFICATION_MODEL_SCHEDULE, &parameters);
    auto actionButtonsOptional = ExtractNotificationButtons(Definitions::NOTIFICATION_MODEL_BUTTONS, &parameters);
    if (actionButtonsOptional)
        actionButtons = actionButtonsOptional.value();
}

flutter::EncodableValue NotificationModel::ToMap() const {

    if(!content) {
        return nullptr;
    }
    flutter::EncodableMap dataMap;

    dataMap.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_MODEL_CONTENT), content->ToMap()));

    if(schedule) {
        dataMap.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_MODEL_SCHEDULE), schedule->ToMap()));
    }

    if(!actionButtons.empty()) {
        flutter::EncodableList buttonsData;
        for (auto& button : actionButtons) {
            buttonsData.push_back(button.ToMap());
        }
        dataMap.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_MODEL_BUTTONS), flutter::EncodableValue(buttonsData)));
    }

    return dataMap;
}

std::string NotificationModel::ToJson() const {
    return TemplateToJson();
}

void NotificationModel::FromJson(const std::string& json) {
    if(json.empty()) {
        return;
    }

    flutter::EncodableMap map = JsonUtils::FromJson(json);
    FromMap(map);
}

void NotificationModel::Validate() const {
    if (!this->content) {
        throw AwesomeNotificationException("Push Notification content cannot be null or empty");
    }

    this->content->Validate();

    if(this->schedule) {
        this->schedule->Validate();
    }

    if (!this->actionButtons.empty()) {
        for(NotificationButtonModel button : this->actionButtons){
            button.Validate();
        }
    }
}

std::shared_ptr<NotificationContentModel> NotificationModel::ExtractNotificationContent(std::string reference, const flutter::EncodableMap* parameters) {
    auto result_it = parameters->find(flutter::EncodableValue(reference));
    if (parameters == nullptr || result_it == parameters->end()) {
        return nullptr;
    }

    if(const auto* map = std::get_if<flutter::EncodableMap>(&result_it->second)) {
        if (map->empty()) {
            return nullptr;
        }
        auto notificationContentModel = std::make_shared<NotificationContentModel>();
        notificationContentModel->FromMap(*map);
        return notificationContentModel;
    }
    return nullptr;
}

std::shared_ptr<NotificationScheduleModel> NotificationModel::ExtractNotificationSchedule(std::string reference, const flutter::EncodableMap* parameters) {
    auto result_it = parameters->find(flutter::EncodableValue(reference));
    if (parameters == nullptr || result_it == parameters->end()) {
        return nullptr;
    }

    if(const auto* map = std::get_if<flutter::EncodableMap>(&result_it->second)) {
        return NotificationScheduleModel::GetScheduleModelFromMap(*map);
    }
    return nullptr;
}

std::optional<std::vector<NotificationButtonModel>> NotificationModel::ExtractNotificationButtons(std::string reference, const flutter::EncodableMap* parameters) {
    auto result_it = parameters->find(flutter::EncodableValue(reference));
    if (parameters == nullptr || result_it == parameters->end()) {
        return {};
    }

    if(const auto* actionButtonsData = std::get_if<flutter::EncodableList>(&result_it->second)) {
        std::vector<NotificationButtonModel> actionButtons;

        for (auto& objButton : *actionButtonsData) {
            if(const auto* map = std::get_if<flutter::EncodableMap>(&objButton)) {
                if(map->empty()) {
                    continue;
                }

                auto button = NotificationButtonModel();
                button.FromMap(*map);
                actionButtons.push_back(button);
            } else {
                return {};
            }
        }

        if(actionButtons.empty()) {
            return {};
        }

        return actionButtons;
    }
    return {};
}