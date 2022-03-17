#pragma once

#include <string>

enum class ActionButtonType {
    Default,
    InputField,
    DisabledAction,
    KeepOnTop
};

std::string ActionButtonTypeToString(ActionButtonType actionButtonType);