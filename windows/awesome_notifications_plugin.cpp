#include "include/awesome_notifications/awesome_notifications_plugin.h"
#include "definitions.h"

// This must be included before many other Windows headers.
#include <windows.h>

// For getPlatformVersion; remove unless needed for your plugin implementation.
#include <VersionHelpers.h>

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>

#include <map>
#include <string>
#include <vector>
#include <memory>
#include <sstream>

#include <wil/win32_helpers.h>
#include <wil/filesystem.h>
#include <wil/stl.h>
#include <winrt/base.h>
#include <winrt/Windows.Foundation.h>
#include <MddBootstrap.h>
#include <winrt/Microsoft.Windows.AppNotifications.h>
#include <appmodel.h>

#include <propkey.h> //PKEY properties
#include <propsys.h>
#include <ShObjIdl_core.h>

#include "notifications/models/NotificationModel.h"
#include "notifications/models/NotificationChannelGroupModel.h"
#include "notifications/models/NotificationChannelModel.h"
#include "notifications/NotificationSender.h"

namespace {

template <typename T>
// Helper method for getting an argument from an EncodableValue
T GetArgument(const std::string arg, const flutter::EncodableValue* args, T fallback) {
    const auto* arguments = std::get_if<flutter::EncodableMap>(args);
    if (arguments) {
        return GetArgument(arg, arguments, fallback);
    }
    return T{fallback};
}

template <typename T>
T GetArgument(const std::string arg, const flutter::EncodableMap* arguments, T fallback) {
    T result{fallback};
    auto result_it = arguments->find(flutter::EncodableValue(arg));
    if (result_it != arguments->end()) {
        if(const auto* r = std::get_if<T>(&result_it->second)) {
        result = *r;
        }
    }
    return result;
}

class AwesomeNotificationsPlugin : public flutter::Plugin {
 public:
    static void RegisterWithRegistrar(flutter::PluginRegistrarWindows *registrar);

    static inline bool debug = false;

    AwesomeNotificationsPlugin(flutter::PluginRegistrarWindows *registrar);

