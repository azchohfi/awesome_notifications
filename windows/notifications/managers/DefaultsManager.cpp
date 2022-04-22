#include <string>

#include "DefaultsManager.h"

bool DefaultsManager::RemoveDefault() {
    //return shared.Remove(Definitions::SHARED_DEFAULTS, "Defaults");
    return false;
}

void DefaultsManager::SaveDefault(const DefaultsModel& defaults) {
    //shared.Set(Definitions::SHARED_DEFAULTS, "Defaults", defaults);
}

DefaultsModel DefaultsManager::GetDefaultByKey() {
    //return shared.Get(Definitions::SHARED_DEFAULTS, "Defaults");
    return DefaultsModel();
}

std::string DefaultsManager::GetDefaultIconByKey() {
    // DefaultsModel defaults = shared.Get(Definitions::SHARED_DEFAULTS, "Defaults");
    // return (defaults != nullptr) ? defaults.appIcon : nullptr;
    return "";
}

bool DefaultsManager::IsFirebaseEnabled() {
    // DefaultsModel defaults = shared.Get(Definitions::SHARED_DEFAULTS, "Defaults");
    // return (defaults != nullptr) ? defaults.firebaseEnabled : true;
    return false;
}

void DefaultsManager::CommitChanges() {
    //shared.Commit();
}
