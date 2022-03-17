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

    @NonNull
    public static void createActionButtons(NotificationModel notificationModel, NotificationChannelModel channel, NotificationCompat.Builder builder) {

        if (ListUtils.isNullOrEmpty(notificationModel.actionButtons)) return;

        for (NotificationButtonModel buttonProperties : notificationModel.actionButtons) {

            // If reply is not available, do not show it
            if (
                android.os.Build.VERSION.SDK_INT < Build.VERSION_CODES.N &&
                buttonProperties.buttonType == ActionButtonType.InputField
            ){
                continue;
            }

            Intent actionIntent = buildNotificationIntentFromModel(
                    Definitions.NOTIFICATION_BUTTON_ACTION_PREFIX + "_" + buttonProperties.key,
                    notificationModel,
                    channel,
                    buttonProperties.buttonType == ActionButtonType.DisabledAction ||
                    buttonProperties.buttonType == ActionButtonType.KeepOnTop ?
                                    KeepOnTopActionReceiver.class : getNotificationTargetActivityClass()
            );

            actionIntent.putExtra(Definitions.NOTIFICATION_AUTO_DISMISSIBLE, buttonProperties.autoDismissible);
            actionIntent.putExtra(Definitions.NOTIFICATION_SHOW_IN_COMPACT_VIEW, buttonProperties.showInCompactView);
            actionIntent.putExtra(Definitions.NOTIFICATION_ENABLED, buttonProperties.enabled);
            actionIntent.putExtra(Definitions.NOTIFICATION_BUTTON_TYPE, buttonProperties.buttonType.toString());
            actionIntent.putExtra(Definitions.NOTIFICATION_BUTTON_KEY, buttonProperties.key);

            PendingIntent actionPendingIntent = null;

            if (buttonProperties.enabled) {

                if (
                    buttonProperties.buttonType == ActionButtonType.KeepOnTop ||
                    buttonProperties.buttonType == ActionButtonType.DisabledAction
                ) {

                    actionPendingIntent = PendingIntent.getBroadcast(
                            notificationModel.content.id,
                            actionIntent,
                            PendingIntent.FLAG_IMMUTABLE | PendingIntent.FLAG_UPDATE_CURRENT
                    );

                } else if (buttonProperties.buttonType == ActionButtonType.InputField) {

                    actionPendingIntent = PendingIntent.getActivity(
                            notificationModel.content.id,
                            actionIntent,
                            PendingIntent.FLAG_MUTABLE | PendingIntent.FLAG_UPDATE_CURRENT
                    );

                } else {

                    actionPendingIntent = PendingIntent.getActivity(
                            notificationModel.content.id,
                            actionIntent,
                            PendingIntent.FLAG_IMMUTABLE | PendingIntent.FLAG_UPDATE_CURRENT
                    );
                }
            }

            int iconResource = 0;
            if (!StringUtils.isNullOrEmpty(buttonProperties.icon)) {
                iconResource = BitmapUtils.getDrawableResourceId(buttonProperties.icon);
            }

            if (
                buttonProperties.buttonType == ActionButtonType.InputField
            ){

                RemoteInput remoteInput = new RemoteInput.Builder(buttonProperties.key)
                        .setLabel(buttonProperties.label)
                        .build();

                NotificationCompat.Action replyAction = new NotificationCompat.Action.Builder(
                        iconResource, buttonProperties.label, actionPendingIntent)
                        .addRemoteInput(remoteInput)
                        .build();

                builder.addAction(replyAction);

            } else {

                builder.addAction(
                    iconResource,
                    HtmlCompat.fromHtml(
                        buttonProperties.isDangerousOption ?
                            "<font color=\"16711680\">" + buttonProperties.label + "</font>" :
                            (
                                buttonProperties.color != null ?
                                    "<font color=\"" + buttonProperties.color.toString() + "\">" + buttonProperties.label + "</font>":
                                    buttonProperties.label
                            ),
                        HtmlCompat.FROM_HTML_MODE_LEGACY
                    ),
                    actionPendingIntent);
            }
        }
    }

    public static final ConcurrentHashMap<String, List<NotificationMessageModel>> messagingQueue = new ConcurrentHashMap<String, List<NotificationMessageModel>>();
