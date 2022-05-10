#pragma once

#include <string>

enum class ActionButtonType {
    Default,
    InputField,
    DisabledAction,
    KeepOnTop
};

std::string ActionButtonTypeToString(ActionButtonType actionButtonType);

constexpr std::initializer_list<ActionButtonType> All_ActionButtonType = { ActionButtonType::Default, ActionButtonType::InputField, ActionButtonType::DisabledAction, ActionButtonType::KeepOnTop };