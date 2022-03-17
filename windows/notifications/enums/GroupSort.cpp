#include "GroupSort.h"

std::string GroupSortToString(GroupSort groupSort) {
    switch (groupSort) {
        case GroupSort::Asc:
            return "Asc";
        case GroupSort::Desc:
            return "Desc";
    }

    return "";
}