*/
 private:

/*
    private static PendingIntent getPendingActionIntent(NotificationModel notificationModel, NotificationChannelModel channelModel) {
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

    private static PendingIntent getPendingDismissIntent(NotificationModel notificationModel, NotificationChannelModel channelModel) {
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
    private static void updateTrackingExtras(NotificationModel notificationModel, NotificationChannelModel channel, Bundle extras) {
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

    private static Class<?> getTargetClass(){
        return getNotificationTargetActivityClass();
    }

    private static String getButtonInputText(Intent intent, String buttonKey) {
        Bundle remoteInput = RemoteInput.getResultsFromIntent(intent);
        if (remoteInput != null) {
            return remoteInput.getCharSequence(buttonKey).toString();
        }
        return null;
    }
*/
    static winrt::Microsoft::Windows::AppNotifications::AppNotification GetNotificationBuilderFromModel(const NotificationModel& notificationModel);

    /*

    private static void setCategoryFlags(NotificationModel notificationModel, Notification androidNotification) {

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

    private static void setNotificationPendingIntents(NotificationModel notificationModel, PendingIntent pendingActionIntent, PendingIntent pendingDismissIntent, NotificationCompat.Builder builder) {
        builder.setContentIntent(pendingActionIntent);
        if(!notificationModel.groupSummary)
            builder.setDeleteIntent(pendingDismissIntent);
    }

    private static void setWakeUpScreen(NotificationModel notificationModel) {
        if (notificationModel.content.wakeUpScreen)
//            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.KITKAT_WATCH)
                wakeUpScreen();
    }

    private static void setCriticalAlert(NotificationChannelModel channel) throws AwesomeNotificationException {
        if (channel.criticalAlerts)
            ensureCriticalAlert();
    }

    private static void setFullScreenIntent(PendingIntent pendingIntent, NotificationModel notificationModel, NotificationCompat.Builder builder) {
        if (BooleanUtils.getValue(notificationModel.content.fullScreenIntent)) {
            builder.setFullScreenIntent(pendingIntent, true);
        }
    }

    private static void setShowWhen(NotificationModel notificationModel, NotificationCompat.Builder builder) {
        builder.setShowWhen(BooleanUtils.getValueOrDefault(notificationModel.content.showWhen, true));
    }

    private static Integer getBackgroundColor(NotificationModel notificationModel, NotificationChannelModel channel, NotificationCompat.Builder builder) {
        Integer bgColorValue;
        bgColorValue = IntegerUtils.extractInteger(notificationModel.content.backgroundColor, null);
        if (bgColorValue != null) {
            builder.setColorized(true);
        } else {
            bgColorValue = getLayoutColor(notificationModel, channel);
        }
        return bgColorValue;
    }

    private static Integer getLayoutColor(NotificationModel notificationModel, NotificationChannelModel channel) {
        Integer layoutColorValue;
        layoutColorValue = IntegerUtils.extractInteger(notificationModel.content.color, channel.defaultColor);
        layoutColorValue = IntegerUtils.extractInteger(layoutColorValue, Color.BLACK);
        return layoutColorValue;
    }

    private static void setImportance(NotificationChannelModel channel, NotificationCompat.Builder builder) {
        builder.setPriority(NotificationImportance.toAndroidPriority(channel.importance));
    }

    private static void setCategory(NotificationModel notificationModel, NotificationCompat.Builder builder){
        if(notificationModel.content.category != null)
            builder.setCategory(notificationModel.content.category.rawValue);
    }

    private static void setOnlyAlertOnce(NotificationModel notificationModel, NotificationChannelModel channel, NotificationCompat.Builder builder) {
        boolean onlyAlertOnceValue = BooleanUtils.getValue(notificationModel.content.notificationLayout == NotificationLayout.ProgressBar || channel.onlyAlertOnce);
        builder.setOnlyAlertOnce(onlyAlertOnceValue);
    }

    private static void setRemoteHistory(NotificationModel notificationModel, NotificationCompat.Builder builder) {
        if(!StringUtils.isNullOrEmpty(notificationModel.remoteHistory) && notificationModel.content.notificationLayout == NotificationLayout.Default)
            builder.setRemoteInputHistory(new CharSequence[]{notificationModel.remoteHistory});
    }

    private static void setLockedNotification(NotificationModel notificationModel, NotificationChannelModel channel, NotificationCompat.Builder builder) {
        boolean contentLocked = BooleanUtils.getValue(notificationModel.content.locked);
        boolean channelLocked = BooleanUtils.getValue(channel.locked);

        if (contentLocked) {
            builder.setOngoing(true);
        } else if (channelLocked) {
            boolean lockedValue = BooleanUtils.getValueOrDefault(notificationModel.content.locked, true);
            builder.setOngoing(lockedValue);
        }
    }

    private static void setTicker(NotificationModel notificationModel, NotificationCompat.Builder builder) {
        String tickerValue;
        tickerValue = StringUtils.getValueOrDefault(notificationModel.content.ticker, null);
        tickerValue = StringUtils.getValueOrDefault(tickerValue, notificationModel.content.summary);
        tickerValue = StringUtils.getValueOrDefault(tickerValue, notificationModel.content.body);
        builder.setTicker(tickerValue);
    }

    private static void setBadge(NotificationModel notificationModel, NotificationChannelModel channelModel, NotificationCompat.Builder builder) {
        if (!notificationModel.groupSummary && BooleanUtils.getValue(channelModel.channelShowBadge)) {
            BadgeManager.incrementGlobalBadgeCounter();
            builder.setNumber(1);
        }
    }

    private static void setAutoCancel(NotificationModel notificationModel, NotificationCompat.Builder builder) {
        builder.setAutoCancel(BooleanUtils.getValueOrDefault(notificationModel.content.autoDismissible, true));
    }

    private static void setBody(NotificationModel notificationModel, NotificationCompat.Builder builder) {
        builder.setContentText(HtmlUtils.fromHtml(notificationModel.content.body));
    }

    private static void setTitle(NotificationModel notificationModel, NotificationChannelModel channelModel, NotificationCompat.Builder builder) {
        if (notificationModel.content.title != null) {
            builder.setContentTitle(HtmlUtils.fromHtml(notificationModel.content.title));
        }
    }

    private static void setVibrationPattern(NotificationChannelModel channelModel, NotificationCompat.Builder builder) {
        if (BooleanUtils.getValue(channelModel.enableVibration)) {
            if (channelModel.vibrationPattern != null && channelModel.vibrationPattern.length > 0) {
                builder.setVibrate(channelModel.vibrationPattern);
            }
        } else {
            builder.setVibrate(new long[]{0});
        }
    }

    private static void setLights(NotificationChannelModel channelModel, NotificationCompat.Builder builder) {
        if (BooleanUtils.getValue(channelModel.enableLights)) {
            Integer ledColorValue = IntegerUtils.extractInteger(channelModel.ledColor, Color.WHITE);
            Integer ledOnMsValue = IntegerUtils.extractInteger(channelModel.ledOnMs, 300);
            Integer ledOffMsValue = IntegerUtils.extractInteger(channelModel.ledOffMs, 700);
            builder.setLights(ledColorValue, ledOnMsValue, ledOffMsValue);
        }
    }

    private static void setVisibility(NotificationModel notificationModel, NotificationChannelModel channelModel, NotificationCompat.Builder builder) {

//        if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.LOLLIPOP) {
//
            Integer visibilityIndex;
            visibilityIndex = IntegerUtils.extractInteger(notificationModel.content.privacy, channelModel.defaultPrivacy.ordinal());
            visibilityIndex = IntegerUtils.extractInteger(visibilityIndex, NotificationPrivacy.Public);

            builder.setVisibility(visibilityIndex - 1);
//        }
    }

    private static void setLayoutColor(NotificationModel notificationModel, NotificationChannelModel channelModel, NotificationCompat.Builder builder) {

        if (notificationModel.content.backgroundColor == null) {
            builder.setColor(getLayoutColor(notificationModel, channelModel));
        } else {
            builder.setColor(getBackgroundColor(notificationModel, channelModel, builder));
        }
    }

    private static void setLargeIcon(NotificationModel notificationModel, NotificationCompat.Builder builder) {
        if (notificationModel.content.notificationLayout != NotificationLayout.BigPicture)
            if (!StringUtils.isNullOrEmpty(notificationModel.content.largeIcon)) {
                Bitmap largeIcon = BitmapUtils.getBitmapFromSource(
                        notificationModel.content.largeIcon,
                        notificationModel.content.roundedLargeIcon);
                if (largeIcon != null)
                    builder.setLargeIcon(largeIcon);
            }
    }

    private static void setSound(NotificationModel notificationModel, NotificationChannelModel channelModel, NotificationCompat.Builder builder) {

        Uri uri = null;

        if (!notificationModel.content.isRefreshNotification && BooleanUtils.getValue(channelModel.playSound)) {
            String soundSource = StringUtils.isNullOrEmpty(notificationModel.content.customSound) ? channelModel.soundSource : notificationModel.content.customSound;
            uri = ChannelManager.retrieveSoundResourceUri(channelModel.defaultRingtoneType, soundSource);
        }

        builder.setSound(uri);
    }

    private static void setSmallIcon(NotificationModel notificationModel, NotificationChannelModel channelModel, NotificationCompat.Builder builder) {
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

    private static void setGrouping(NotificationModel notificationModel, NotificationChannelModel channelModel, NotificationCompat.Builder builder) {

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

    private static void setLayout(NotificationModel notificationModel, NotificationChannelModel channelModel, NotificationCompat.Builder builder) throws AwesomeNotificationException {

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

    private static Boolean setBigPictureLayout(NotificationContentModel contentModel, NotificationCompat.Builder builder) {

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

    private static Boolean setBigTextStyle(NotificationContentModel contentModel, NotificationCompat.Builder builder) {

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

    private static Boolean setInboxLayout(NotificationContentModel contentModel, NotificationCompat.Builder builder) {

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
    private static Boolean setMessagingLayout(boolean isGrouping, NotificationContentModel contentModel, NotificationChannelModel channelModel, NotificationCompat.Builder builder) throws AwesomeNotificationException {
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

    private static Boolean setMediaPlayerLayout(NotificationContentModel contentModel, List<NotificationButtonModel> actionButtons, NotificationCompat.Builder builder) {

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

    private static void setProgressLayout(NotificationModel notificationModel, NotificationCompat.Builder builder) {
        builder.setProgress(
                100,
                Math.max(0, Math.min(100, IntegerUtils.extractInteger(notificationModel.content.progress, 0))),
                notificationModel.content.progress == null
        );
    }

    private static void setPhoneCallLayout(NotificationModel notificationModel, NotificationCompat.Builder builder) {
        // RemoteViews notificationLayout = new RemoteViews(context.getPackageName(), android.R.layout.incoming_call);
        // //RemoteViews notificationLayoutExpanded = new RemoteViews(context.getPackageName(), R.layout.incoming_call_large);
    
        // builder
        //     .setStyle(new NotificationCompat.DecoratedCustomViewStyle())
        //     .setCustomContentView(notificationLayout);
        //     //.setCustomBigContentView(notificationLayoutExpanded);
    }

    private static int[] toIntArray(ArrayList<Integer> list) {
        if (list == null || list.size() <= 0) return new int[0];

        int[] result = new int[list.size()];
        for (int i = 0; i < list.size(); i++) {
            result[i] = list.get(i);
        }

        return result;
    }
    */
};
