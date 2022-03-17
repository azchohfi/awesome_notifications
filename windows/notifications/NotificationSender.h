#pragma once

#include <string>

#include <winrt/Windows.Foundation.h>

#include "models/NotificationModel.h"
#include "enums/NotificationLifeCycle.h"

class NotificationSender {
 public:
    static inline std::string TAG = "NotificationSender";

    static winrt::Windows::Foundation::IAsyncOperation<bool> Send(const NotificationModel& notificationModel);

    static winrt::Windows::Foundation::IAsyncOperation<bool> Send(NotificationSource createdSource, const NotificationModel& notificationModel);

    //static void SendDismissedNotification(ActionReceived actionReceived);

 private:
    NotificationSender() {};

    static bool ShowNotification(const NotificationModel& notificationModel);

    // static NotificationModel _buildSummaryGroupNotification(const NotificationModel& original);
};
