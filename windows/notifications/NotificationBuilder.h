#pragma once

#include <string>

#include <winrt/Microsoft.Windows.AppNotifications.h>

#include "models/NotificationModel.h"
#include "models/NotificationChannelModel.h"

class NotificationBuilder {
 public:
    static inline std::string TAG = "NotificationBuilder";

    /*
    static ActionReceived receiveNotificationAction(Intent intent, NotificationLifeCycle appLifeCycle) {

        ActionReceived actionReceived
            = NotificationBuilder
                .buildNotificationActionFromIntent(intent, appLifeCycle);

        if (actionReceived != null) {
            if (NotificationBuilder.notificationActionShouldAutoDismiss(actionReceived))
                StatusBarManager
                        .dismissNotification(actionReceived.id);

            if (actionReceived.actionButtonType == ActionButtonType.DisabledAction)
                return null;
        }

        return actionReceived;
    }

    public static boolean notificationActionShouldAutoDismiss(ActionReceived actionReceived){
        return actionReceived.shouldAutoDismiss && actionReceived.autoDismissible;
    }
    */

    static winrt::Microsoft::Windows::AppNotifications::AppNotification CreateNotification(const NotificationModel& notificationModel);

    /*
    public static Intent buildNotificationIntentFromModel(
            String ActionReference,
            NotificationModel notificationModel,
            NotificationChannelModel channel,
            Class<?> targetAction
    ) {
        Intent intent = new Intent(targetAction);

        intent.setAction(ActionReference);

        Bundle extras = intent.getExtras();
        if(extras == null)
            extras = new Bundle();

        String jsonData = notificationModel.toJson();
        extras.putString(Definitions.NOTIFICATION_JSON, jsonData);

        updateTrackingExtras(notificationModel, channel, extras);
        intent.putExtras(extras);

        return intent;
    }

    public static Intent buildNotificationIntentFromModel(
            String actionReference,
            NotificationModel notificationModel,
            NotificationChannelModel channel
    ) {
        Class<?> targetClass = getTargetClass();
        return buildNotificationIntentFromModel(
                actionReference,
                notificationModel,
                channel,
                targetClass);
    }

    public static ActionReceived buildNotificationActionFromIntent(Intent intent, NotificationLifeCycle lifeCycle) {
        String buttonKeyPressed = intent.getAction();

        if (buttonKeyPressed == null) return null;

        boolean isNormalAction = Definitions.SELECT_NOTIFICATION.equals(buttonKeyPressed) || Definitions.DISMISSED_NOTIFICATION.equals(buttonKeyPressed);
        boolean isButtonAction = buttonKeyPressed.startsWith(Definitions.NOTIFICATION_BUTTON_ACTION_PREFIX);

        if (isNormalAction || isButtonAction) {

            String notificationJson = intent.getStringExtra(Definitions.NOTIFICATION_JSON);

            NotificationModel notificationModel = new NotificationModel().fromJson(notificationJson);
            if (notificationModel == null) return null;

            ActionReceived actionModel = new ActionReceived(notificationModel.content);

            actionModel.actionDate = DateUtils.getUTCDate();
            actionModel.actionLifeCycle = lifeCycle;

            if (StringUtils.isNullOrEmpty(actionModel.displayedDate))
                actionModel.displayedDate = DateUtils.getUTCDate();

            actionModel.autoDismissible = intent.getBooleanExtra(Definitions.NOTIFICATION_AUTO_DISMISSIBLE, true);
            actionModel.shouldAutoDismiss = actionModel.autoDismissible;

            if (isButtonAction) {

                actionModel.buttonKeyPressed = intent.getStringExtra(Definitions.NOTIFICATION_BUTTON_KEY);
                String NotificationButtonType = intent.getStringExtra(Definitions.NOTIFICATION_BUTTON_TYPE);

                if (NotificationButtonType.equals(ActionButtonType.InputField.toString()))
                    actionModel.buttonKeyInput = getButtonInputText(intent, intent.getStringExtra(Definitions.NOTIFICATION_BUTTON_KEY));

                if(
                    !StringUtils.isNullOrEmpty(actionModel.buttonKeyInput) &&
                    Build.VERSION.SDK_INT >= Build.VERSION_CODES.N // Android 7
                ) {
                    actionModel.shouldAutoDismiss = false;

                    switch (notificationModel.content.notificationLayout){

                        case Inbox:
                        case BigText:
                        case BigPicture:
                        case ProgressBar:
                        case MediaPlayer:
                        case Default:
                            try {
                                notificationModel.remoteHistory = actionModel.buttonKeyInput;
                                NotificationSender.send(notificationModel);
                            } catch (Exception e) {
                                e.printStackTrace();
                            }
                            break;
                    }
                }
            }

            if (isButtonAction)
                actionModel.actionButtonType = StringUtils.getEnumFromString(ActionButtonType.class, intent.getStringExtra(Definitions.NOTIFICATION_BUTTON_TYPE));

            return actionModel;
        }
        return null;
    }

    public static String getAppName(){
        ApplicationInfo applicationInfo = context.getApplicationInfo();
        int stringId = applicationInfo.labelRes;
        return stringId == 0 ? applicationInfo.nonLocalizedLabel.toString() : context.getString(stringId);
    }

    @RequiresApi(api = Build.VERSION_CODES.KITKAT_WATCH)
    public static void wakeUpScreen(){

        PowerManager pm = (PowerManager)context.getSystemService(Context.POWER_SERVICE);
        boolean isScreenOn = pm.isInteractive();
        if(!isScreenOn)
        {
            String appName = NotificationBuilder.getAppName();

            PowerManager.WakeLock wl = pm.newWakeLock(
                    PowerManager.FULL_WAKE_LOCK |
                    PowerManager.ACQUIRE_CAUSES_WAKEUP |
                    PowerManager.ON_AFTER_RELEASE,
                    appName+":"+TAG+":WakeupLock");
            wl.acquire(10000);

            PowerManager.WakeLock wl_cpu = pm.newWakeLock(
                    PowerManager.PARTIAL_WAKE_LOCK,
                    appName+":"+TAG+":WakeupCpuLock");
            wl_cpu.acquire(10000);
            wl_cpu.acquire(10000);
        }
    }

    public static void ensureCriticalAlert() throws AwesomeNotificationException {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            NotificationManager notificationManager = (NotificationManager) context.getSystemService(NOTIFICATION_SERVICE);
            if (isDndOverrideAllowed(notificationManager)) {
                if (!PermissionManager.isSpecifiedPermissionGloballyAllowed(NotificationPermission.CriticalAlert)){
                    notificationManager.setInterruptionFilter(NotificationManager.INTERRUPTION_FILTER_PRIORITY);
                    NotificationManager.Policy policy = new NotificationManager.Policy(PRIORITY_CATEGORY_ALARMS, 0, 0);
                    notificationManager.setNotificationPolicy(policy);
                }
            }
        }
    }

    public static NotificationManager getAndroidNotificationManager(){
        return  (NotificationManager) context.getSystemService(Context.NOTIFICATION_SERVICE);
    }

    public static boolean isDndOverrideAllowed(){
        NotificationManager notificationManager = (NotificationManager) context.getSystemService(NOTIFICATION_SERVICE);
        return isDndOverrideAllowed(notificationManager);
    }

    public static boolean isCriticalAlertsGloballyAllowed(){
        NotificationManager notificationManager = getAndroidNotificationManager();

        return notificationManager.getCurrentInterruptionFilter() != NotificationManager.INTERRUPTION_FILTER_NONE;

        // Critical alerts until Android 6 are "Treat as priority" or "Priority"
//            return (notificationManager.getNotificationPolicy().state
//                    & NotificationManager.Policy.STATE_CHANNELS_BYPASSING_DND) == 1;
            // TODO read "Treat as priority" or "Priority" property on notifications page
        return true;
    }

    @RequiresApi(api = Build.VERSION_CODES.N)
    public static boolean isNotificationSoundGloballyAllowed(){
        NotificationManager manager = (NotificationManager) context.getSystemService(Context.NOTIFICATION_SERVICE);
        int importance = manager.getImportance();
        return importance < 0 || importance >= NotificationManager.IMPORTANCE_DEFAULT;
    }

    public static boolean isDndOverrideAllowed(NotificationManager notificationManager){
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            return notificationManager.isNotificationPolicyAccessGranted();
        }
        return true;
    }

    // https://github.com/rafaelsetragni/awesome_notifications/issues/191
    public static Class getNotificationTargetActivityClass() {

        String packageName = context.getPackageName();
        Intent launchIntent = context.getPackageManager().getLaunchIntentForPackage(packageName);
        String className =
                launchIntent == null ?
                        AwesomeNotificationsPlugin.getMainTargetClassName() :
                        launchIntent.getComponent().getClassName();
        try {
            return Class.forName(className);
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
            return null;
        }
    }
    */

