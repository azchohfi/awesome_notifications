#include <string>

#include "DefaultsManager.h"

SharedManager<DefaultsModel> DefaultsManager::shared = SharedManager<DefaultsModel>(
                     "DefaultsManager",
                     "DefaultsModel");

bool DefaultsManager::RemoveDefault() {
    return shared.Remove(Definitions::SHARED_DEFAULTS, "Defaults");
}

void DefaultsManager::SaveDefault(const DefaultsModel& defaults) {
    shared.Set(Definitions::SHARED_DEFAULTS, "Defaults", defaults);
}

std::optional<DefaultsModel> DefaultsManager::GetDefaultByKey() {
    return shared.Get(Definitions::SHARED_DEFAULTS, "Defaults");
}

std::string DefaultsManager::GetDefaultIconByKey() {
    auto defaults = shared.Get(Definitions::SHARED_DEFAULTS, "Defaults");
    return defaults.has_value() ? defaults->appIcon : "";
}

bool DefaultsManager::IsFirebaseEnabled() {
    auto defaults = shared.Get(Definitions::SHARED_DEFAULTS, "Defaults");
    return defaults.has_value() ? defaults->firebaseEnabled : true;
}

void DefaultsManager::CommitChanges() {
    shared.Commit();
}
