#pragma once

#include <string>

#include "../../definitions.h"
#include "AbstractModel.h"

class DefaultsModel : public AbstractModel {
 public:
    std::string appIcon;
    bool firebaseEnabled;

    DefaultsModel();

    DefaultsModel(const std::string& defaultAppIcon);

    void FromMap(const flutter::EncodableMap& arguments) override;

    flutter::EncodableValue ToMap() const override;

    std::string ToJson() const override;

    void FromJson(const std::string& json) override;

    void Validate() const override;
};