    static void CreateActionButtons(const NotificationModel& notificationModel, const NotificationChannelModel& channel, std::wstring& actions);

    /*
    public static final ConcurrentHashMap<String, List<NotificationMessageModel>> messagingQueue = new ConcurrentHashMap<String, List<NotificationMessageModel>>();
    */
 private:

/*
    static PendingIntent getPendingActionIntent(NotificationModel notificationModel, NotificationChannelModel channelModel) {
        Intent intent = buildNotificationIntentFromModel(
                Definitions.SELECT_NOTIFICATION,
                notificationModel,
                channelModel
        );

        PendingIntent pendingActionIntent = PendingIntent.getActivity(
                notificationModel.content.id,
                intent,
                PendingIntent.FLAG_IMMUTABLE | PendingIntent.FLAG_UPDATE_CURRENT
        );
        return pendingActionIntent;
    }

    static PendingIntent getPendingDismissIntent(NotificationModel notificationModel, NotificationChannelModel channelModel) {
        Intent deleteIntent = buildNotificationIntentFromModel(
                Definitions.DISMISSED_NOTIFICATION,
                notificationModel,
                channelModel,
                DismissedNotificationReceiver.class
        );

        PendingIntent pendingDismissIntent = PendingIntent.getBroadcast(
                notificationModel.content.id,
                deleteIntent,
                PendingIntent.FLAG_IMMUTABLE | PendingIntent.FLAG_UPDATE_CURRENT
        );
        return pendingDismissIntent;
    }

    @SuppressWarnings("unchecked")
    static void updateTrackingExtras(NotificationModel notificationModel, NotificationChannelModel channel, Bundle extras) {
        String groupKey = getGroupKey(notificationModel.content, channel);

        extras.putInt(Definitions.NOTIFICATION_ID, notificationModel.content.id);
        extras.putString(Definitions.NOTIFICATION_CHANNEL_KEY, StringUtils.digestString(notificationModel.content.channelKey));
        extras.putString(Definitions.NOTIFICATION_GROUP_KEY, StringUtils.digestString(groupKey));
        extras.putBoolean(Definitions.NOTIFICATION_AUTO_DISMISSIBLE, notificationModel.content.autoDismissible);

        if(!ListUtils.isNullOrEmpty(notificationModel.content.messages)) {
            Map<String, Object> contentData = notificationModel.content.toMap();
            List<Map> contentMessageData = null;
            if(contentData.get(Definitions.NOTIFICATION_MESSAGES) instanceof List) {
                contentMessageData = (List<Map>) contentData.get(Definitions.NOTIFICATION_MESSAGES);
            }
            if(contentMessageData != null)
                extras.putSerializable(
                        Definitions.NOTIFICATION_MESSAGES,
                        (Serializable) contentMessageData);
        }
    }

    static Class<?> getTargetClass(){
        return getNotificationTargetActivityClass();
    }

    static String getButtonInputText(Intent intent, String buttonKey) {
        Bundle remoteInput = RemoteInput.getResultsFromIntent(intent);
        if (remoteInput != null) {
            return remoteInput.getCharSequence(buttonKey).toString();
        }
        return null;
    }
*/
    static winrt::Microsoft::Windows::AppNotifications::AppNotification GetNotificationBuilderFromModel(const NotificationModel& notificationModel);

