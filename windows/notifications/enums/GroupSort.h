#pragma once

#include <string>

enum class GroupSort {
    Asc,
    Desc
};

std::string GroupSortToString(GroupSort groupSort);

constexpr std::initializer_list<GroupSort> All_GroupSort = { GroupSort::Asc, GroupSort::Desc };