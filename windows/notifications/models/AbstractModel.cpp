#include <flutter/encodable_value.h>

#include <string>
#include <optional>
#include <map>

#include "AbstractModel.h"

AbstractModel::AbstractModel() {
}

AbstractModel::~AbstractModel() {
}

std::string AbstractModel::TemplateToJson() const {
    return JsonUtils::ToJson(std::get<flutter::EncodableMap>(this->ToMap()));
}