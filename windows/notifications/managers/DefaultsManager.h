#pragma once

#include <string>

#include "../../definitions.h"
#include "../models/DefaultsModel.h"
#include "SharedManager.h"

class DefaultsManager {
 private:
    static SharedManager<DefaultsModel> shared;
 public:

    static bool RemoveDefault();

    static void SaveDefault(const DefaultsModel& defaults);

    static std::optional<DefaultsModel> GetDefaultByKey();

    static std::string GetDefaultIconByKey();

    static bool IsFirebaseEnabled();

    static void CommitChanges();
};
