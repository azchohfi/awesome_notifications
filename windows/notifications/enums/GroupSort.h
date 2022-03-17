#pragma once

#include <string>

enum class GroupSort {
    Asc,
    Desc
};

std::string GroupSortToString(GroupSort groupSort);