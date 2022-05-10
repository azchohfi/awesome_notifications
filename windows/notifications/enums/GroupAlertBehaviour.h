#pragma once

#include <string>

enum class GroupAlertBehaviour {
    All,
    Summary,
    Children
};

std::string GroupAlertBehaviourToString(GroupAlertBehaviour groupAlertBehaviour);

constexpr std::initializer_list<GroupAlertBehaviour> All_GroupAlertBehaviour = { GroupAlertBehaviour::All, GroupAlertBehaviour::Summary, GroupAlertBehaviour::Children };