    /*

    static void setCategoryFlags(NotificationModel notificationModel, Notification androidNotification) {

        if(notificationModel.content.category != null)
            switch (notificationModel.content.category){

                case Alarm:
                    androidNotification.flags |= Notification.FLAG_INSISTENT;
                    androidNotification.flags |= Notification.FLAG_NO_CLEAR;
                    break;

                case Call:
                    androidNotification.flags |= Notification.FLAG_INSISTENT;
                    androidNotification.flags |= Notification.FLAG_HIGH_PRIORITY;
                    androidNotification.flags |= Notification.FLAG_NO_CLEAR;
                    break;
            }
    }

    static void setNotificationPendingIntents(NotificationModel notificationModel, PendingIntent pendingActionIntent, PendingIntent pendingDismissIntent, std::wstring& builder) {
        builder.setContentIntent(pendingActionIntent);
        if(!notificationModel.groupSummary)
            builder.setDeleteIntent(pendingDismissIntent);
    }

    static void setWakeUpScreen(NotificationModel notificationModel) {
        if (notificationModel.content.wakeUpScreen)
//            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.KITKAT_WATCH)
                wakeUpScreen();
    }

    static void setCriticalAlert(NotificationChannelModel channel) throws AwesomeNotificationException {
        if (channel.criticalAlerts)
            ensureCriticalAlert();
    }

    static void setFullScreenIntent(PendingIntent pendingIntent, NotificationModel notificationModel, std::wstring& builder) {
        if (BooleanUtils.getValue(notificationModel.content.fullScreenIntent)) {
            builder.setFullScreenIntent(pendingIntent, true);
        }
    }

    static void setShowWhen(NotificationModel notificationModel, std::wstring& builder) {
        builder.setShowWhen(BooleanUtils.getValueOrDefault(notificationModel.content.showWhen, true));
    }

    static Integer getBackgroundColor(NotificationModel notificationModel, NotificationChannelModel channel, std::wstring& builder) {
        Integer bgColorValue;
        bgColorValue = IntegerUtils.extractInteger(notificationModel.content.backgroundColor, null);
        if (bgColorValue != null) {
            builder.setColorized(true);
        } else {
            bgColorValue = getLayoutColor(notificationModel, channel);
        }
        return bgColorValue;
    }

    static Integer getLayoutColor(NotificationModel notificationModel, NotificationChannelModel channel) {
        Integer layoutColorValue;
        layoutColorValue = IntegerUtils.extractInteger(notificationModel.content.color, channel.defaultColor);
        layoutColorValue = IntegerUtils.extractInteger(layoutColorValue, Color.BLACK);
        return layoutColorValue;
    }
*/
    static void SetImportance(const NotificationChannelModel& channel, std::wstring& builder);
/*
    static void setCategory(NotificationModel notificationModel, std::wstring& builder){
        if(notificationModel.content.category != null)
            builder.setCategory(notificationModel.content.category.rawValue);
    }

    static void setOnlyAlertOnce(NotificationModel notificationModel, NotificationChannelModel channel, std::wstring& builder) {
        boolean onlyAlertOnceValue = BooleanUtils.getValue(notificationModel.content.notificationLayout == NotificationLayout.ProgressBar || channel.onlyAlertOnce);
        builder.setOnlyAlertOnce(onlyAlertOnceValue);
    }

    static void setRemoteHistory(NotificationModel notificationModel, std::wstring& builder) {
        if(!StringUtils.isNullOrEmpty(notificationModel.remoteHistory) && notificationModel.content.notificationLayout == NotificationLayout.Default)
            builder.setRemoteInputHistory(new CharSequence[]{notificationModel.remoteHistory});
    }

    static void setLockedNotification(NotificationModel notificationModel, NotificationChannelModel channel, std::wstring& builder) {
        boolean contentLocked = BooleanUtils.getValue(notificationModel.content.locked);
        boolean channelLocked = BooleanUtils.getValue(channel.locked);

        if (contentLocked) {
            builder.setOngoing(true);
        } else if (channelLocked) {
            boolean lockedValue = BooleanUtils.getValueOrDefault(notificationModel.content.locked, true);
            builder.setOngoing(lockedValue);
        }
    }

    static void setTicker(NotificationModel notificationModel, std::wstring& builder) {
        String tickerValue;
        tickerValue = StringUtils.getValueOrDefault(notificationModel.content.ticker, null);
        tickerValue = StringUtils.getValueOrDefault(tickerValue, notificationModel.content.summary);
        tickerValue = StringUtils.getValueOrDefault(tickerValue, notificationModel.content.body);
        builder.setTicker(tickerValue);
    }

    static void setBadge(NotificationModel notificationModel, NotificationChannelModel channelModel, std::wstring& builder) {
        if (!notificationModel.groupSummary && BooleanUtils.getValue(channelModel.channelShowBadge)) {
            BadgeManager.incrementGlobalBadgeCounter();
            builder.setNumber(1);
        }
    }

    static void setAutoCancel(NotificationModel notificationModel, std::wstring& builder) {
        builder.setAutoCancel(BooleanUtils.getValueOrDefault(notificationModel.content.autoDismissible, true));
    }
*/
    static void SetBody(const NotificationModel& notificationModel, std::wstring& builder);