    void channelMethodInitialize(const flutter::MethodCall<flutter::EncodableValue> &method_call,
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
    void channelMethodGetDrawableData(const flutter::MethodCall<flutter::EncodableValue> &method_call,
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
    void channelMethodGetPlatformVersion(const flutter::MethodCall<flutter::EncodableValue> &method_call,
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
    void channelIsNotificationAllowed(const flutter::MethodCall<flutter::EncodableValue> &method_call,
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
    void channelShowNotificationPage(const flutter::MethodCall<flutter::EncodableValue> &method_call,
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
    void channelShowAlarmPage(const flutter::MethodCall<flutter::EncodableValue> &method_call,
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
    void channelShowGlobalDndPage(const flutter::MethodCall<flutter::EncodableValue> &method_call,
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
    void channelMethodCheckPermissions(const flutter::MethodCall<flutter::EncodableValue> &method_call,
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
    void channelMethodShouldShowRationale(const flutter::MethodCall<flutter::EncodableValue> &method_call,
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
    void channelRequestNotification(const flutter::MethodCall<flutter::EncodableValue> &method_call,
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
    winrt::fire_and_forget channelMethodCreateNotification(const flutter::MethodCall<flutter::EncodableValue> &method_call,
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
    void channelMethodListAllSchedules(const flutter::MethodCall<flutter::EncodableValue> &method_call,
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
    void channelMethodGetNextDate(const flutter::MethodCall<flutter::EncodableValue> &method_call,
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
    void channelMethodGetLocalTimeZone(const flutter::MethodCall<flutter::EncodableValue> &method_call,
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
    void channelMethodGetUtcTimeZone(const flutter::MethodCall<flutter::EncodableValue> &method_call,
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
    void channelMethodSetChannel(const flutter::MethodCall<flutter::EncodableValue> &method_call,
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
    void channelMethodRemoveChannel(const flutter::MethodCall<flutter::EncodableValue> &method_call,
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
    void channelMethodGetBadgeCounter(const flutter::MethodCall<flutter::EncodableValue> &method_call,
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
    void channelMethodSetBadgeCounter(const flutter::MethodCall<flutter::EncodableValue> &method_call,
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
    void channelMethodIncrementBadge(const flutter::MethodCall<flutter::EncodableValue> &method_call,
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
    void channelMethodDecrementBadge(const flutter::MethodCall<flutter::EncodableValue> &method_call,
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
    void channelMethodResetBadge(const flutter::MethodCall<flutter::EncodableValue> &method_call,
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
    void channelMethodDismissNotification(const flutter::MethodCall<flutter::EncodableValue> &method_call,
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
    void channelMethodCancelNotification(const flutter::MethodCall<flutter::EncodableValue> &method_call,
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
    void channelMethodCancelSchedule(const flutter::MethodCall<flutter::EncodableValue> &method_call,
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
    void channelMethodDismissNotificationsByChannelKey(const flutter::MethodCall<flutter::EncodableValue> &method_call,
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
    void channelMethodCancelSchedulesByChannelKey(const flutter::MethodCall<flutter::EncodableValue> &method_call,
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
    void channelMethodCancelNotificationsByChannelKey(const flutter::MethodCall<flutter::EncodableValue> &method_call,
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
    void channelMethodDismissNotificationsByGroupKey(const flutter::MethodCall<flutter::EncodableValue> &method_call,
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
    void channelMethodCancelSchedulesByGroupKey(const flutter::MethodCall<flutter::EncodableValue> &method_call,
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
    void channelMethodCancelNotificationsByGroupKey(const flutter::MethodCall<flutter::EncodableValue> &method_call,
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
    void channelMethodDismissAllNotifications(const flutter::MethodCall<flutter::EncodableValue> &method_call,
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
    void channelMethodCancelAllSchedules(const flutter::MethodCall<flutter::EncodableValue> &method_call,
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
    void channelMethodCancelAllNotifications(const flutter::MethodCall<flutter::EncodableValue> &method_call,
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
    void channelMethodStartForeground(const flutter::MethodCall<flutter::EncodableValue> &method_call,
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
    void channelMethodStopForeground(const flutter::MethodCall<flutter::EncodableValue> &method_call,
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);

    virtual ~AwesomeNotificationsPlugin();

 private:

    void SetDefaultConfigurations(std::string defaultIcon, flutter::EncodableList channelsData, flutter::EncodableList channelGroupsData);
    void SetChannelGroups(flutter::EncodableList channelGroupsData);
    void SetChannels(flutter::EncodableList channelsData);
    void SetDefaults(std::string defaultIcon);

    void SetDisplayNameAndIcon(std::string defaultIcon) noexcept;

    // The registrar for this plugin, for accessing the window.
    flutter::PluginRegistrarWindows *registrar_;

    // Called when a method is called on this plugin's channel from Dart.
    void HandleMethodCall(
        const flutter::MethodCall<flutter::EncodableValue> &method_call,
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
};

// static
void AwesomeNotificationsPlugin::RegisterWithRegistrar(
    flutter::PluginRegistrarWindows *registrar) {
    auto channel =
        std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
            registrar->messenger(), "awesome_notifications",
            &flutter::StandardMethodCodec::GetInstance());

    auto plugin = std::make_unique<AwesomeNotificationsPlugin>(registrar);

    channel->SetMethodCallHandler(
        [plugin_pointer = plugin.get()](const auto &call, auto result) {
            plugin_pointer->HandleMethodCall(call, std::move(result));
        });

    registrar->AddPlugin(std::move(plugin));
}

AwesomeNotificationsPlugin::AwesomeNotificationsPlugin(flutter::PluginRegistrarWindows *registrar)
    : registrar_(registrar) {}

AwesomeNotificationsPlugin::~AwesomeNotificationsPlugin() {}

void AwesomeNotificationsPlugin::HandleMethodCall(
    const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
    try {
        if (method_call.method_name().compare(Definitions::CHANNEL_METHOD_INITIALIZE) == 0) {
            channelMethodInitialize(method_call, std::move(result));
        } else if (method_call.method_name().compare(Definitions::CHANNEL_METHOD_GET_DRAWABLE_DATA) == 0) {
            channelMethodGetDrawableData(method_call, std::move(result));
        } else if (method_call.method_name().compare(Definitions::CHANNEL_METHOD_ENABLE_WAKELOCK) == 0) {
            channelMethodGetPlatformVersion(method_call, std::move(result));
        } else if (method_call.method_name().compare(Definitions::CHANNEL_METHOD_IS_NOTIFICATION_ALLOWED) == 0) {
            channelIsNotificationAllowed(method_call, std::move(result));
        } else if (method_call.method_name().compare(Definitions::CHANNEL_METHOD_SHOW_NOTIFICATION_PAGE) == 0) {
            channelShowNotificationPage(method_call, std::move(result));
        } else if (method_call.method_name().compare(Definitions::CHANNEL_METHOD_SHOW_ALARM_PAGE) == 0) {
            channelShowAlarmPage(method_call, std::move(result));
        } else if (method_call.method_name().compare(Definitions::CHANNEL_METHOD_SHOW_GLOBAL_DND_PAGE) == 0) {
            channelShowGlobalDndPage(method_call, std::move(result));
        } else if (method_call.method_name().compare(Definitions::CHANNEL_METHOD_CHECK_PERMISSIONS) == 0) {
            channelMethodCheckPermissions(method_call, std::move(result));
        } else if (method_call.method_name().compare(Definitions::CHANNEL_METHOD_SHOULD_SHOW_RATIONALE) == 0) {
            channelMethodShouldShowRationale(method_call, std::move(result));
        } else if (method_call.method_name().compare(Definitions::CHANNEL_METHOD_REQUEST_NOTIFICATIONS) == 0) {
            channelRequestNotification(method_call, std::move(result));
        } else if (method_call.method_name().compare(Definitions::CHANNEL_METHOD_CREATE_NOTIFICATION) == 0) {
            channelMethodCreateNotification(method_call, std::move(result));
        } else if (method_call.method_name().compare(Definitions::CHANNEL_METHOD_LIST_ALL_SCHEDULES) == 0) {
            channelMethodListAllSchedules(method_call, std::move(result));
        } else if (method_call.method_name().compare(Definitions::CHANNEL_METHOD_GET_NEXT_DATE) == 0) {
            channelMethodGetNextDate(method_call, std::move(result));
        } else if (method_call.method_name().compare(Definitions::CHANNEL_METHOD_GET_LOCAL_TIMEZONE_IDENTIFIER) == 0) {
            channelMethodGetLocalTimeZone(method_call, std::move(result));
        } else if (method_call.method_name().compare(Definitions::CHANNEL_METHOD_GET_UTC_TIMEZONE_IDENTIFIER) == 0) {
            channelMethodGetUtcTimeZone(method_call, std::move(result));
        } else if (method_call.method_name().compare(Definitions::CHANNEL_METHOD_SET_NOTIFICATION_CHANNEL) == 0) {
            channelMethodSetChannel(method_call, std::move(result));
        } else if (method_call.method_name().compare(Definitions::CHANNEL_METHOD_REMOVE_NOTIFICATION_CHANNEL) == 0) {
            channelMethodRemoveChannel(method_call, std::move(result));
        } else if (method_call.method_name().compare(Definitions::CHANNEL_METHOD_GET_BADGE_COUNT) == 0) {
            channelMethodGetBadgeCounter(method_call, std::move(result));
        } else if (method_call.method_name().compare(Definitions::CHANNEL_METHOD_SET_BADGE_COUNT) == 0) {
            channelMethodSetBadgeCounter(method_call, std::move(result));
        } else if (method_call.method_name().compare(Definitions::CHANNEL_METHOD_INCREMENT_BADGE_COUNT) == 0) {
            channelMethodIncrementBadge(method_call, std::move(result));
        } else if (method_call.method_name().compare(Definitions::CHANNEL_METHOD_DECREMENT_BADGE_COUNT) == 0) {
            channelMethodDecrementBadge(method_call, std::move(result));
        } else if (method_call.method_name().compare(Definitions::CHANNEL_METHOD_RESET_BADGE) == 0) {
            channelMethodResetBadge(method_call, std::move(result));
        } else if (method_call.method_name().compare(Definitions::CHANNEL_METHOD_DISMISS_NOTIFICATION) == 0) {
            channelMethodDismissNotification(method_call, std::move(result));
        } else if (method_call.method_name().compare(Definitions::CHANNEL_METHOD_CANCEL_NOTIFICATION) == 0) {
            channelMethodCancelNotification(method_call, std::move(result));
        } else if (method_call.method_name().compare(Definitions::CHANNEL_METHOD_CANCEL_SCHEDULE) == 0) {
            channelMethodCancelSchedule(method_call, std::move(result));
        } else if (method_call.method_name().compare(Definitions::CHANNEL_METHOD_DISMISS_NOTIFICATIONS_BY_CHANNEL_KEY) == 0) {
            channelMethodDismissNotificationsByChannelKey(method_call, std::move(result));
        } else if (method_call.method_name().compare(Definitions::CHANNEL_METHOD_CANCEL_SCHEDULES_BY_CHANNEL_KEY) == 0) {
            channelMethodCancelSchedulesByChannelKey(method_call, std::move(result));
        } else if (method_call.method_name().compare(Definitions::CHANNEL_METHOD_CANCEL_NOTIFICATIONS_BY_CHANNEL_KEY) == 0) {
            channelMethodCancelNotificationsByChannelKey(method_call, std::move(result));
        } else if (method_call.method_name().compare(Definitions::CHANNEL_METHOD_DISMISS_NOTIFICATIONS_BY_GROUP_KEY) == 0) {
            channelMethodDismissNotificationsByGroupKey(method_call, std::move(result));
        } else if (method_call.method_name().compare(Definitions::CHANNEL_METHOD_CANCEL_SCHEDULES_BY_GROUP_KEY) == 0) {
            channelMethodCancelSchedulesByGroupKey(method_call, std::move(result));
        } else if (method_call.method_name().compare(Definitions::CHANNEL_METHOD_CANCEL_NOTIFICATIONS_BY_GROUP_KEY) == 0) {
            channelMethodCancelNotificationsByGroupKey(method_call, std::move(result));
        } else if (method_call.method_name().compare(Definitions::CHANNEL_METHOD_DISMISS_ALL_NOTIFICATIONS) == 0) {
            channelMethodDismissAllNotifications(method_call, std::move(result));
        } else if (method_call.method_name().compare(Definitions::CHANNEL_METHOD_CANCEL_ALL_SCHEDULES) == 0) {
            channelMethodCancelAllSchedules(method_call, std::move(result));
        } else if (method_call.method_name().compare(Definitions::CHANNEL_METHOD_CANCEL_ALL_NOTIFICATIONS) == 0) {
            channelMethodCancelAllNotifications(method_call, std::move(result));
        } else if (method_call.method_name().compare(Definitions::CHANNEL_METHOD_START_FOREGROUND) == 0) {
            channelMethodStartForeground(method_call, std::move(result));
        } else if (method_call.method_name().compare(Definitions::CHANNEL_METHOD_STOP_FOREGROUND) == 0) {
            channelMethodStopForeground(method_call, std::move(result));
        } else {
            result->NotImplemented();
        }

    } catch (const std::exception& e) {
        if (AwesomeNotificationsPlugin::debug) {
            std::wcout << e.what() << std::endl;
        }
        
        result->Error(method_call.method_name(), std::string(e.what()));
    }

}

inline bool IsPackagedProcess()
{
    UINT32 n{};
    const auto rc = GetCurrentPackageFullName(&n, nullptr);
    return rc == ERROR_INSUFFICIENT_BUFFER;
}

std::wstring ReplaceAll(std::wstring str, const std::wstring& from, const std::wstring& to) {
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::wstring::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}

HWND GetRootWindow(flutter::FlutterView *view) {
    return ::GetAncestor(view->GetNativeWindow(), GA_ROOT);
}

void AwesomeNotificationsPlugin::SetDisplayNameAndIcon(std::string defaultIcon) noexcept
{
    // Not mandatory, but it's highly recommended to specify AppUserModelId
    //SetCurrentProcessExplicitAppUserModelID(L"TestAppId");

    // Icon is mandatory
    winrt::com_ptr<IPropertyStore> propertyStore;
    wil::unique_hwnd hWindow{ GetConsoleWindow() };

    SHGetPropertyStoreForWindow(hWindow.get(), IID_PPV_ARGS(&propertyStore));

    defaultIcon = "/data/flutter_assets/" + defaultIcon;

    auto modulePath = wil::GetModuleFileNameW<std::wstring>(nullptr);

    size_t found = modulePath.find_last_of(L"/\\");
    modulePath = modulePath.substr(0, found);

    auto wDefaultIcon = modulePath + std::wstring(defaultIcon.begin(), defaultIcon.end());
    wDefaultIcon = ReplaceAll(wDefaultIcon, std::wstring(L"/"), std::wstring(L"\\"));

    wil::unique_prop_variant propVariantIcon;
    wil::unique_cotaskmem_string sth = wil::make_unique_string<wil::unique_cotaskmem_string>(wDefaultIcon.c_str());
    propVariantIcon.pwszVal = sth.release();
    propVariantIcon.vt = VT_LPWSTR;
    propertyStore->SetValue(PKEY_AppUserModel_RelaunchIconResource, propVariantIcon);

    // App name is not mandatory, but it's highly recommended to specify it
    wil::unique_prop_variant propVariantAppName;
    auto hWnd = GetRootWindow(registrar_->GetView());
    WCHAR title[1024];
    GetWindowTextW(hWnd, title, 1023);
    wil::unique_cotaskmem_string prodName = wil::make_unique_string<wil::unique_cotaskmem_string>(title);
    propVariantAppName.pwszVal = prodName.release();
    propVariantAppName.vt = VT_LPWSTR;
    propertyStore->SetValue(PKEY_AppUserModel_RelaunchDisplayNameResource, propVariantAppName);
}

void AwesomeNotificationsPlugin::channelMethodInitialize(const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
    
    flutter::EncodableList channelsData, channelGroupsData;

    const auto* platformParameters = std::get_if<flutter::EncodableMap>(method_call.arguments());

    debug = GetArgument<bool>(Definitions::INITIALIZE_DEBUG_MODE, platformParameters, debug);

    std::string defaultIconPath = GetArgument<std::string>(Definitions::INITIALIZE_DEFAULT_ICON, platformParameters, "");
    channelsData = GetArgument<flutter::EncodableList>(Definitions::INITIALIZE_CHANNELS, platformParameters, flutter::EncodableList());
    channelGroupsData = GetArgument<flutter::EncodableList>(Definitions::INITIALIZE_CHANNEL_GROUPS, platformParameters, flutter::EncodableList());

    SetDefaultConfigurations(
        defaultIconPath,
        channelsData,
        channelGroupsData
    );

    // Retrieve the app scenario.
    bool isPackaged{ IsPackagedProcess() };
    if (!isPackaged)
    {
        const UINT32 majorMinorVersion{ 0x00010001 };
        PCWSTR versionTag{ L"" };
        const PACKAGE_VERSION minVersion{};

        const HRESULT hr{ MddBootstrapInitialize(majorMinorVersion, versionTag, minVersion) };

        // Check the return code for errors. If there is an error, display the result.
        if (FAILED(hr))
        {
            wprintf(L"Error 0x%X in MddBootstrapInitialize(0x%08X, %s, %hu.%hu.%hu.%hu)\n",
                hr, majorMinorVersion, versionTag, minVersion.Major, minVersion.Minor, minVersion.Build, minVersion.Revision);
            result->Success(false);
            return;
        }

        SetDisplayNameAndIcon(defaultIconPath);
    }

    std::wcout << L"Running as " << (isPackaged ? L"packaged.\n\n" : L"unpackaged.\n\n");

    winrt::Microsoft::Windows::AppNotifications::AppNotificationManager::Default().Register();

    if (AwesomeNotificationsPlugin::debug) {
        std::wcout << "Awesome Notifications service initialized" << std::endl;
    }

    result->Success(true);
}

void AwesomeNotificationsPlugin::SetDefaultConfigurations(std::string defaultIcon, flutter::EncodableList channelsData, flutter::EncodableList channelGroupsData) {

    SetDefaults(defaultIcon);

    SetChannelGroups(channelGroupsData);
    SetChannels(channelsData);

    /*recoverNotificationCreated();
    recoverNotificationDisplayed();
    recoverNotificationDismissed();

    captureNotificationActionOnLaunch();
    */
}

void AwesomeNotificationsPlugin::SetDefaults(std::string defaultIcon) {
    /*
    if (MediaUtils.getMediaSourceType(defaultIcon) != MediaSource.Resource) {
        defaultIcon = null;
    }

    DefaultsManager.saveDefault(context, new DefaultsModel(defaultIcon));
    DefaultsManager.commitChanges(context);
    */
}

void AwesomeNotificationsPlugin::SetChannelGroups(flutter::EncodableList channelGroupsData) {
    if (channelGroupsData.empty()) return;

    std::vector<NotificationChannelGroupModel> channelGroups;

    for (flutter::EncodableValue channelDataObject : channelGroupsData) {
        if(const auto* channelData = std::get_if<flutter::EncodableMap>(&channelDataObject)) {
            NotificationChannelGroupModel channelGroup;
            channelGroup.FromMap(*channelData);

            channelGroups.push_back(channelGroup);
        }
    }

    for (NotificationChannelGroupModel channelGroupModel : channelGroups) {
        //ChannelGroupManager::SaveChannelGroup(channelGroupModel);
    }

    //ChannelManager::CommitChanges();
}

void AwesomeNotificationsPlugin::SetChannels(flutter::EncodableList channelsData) {
    if (channelsData.empty()) return;

    std::vector<NotificationChannelModel> channels;
    boolean forceUpdate = false;

    for (flutter::EncodableValue channelDataObject : channelsData) {
        if(const auto* channelData = std::get_if<flutter::EncodableMap>(&channelDataObject)) {
            NotificationChannelModel channelModel;
            channelModel.FromMap(*channelData);
            forceUpdate = GetArgument<bool>(Definitions::CHANNEL_FORCE_UPDATE, channelData, false);

            channels.push_back(channelModel);
        }
    }

    for (NotificationChannelModel channelModel : channels) {
        //ChannelManager::SaveChannel( channelModel, false, forceUpdate);
    }

    //ChannelManager::CommitChanges();
}

void AwesomeNotificationsPlugin::channelMethodGetDrawableData(const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  result->NotImplemented();
}

void AwesomeNotificationsPlugin::channelMethodGetPlatformVersion(const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  result->NotImplemented();
}

void AwesomeNotificationsPlugin::channelIsNotificationAllowed(const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  result->Success(flutter::EncodableValue(true));
}

void AwesomeNotificationsPlugin::channelShowNotificationPage(const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  result->NotImplemented();
}

void AwesomeNotificationsPlugin::channelShowAlarmPage(const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  result->NotImplemented();
}

void AwesomeNotificationsPlugin::channelShowGlobalDndPage(const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  result->NotImplemented();
}

void AwesomeNotificationsPlugin::channelMethodCheckPermissions(const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  const auto* parameters = std::get_if<flutter::EncodableMap>(method_call.arguments());
  if (parameters == nullptr) {
    throw AwesomeNotificationException("Parameters are required");
  }
  std::string channelKey = GetArgument<std::string>(Definitions::NOTIFICATION_CHANNEL_KEY, parameters, std::string());
  flutter::EncodableList permissions = GetArgument<flutter::EncodableList>(Definitions::NOTIFICATION_PERMISSIONS, parameters, flutter::EncodableList());

  if(permissions.empty()) {
      throw AwesomeNotificationException("Permission list cannot be empty");
  }

  //permissions = PermissionManager.arePermissionsAllowed(channelKey, permissions);

  result->Success(permissions);
}

void AwesomeNotificationsPlugin::channelMethodShouldShowRationale(const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  result->NotImplemented();
}

void AwesomeNotificationsPlugin::channelRequestNotification(const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  result->NotImplemented();
}

winrt::fire_and_forget AwesomeNotificationsPlugin::channelMethodCreateNotification(const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
    const auto* pushData = std::get_if<flutter::EncodableMap>(method_call.arguments());
    NotificationModel notificationModel;
    notificationModel.FromMap(*pushData);

    /*
    if (!PermissionManager.areNotificationsGloballyAllowed()) {
        throw AwesomeNotificationException("Notifications are disabled");
    }
    */

    if (notificationModel.schedule) {
        /*NotificationScheduler::Schedule(
                NotificationSource::Schedule,
                notificationModel
        );*/
        result->Success(false);
    } else {
        result->Success(co_await NotificationSender::Send(
                NotificationSource::Local,
                notificationModel
        ));
    }
}

void AwesomeNotificationsPlugin::channelMethodListAllSchedules(const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  result->NotImplemented();
}

void AwesomeNotificationsPlugin::channelMethodGetNextDate(const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  result->NotImplemented();
}

void AwesomeNotificationsPlugin::channelMethodGetLocalTimeZone(const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  result->Success(flutter::EncodableValue(DateUtils::GetLocalTimeZoneId()));
}

void AwesomeNotificationsPlugin::channelMethodGetUtcTimeZone(const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  result->Success(flutter::EncodableValue("UTC"));
}

void AwesomeNotificationsPlugin::channelMethodSetChannel(const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  result->NotImplemented();
}

void AwesomeNotificationsPlugin::channelMethodRemoveChannel(const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  result->NotImplemented();
}

void AwesomeNotificationsPlugin::channelMethodGetBadgeCounter(const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  result->NotImplemented();
}

void AwesomeNotificationsPlugin::channelMethodSetBadgeCounter(const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  result->NotImplemented();
}

void AwesomeNotificationsPlugin::channelMethodIncrementBadge(const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  result->NotImplemented();
}

void AwesomeNotificationsPlugin::channelMethodDecrementBadge(const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  result->NotImplemented();
}

void AwesomeNotificationsPlugin::channelMethodResetBadge(const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  result->NotImplemented();
}

void AwesomeNotificationsPlugin::channelMethodDismissNotification(const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  result->NotImplemented();
}

void AwesomeNotificationsPlugin::channelMethodCancelNotification(const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  result->NotImplemented();
}

void AwesomeNotificationsPlugin::channelMethodCancelSchedule(const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  result->NotImplemented();
}

void AwesomeNotificationsPlugin::channelMethodDismissNotificationsByChannelKey(const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  result->NotImplemented();
}

void AwesomeNotificationsPlugin::channelMethodCancelSchedulesByChannelKey(const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  result->NotImplemented();
}

void AwesomeNotificationsPlugin::channelMethodCancelNotificationsByChannelKey(const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  result->NotImplemented();
}

void AwesomeNotificationsPlugin::channelMethodDismissNotificationsByGroupKey(const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  result->NotImplemented();
}

void AwesomeNotificationsPlugin::channelMethodCancelSchedulesByGroupKey(const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  result->NotImplemented();
}

void AwesomeNotificationsPlugin::channelMethodCancelNotificationsByGroupKey(const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  result->NotImplemented();
}

void AwesomeNotificationsPlugin::channelMethodDismissAllNotifications(const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  result->NotImplemented();
}

void AwesomeNotificationsPlugin::channelMethodCancelAllSchedules(const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  result->NotImplemented();
}

void AwesomeNotificationsPlugin::channelMethodCancelAllNotifications(const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  result->NotImplemented();
}

void AwesomeNotificationsPlugin::channelMethodStartForeground(const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  result->NotImplemented();
}

void AwesomeNotificationsPlugin::channelMethodStopForeground(const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  result->NotImplemented();
}


}  // namespace

void AwesomeNotificationsPluginRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  AwesomeNotificationsPlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
