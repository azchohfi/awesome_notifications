#include "GroupAlertBehaviour.h"

std::string GroupAlertBehaviourToString(GroupAlertBehaviour groupAlertBehaviour) {
    switch(groupAlertBehaviour) {
        case GroupAlertBehaviour::All:
            return "All";
        case GroupAlertBehaviour::Summary:
            return "Summary";
        case GroupAlertBehaviour::Children:
            return "Children";
    }

    return "";
}