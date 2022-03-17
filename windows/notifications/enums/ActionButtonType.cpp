#include "ActionButtonType.h"

std::string ActionButtonTypeToString(ActionButtonType actionButtonType) {
    switch(actionButtonType) {
        case ActionButtonType::Default:
            return "Default";
        case ActionButtonType::InputField:
            return "InputField";
        case ActionButtonType::DisabledAction:
            return "DisabledAction";
        case ActionButtonType::KeepOnTop:
            return "KeepOnTop";
    }

    return "Default";
}