    static void SetTitle(const NotificationModel& notificationModel, const NotificationChannelModel& channelModel, std::wstring& builder);
/*
    static void setVibrationPattern(NotificationChannelModel channelModel, std::wstring& builder) {
        if (BooleanUtils.getValue(channelModel.enableVibration)) {
            if (channelModel.vibrationPattern != null && channelModel.vibrationPattern.length > 0) {
                builder.setVibrate(channelModel.vibrationPattern);
            }
        } else {
            builder.setVibrate(new long[]{0});
        }
    }

    static void setLights(NotificationChannelModel channelModel, std::wstring& builder) {
        if (BooleanUtils.getValue(channelModel.enableLights)) {
            Integer ledColorValue = IntegerUtils.extractInteger(channelModel.ledColor, Color.WHITE);
            Integer ledOnMsValue = IntegerUtils.extractInteger(channelModel.ledOnMs, 300);
            Integer ledOffMsValue = IntegerUtils.extractInteger(channelModel.ledOffMs, 700);
            builder.setLights(ledColorValue, ledOnMsValue, ledOffMsValue);
        }
    }

    static void setVisibility(NotificationModel notificationModel, NotificationChannelModel channelModel, std::wstring& builder) {

//        if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.LOLLIPOP) {
//
            Integer visibilityIndex;
            visibilityIndex = IntegerUtils.extractInteger(notificationModel.content.privacy, channelModel.defaultPrivacy.ordinal());
            visibilityIndex = IntegerUtils.extractInteger(visibilityIndex, NotificationPrivacy.Public);

            builder.setVisibility(visibilityIndex - 1);
//        }
    }

    static void setLayoutColor(NotificationModel notificationModel, NotificationChannelModel channelModel, std::wstring& builder) {

        if (notificationModel.content.backgroundColor == null) {
            builder.setColor(getLayoutColor(notificationModel, channelModel));
        } else {
            builder.setColor(getBackgroundColor(notificationModel, channelModel, builder));
        }
    }

    static void setLargeIcon(NotificationModel notificationModel, std::wstring& builder) {
        if (notificationModel.content.notificationLayout != NotificationLayout.BigPicture)
            if (!StringUtils.isNullOrEmpty(notificationModel.content.largeIcon)) {
                Bitmap largeIcon = BitmapUtils.getBitmapFromSource(
                        notificationModel.content.largeIcon,
                        notificationModel.content.roundedLargeIcon);
                if (largeIcon != null)
                    builder.setLargeIcon(largeIcon);
            }
    }

    static void setSound(NotificationModel notificationModel, NotificationChannelModel channelModel, std::wstring& builder) {

        Uri uri = null;

        if (!notificationModel.content.isRefreshNotification && BooleanUtils.getValue(channelModel.playSound)) {
            String soundSource = StringUtils.isNullOrEmpty(notificationModel.content.customSound) ? channelModel.soundSource : notificationModel.content.customSound;
            uri = ChannelManager.retrieveSoundResourceUri(channelModel.defaultRingtoneType, soundSource);
        }

        builder.setSound(uri);
    }

    static void setSmallIcon(NotificationModel notificationModel, NotificationChannelModel channelModel, std::wstring& builder) {
        if (!StringUtils.isNullOrEmpty(notificationModel.content.icon)) {
            builder.setSmallIcon(BitmapUtils.getDrawableResourceId(notificationModel.content.icon));
        } else if (!StringUtils.isNullOrEmpty(channelModel.icon)) {
            builder.setSmallIcon(BitmapUtils.getDrawableResourceId(channelModel.icon));
        } else {
            String defaultIcon = DefaultsManager.getDefaultIconByKey();

            if (StringUtils.isNullOrEmpty(defaultIcon)) {

                // for backwards compatibility: this is for handling the old way references to the icon used to be kept but should be removed in future
                if (channelModel.iconResourceId != null) {
                    builder.setSmallIcon(channelModel.iconResourceId);
                } else {
                    int defaultResource = context.getResources().getIdentifier(
                            "ic_launcher",
                            "mipmap",
                            context.getPackageName()
                    );

                    if (defaultResource > 0) {
                        builder.setSmallIcon(defaultResource);
                    }
                }
            } else {
                int resourceIndex = BitmapUtils.getDrawableResourceId(defaultIcon);
                if (resourceIndex > 0) {
                    builder.setSmallIcon(resourceIndex);
                }
            }
        }
    }

    static void setGrouping(NotificationModel notificationModel, NotificationChannelModel channelModel, std::wstring& builder) {

        if( // Grouping key is reserved to arrange messaging and messaging group layouts
            notificationModel.content.notificationLayout == NotificationLayout.Messaging ||
            notificationModel.content.notificationLayout == NotificationLayout.MessagingGroup
        ) return;

        String groupKey = getGroupKey(notificationModel.content, channelModel);

        if (!StringUtils.isNullOrEmpty(groupKey)) {
            builder.setGroup(groupKey);

            if(notificationModel.groupSummary)
                builder.setGroupSummary(true);

            String idText = notificationModel.content.id.toString();
            String sortKey = Long.toString(
                    (channelModel.groupSort == GroupSort.Asc ? System.currentTimeMillis() : Long.MAX_VALUE - System.currentTimeMillis())
            );

            builder.setSortKey(sortKey + idText);

            builder.setGroupAlertBehavior(channelModel.groupAlertBehavior.ordinal());
        }
    }

    static void setLayout(NotificationModel notificationModel, NotificationChannelModel channelModel, std::wstring& builder) throws AwesomeNotificationException {

        switch (notificationModel.content.notificationLayout) {

            case BigPicture:
                if (setBigPictureLayout(notificationModel.content, builder)) return;
                break;

            case BigText:
                if (setBigTextStyle(notificationModel.content, builder)) return;
                break;

            case Inbox:
                if (setInboxLayout(notificationModel.content, builder)) return;
                break;

            case Messaging:
                if (setMessagingLayout(false, notificationModel.content, channelModel, builder)) return;
                break;

            case MessagingGroup:
                if(setMessagingLayout(true, notificationModel.content, channelModel, builder)) return;
                break;

            case PhoneCall:
                setPhoneCallLayout(notificationModel, builder);
                break;

            case MediaPlayer:
                if (setMediaPlayerLayout(notificationModel.content, notificationModel.actionButtons, builder)) return;
                break;

            case ProgressBar:
                setProgressLayout(notificationModel, builder);
                break;

            case Default:
            default:
                break;
        }
    }

    static Boolean setBigPictureLayout(NotificationContentModel contentModel, std::wstring& builder) {

        Bitmap bigPicture = null, largeIcon = null;

        if (!StringUtils.isNullOrEmpty(contentModel.bigPicture))
            bigPicture = BitmapUtils.getBitmapFromSource(
                    contentModel.bigPicture,
                    contentModel.roundedBigPicture);

        if (contentModel.hideLargeIconOnExpand)
            largeIcon = bigPicture != null ?
                bigPicture : (!StringUtils.isNullOrEmpty(contentModel.largeIcon) ?
                    BitmapUtils.getBitmapFromSource(
                            contentModel.largeIcon,
                            contentModel.roundedLargeIcon
                    ) : null);
        else {
            boolean areEqual =
                    !StringUtils.isNullOrEmpty(contentModel.largeIcon) &&
                    contentModel.largeIcon.equals(contentModel.bigPicture) &&
                    contentModel.roundedLargeIcon == contentModel.roundedBigPicture;

            if(areEqual)
                largeIcon = bigPicture;
            else if(!StringUtils.isNullOrEmpty(contentModel.largeIcon))
                largeIcon =
                        BitmapUtils.getBitmapFromSource(
                                contentModel.largeIcon,
                                contentModel.roundedLargeIcon);
        }

        if (largeIcon != null)
            builder.setLargeIcon(largeIcon);

        if (bigPicture == null)
            return false;

        NotificationCompat.BigPictureStyle bigPictureStyle = new NotificationCompat.BigPictureStyle();

        bigPictureStyle.bigPicture(bigPicture);
        bigPictureStyle.bigLargeIcon(contentModel.hideLargeIconOnExpand ? null : largeIcon);

        if (!StringUtils.isNullOrEmpty(contentModel.title)) {
            CharSequence contentTitle = HtmlUtils.fromHtml(contentModel.title);
            bigPictureStyle.setBigContentTitle(contentTitle);
        }

        if (!StringUtils.isNullOrEmpty(contentModel.body)) {
            CharSequence summaryText = HtmlUtils.fromHtml(contentModel.body);
            bigPictureStyle.setSummaryText(summaryText);
        }

        builder.setStyle(bigPictureStyle);

        return true;
    }

    static Boolean setBigTextStyle(NotificationContentModel contentModel, std::wstring& builder) {

        NotificationCompat.BigTextStyle bigTextStyle = new NotificationCompat.BigTextStyle();

        if (StringUtils.isNullOrEmpty(contentModel.body)) return false;

        CharSequence bigBody = HtmlUtils.fromHtml(contentModel.body);
        bigTextStyle.bigText(bigBody);

        if (!StringUtils.isNullOrEmpty(contentModel.summary)) {
            CharSequence bigSummary = HtmlUtils.fromHtml(contentModel.summary);
            bigTextStyle.setSummaryText(bigSummary);
        }

        if (!StringUtils.isNullOrEmpty(contentModel.title)) {
            CharSequence bigTitle = HtmlUtils.fromHtml(contentModel.title);
            bigTextStyle.setBigContentTitle(bigTitle);
        }

        builder.setStyle(bigTextStyle);

        return true;
    }

    static Boolean setInboxLayout(NotificationContentModel contentModel, std::wstring& builder) {

        NotificationCompat.InboxStyle inboxStyle = new NotificationCompat.InboxStyle();

        if (StringUtils.isNullOrEmpty(contentModel.body)) return false;

        List<String> lines = new ArrayList<>(Arrays.asList(contentModel.body.split("\\r?\\n")));

        if (ListUtils.isNullOrEmpty(lines)) return false;

        CharSequence summary;
        if (StringUtils.isNullOrEmpty(contentModel.summary)) {
            summary = "+ " + lines.size() + " more";
        } else {
            summary = HtmlUtils.fromHtml(contentModel.body);
        }
        inboxStyle.setSummaryText(summary);

        if (!StringUtils.isNullOrEmpty(contentModel.title)) {
            CharSequence contentTitle = HtmlUtils.fromHtml(contentModel.title);
            inboxStyle.setBigContentTitle(contentTitle);
        }

        if (contentModel.summary != null) {
            CharSequence summaryText = HtmlUtils.fromHtml(contentModel.summary);
            inboxStyle.setSummaryText(summaryText);
        }

        for (String line : lines) {
            inboxStyle.addLine(HtmlUtils.fromHtml(line));
        }

        builder.setStyle(inboxStyle);
        return true;
    }
*/
    static std::optional<std::string> GetGroupKey(std::shared_ptr<NotificationContentModel> contentModel, const NotificationChannelModel& channelModel);
/*
    @SuppressWarnings("unchecked")
    static Boolean setMessagingLayout(boolean isGrouping, NotificationContentModel contentModel, NotificationChannelModel channelModel, std::wstring& builder) throws AwesomeNotificationException {
        String groupKey = getGroupKey(contentModel, channelModel);

            String messageQueueKey = groupKey + (isGrouping ? ".Gr" : "");

            int firstNotificationId = contentModel.id;
            List<String> groupIDs = StatusBarManager
                    .activeNotificationsGroup.get(groupKey);

            if(groupIDs == null || groupIDs.size() == 0)
                messagingQueue.remove(messageQueueKey);
            else
                firstNotificationId = Integer.parseInt(groupIDs.get(0));

            NotificationMessageModel currentMessage = new NotificationMessageModel(
                    (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.M) ?
                            contentModel.title : contentModel.summary,
                    contentModel.body,
                    contentModel.largeIcon
            );

            List<NotificationMessageModel> messages =  messagingQueue.get(messageQueueKey);

            if(messages == null)
                messages = new ArrayList<>();

            messages.add(currentMessage);
            messagingQueue.put(messageQueueKey, messages);

            contentModel.id = firstNotificationId;
            contentModel.messages = messages;

            NotificationCompat.MessagingStyle messagingStyle =
                    new NotificationCompat.MessagingStyle(contentModel.summary);

            for(NotificationMessageModel message : contentModel.messages) {
                Person.Builder personBuilder =  new Person.Builder()
                        .setName(message.title);

                if(!StringUtils.isNullOrEmpty(contentModel.largeIcon)){
                    Bitmap largeIcon = BitmapUtils.getBitmapFromSource(
                            contentModel.largeIcon,
                            contentModel.roundedLargeIcon);

                    if(largeIcon != null)
                        personBuilder.setIcon(
                                IconCompat.createWithBitmap(largeIcon));
                }

                Person person = personBuilder.build();

                messagingStyle.addMessage(
                        message.message, message.timestamp, person);
            }

            if (!StringUtils.isNullOrEmpty(contentModel.summary)){
                messagingStyle.setConversationTitle(contentModel.summary);
                messagingStyle.setGroupConversation(isGrouping);
            }

            builder.setStyle((NotificationCompat.Style) messagingStyle);

        return true;
    }

    static Boolean setMediaPlayerLayout(NotificationContentModel contentModel, List<NotificationButtonModel> actionButtons, std::wstring& builder) {

        ArrayList<Integer> indexes = new ArrayList<>();
        for (int i = 0; i < actionButtons.size(); i++) {
            NotificationButtonModel b = actionButtons.get(i);
            if (b.showInCompactView) indexes.add(i);
        }

        if(!StatusBarManager
                .isFirstActiveOnGroupKey(contentModel.groupKey)
        ){
            List<String> lastIds = StatusBarManager.activeNotificationsGroup.get(contentModel.groupKey);
            if(lastIds != null && lastIds.size() > 0)
                contentModel.id = Integer.parseInt(lastIds.get(0));
        }

        int[] showInCompactView = toIntArray(indexes);

        // This fix is to show the notification in Android versions >= 11 in the QuickSettings area.
        // https://developer.android.com/guide/topics/media/media-controls
	    // https://github.com/rafaelsetragni/awesome_notifications/pull/364
        AwesomeNotificationsPlugin.mediaSession.setMetadata(
                new MediaMetadataCompat.Builder()
                        .putString(MediaMetadataCompat.METADATA_KEY_TITLE, contentModel.title)
                        .putString(MediaMetadataCompat.METADATA_KEY_ARTIST, contentModel.body)
                        .build()
        );

        builder.setStyle(
                new androidx.media.app.NotificationCompat.MediaStyle()
                        .setShowActionsInCompactView(showInCompactView)
                        .setShowCancelButton(true)
                        .setMediaSession(AwesomeNotificationsPlugin.mediaSession.getSessionToken())
        );

        if (!StringUtils.isNullOrEmpty(contentModel.summary)) {
            builder.setSubText(contentModel.summary);
        }

        if(contentModel.progress != null)
            builder.setProgress(
                    100,
                    Math.max(0, Math.min(100, IntegerUtils.extractInteger(contentModel.progress, 0))),
                    contentModel.progress == null
            );

        builder.setShowWhen(false);

        return true;
    }

    static void setProgressLayout(NotificationModel notificationModel, std::wstring& builder) {
        builder.setProgress(
                100,
                Math.max(0, Math.min(100, IntegerUtils.extractInteger(notificationModel.content.progress, 0))),
                notificationModel.content.progress == null
        );
    }

    static void setPhoneCallLayout(NotificationModel notificationModel, std::wstring& builder) {
        // RemoteViews notificationLayout = new RemoteViews(context.getPackageName(), android.R.layout.incoming_call);
        // //RemoteViews notificationLayoutExpanded = new RemoteViews(context.getPackageName(), R.layout.incoming_call_large);
    
        // builder
        //     .setStyle(new NotificationCompat.DecoratedCustomViewStyle())
        //     .setCustomContentView(notificationLayout);
        //     //.setCustomBigContentView(notificationLayoutExpanded);
    }

    static int[] toIntArray(ArrayList<Integer> list) {
        if (list == null || list.size() <= 0) return new int[0];

        int[] result = new int[list.size()];
        for (int i = 0; i < list.size(); i++) {
            result[i] = list.get(i);
        }

        return result;
    }
    */
};
