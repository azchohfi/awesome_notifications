#include <string>

#include "DefaultsModel.h"
#include "../../utils/JsonUtils.h"

DefaultsModel::DefaultsModel(){}

DefaultsModel::DefaultsModel(const std::string& defaultAppIcon){
    this->appIcon = defaultAppIcon;
}

void DefaultsModel::FromMap(const flutter::EncodableMap& arguments) {
    appIcon  = GetValueOrDefault<std::string>(arguments, Definitions::NOTIFICATION_APP_ICON, "");
    firebaseEnabled  = GetValueOrDefault<bool>(arguments, Definitions::FIREBASE_ENABLED, false);
}

flutter::EncodableValue DefaultsModel::ToMap() const {
    flutter::EncodableMap returnedObject;

    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::NOTIFICATION_APP_ICON), flutter::EncodableValue(appIcon)));
    returnedObject.insert(std::make_pair(flutter::EncodableValue(Definitions::FIREBASE_ENABLED), flutter::EncodableValue(firebaseEnabled)));
    return returnedObject;
}

std::string DefaultsModel::ToJson() const {
    return TemplateToJson();
}

void DefaultsModel::FromJson(const std::string& json) {
    if(json.empty()) {
        return;
    }

    flutter::EncodableMap map = JsonUtils::FromJson(json);
    FromMap(map);
}

void DefaultsModel::Validate() const {
}
