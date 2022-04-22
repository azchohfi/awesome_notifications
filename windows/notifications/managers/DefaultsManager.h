#pragma once

#include <string>

#include "../../definitions.h"
#include "../models/DefaultsModel.h"

class DefaultsManager {
 private:
    // static inline SharedManager<DefaultsModel> shared(
    //                 "DefaultsManager",
    //                 "DefaultsModel");
 public:

    static bool RemoveDefault();

    static void SaveDefault(const DefaultsModel& defaults);

    static DefaultsModel GetDefaultByKey();

    static std::string GetDefaultIconByKey();

    static bool IsFirebaseEnabled();

    static void CommitChanges();
};
