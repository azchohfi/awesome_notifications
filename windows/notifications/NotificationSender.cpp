#include "NotificationSender.h"

#include <iostream>

#include "../utils/IntegerUtils.h"
#include "models/returnedData/NotificationReceived.h"
#include "enums/NotificationLifeCycle.h"
#include "NotificationBuilder.h"

#include <winrt/Microsoft.Windows.AppNotifications.h>

winrt::Windows::Foundation::IAsyncOperation<bool> NotificationSender::Send(const NotificationModel& notificationModel) {

    return NotificationSender::Send(
            notificationModel.content->createdSource.value(),
            notificationModel
    );
}

winrt::Windows::Foundation::IAsyncOperation<bool> NotificationSender::Send(NotificationSource createdSource, const NotificationModel& notificationModel){

    NotificationLifeCycle appLifeCycle;
    // if(AwesomeNotificationsPlugin::appLifeCycle != NotificationLifeCycle::AppKilled){
    //     appLifeCycle = AwesomeNotificationsPlugin::GetApplicationLifeCycle();
    // }
    // else {
        appLifeCycle = NotificationLifeCycle::AppKilled;
    //}

    notificationModel.Validate();

    bool created = false;
    bool displayed = false;

    try {

        std::optional<NotificationReceived> receivedNotification;

        if (!notificationModel.content->createdSource.has_value()) {
            notificationModel.content->createdSource = createdSource;
            created = true;
        }

        if (!notificationModel.content->createdLifeCycle.has_value())
            notificationModel.content->createdLifeCycle = appLifeCycle;

        if (
            !notificationModel.content->title.empty() ||
            !notificationModel.content->body.empty()
        ){

            if (!notificationModel.content->displayedLifeCycle.has_value())
                notificationModel.content->displayedLifeCycle = appLifeCycle;

            notificationModel.content->displayedDate = DateUtils::GetUTCDate();

            // Only save DisplayedMethods if notificationModel was created and displayed successfully
            if(ShowNotification(notificationModel)) {
                displayed = true;

                receivedNotification = NotificationReceived(notificationModel.content);

                receivedNotification->displayedLifeCycle = receivedNotification->displayedLifeCycle.has_value() ?
                        receivedNotification->displayedLifeCycle : appLifeCycle;
            }

        } else {
            receivedNotification = NotificationReceived(notificationModel.content);
        }

        if (created) {
            /*
            CreatedManager::SaveCreated(receivedNotification);
            BroadcastSender.SendBroadcastNotificationCreated(
                context,
                receivedNotification
            );

            CreatedManager.CommitChanges();
            */
        }

        if (displayed) {
            /*
            DisplayedManager::SaveDisplayed(receivedNotification);
            BroadcastSender.SendBroadcastNotificationDisplayed(
                receivedNotification
            );

            DisplayedManager.commitChanges();
            */
        }

    } catch (const std::exception& e) {
        std::wcout << e.what() << std::endl;
    }

    co_return true;
}

bool NotificationSender::ShowNotification(const NotificationModel& notificationModel) {
    try {

        // NotificationLifeCycle lifeCycle = AwesomeNotificationsPlugin.getApplicationLifeCycle();
        NotificationLifeCycle lifeCycle = NotificationLifeCycle::AppKilled;

        if(
            (lifeCycle == NotificationLifeCycle::AppKilled) ||
            (lifeCycle == NotificationLifeCycle::Foreground && notificationModel.content->displayOnForeground) ||
            (lifeCycle == NotificationLifeCycle::Background && notificationModel.content->displayOnBackground)
        ){
            winrt::Microsoft::Windows::AppNotifications::AppNotification notification = NotificationBuilder::CreateNotification(notificationModel);

            /*
            if(
                notificationModel.content->notificationLayout == NotificationLayout::Default &&
                StatusBarManager
                    .getInstance(context)
                    .isFirstActiveOnGroupKey(notificationModel.content->groupKey)
            ){
                NotificationModel pushSummary = _buildSummaryGroupNotification(notificationModel);
                winrt::Microsoft::Windows::AppNotifications::AppNotification summaryNotification = NotificationBuilder::CreateNotification( pushSummary);

                StatusBarManager
                    .getInstance(context)
                    .showNotificationOnStatusBar(pushSummary, summaryNotification);
            }
            */

            /*
            StatusBarManager
                    .getInstance(context)
                    .showNotificationOnStatusBar(notificationModel, notification);
                    */
            winrt::Microsoft::Windows::AppNotifications::AppNotificationManager::Default().Show(notification);

            if (notification.Id() != 0) {
                return true;
            }
        }

        return false;

    } catch (const std::exception& e) {
        std::wcout << e.what() << std::endl;
    }
    return false;
}

/*
void NotificationSender::SendDismissedNotification(ActionReceived actionReceived) {

    if (actionReceived != null){

        actionReceived.dismissedLifeCycle = AwesomeNotificationsPlugin.getApplicationLifeCycle();
        actionReceived.dismissedDate = DateUtils.getUTCDate();

        DismissedManager.saveDismissed(context, actionReceived);
        DismissedManager.commitChanges(context);

        try {

            BroadcastSender.SendBroadcastNotificationDismissed(
                context,
                actionReceived
            );

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
*/

/*
NotificationModel NotificationSender::_buildSummaryGroupNotification(const NotificationModel& original) {

    NotificationModel pushSummary = original.ClonePush();

    pushSummary.content->id = IntegerUtils::GenerateNextRandomId();
    pushSummary.content->notificationLayout = NotificationLayout::Default;
    pushSummary.content->largeIcon = nullptr;
    pushSummary.content->bigPicture = nullptr;
    pushSummary.groupSummary = true;

    return pushSummary;
}
*/