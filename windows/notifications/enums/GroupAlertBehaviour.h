#pragma once

#include <string>

enum class GroupAlertBehaviour {
    All,
    Summary,
    Children
};

std::string GroupAlertBehaviourToString(GroupAlertBehaviour groupAlertBehaviour);