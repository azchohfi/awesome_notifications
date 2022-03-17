cmake_minimum_required(VERSION 3.15)
set(PROJECT_NAME "awesome_notifications")
set(CPPWINRT_VERSION "2.0.220325.3")
set(WIL_VERSION "1.0.220201.1")
set(WAS_VERSION "1.1.0-preview1")
project(${PROJECT_NAME} LANGUAGES CXX)
include(FetchContent)

# This value is used when generating builds using this plugin, so it must
# not be changed
set(PLUGIN_NAME "awesome_notifications_plugin")

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz)
FetchContent_MakeAvailable(json)

FetchContent_Declare(nuget
  URL "https://dist.nuget.org/win-x86-commandline/v6.0.0/nuget.exe"
  URL_HASH SHA256=04eb6c4fe4213907e2773e1be1bbbd730e9a655a3c9c58387ce8d4a714a5b9e1
  DOWNLOAD_NO_EXTRACT true
)

find_program(NUGET nuget)
if (NOT NUGET)
    message("Nuget.exe not found, trying to download or use cached version.")
    FetchContent_MakeAvailable(nuget)
    set(NUGET ${nuget_SOURCE_DIR}/nuget.exe)
endif()

execute_process(COMMAND
    ${NUGET} install Microsoft.Windows.ImplementationLibrary -Version ${WIL_VERSION} -OutputDirectory ${CMAKE_BINARY_DIR}/packages
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    RESULT_VARIABLE ret)
if (NOT ret EQUAL 0)
    message(FATAL_ERROR "Failed to install nuget package Microsoft.Windows.ImplementationLibrary.${WIL_VERSION}")
endif()

execute_process(COMMAND
    ${NUGET} install Microsoft.WindowsAppSDK -Version ${WAS_VERSION} -OutputDirectory ${CMAKE_BINARY_DIR}/packages
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    RESULT_VARIABLE ret)
if (NOT ret EQUAL 0)
    message(FATAL_ERROR "Failed to install nuget package Microsoft.WindowsAppSDK.${WAS_VERSION}")
endif()

execute_process(COMMAND
    ${NUGET} install Microsoft.Windows.CppWinRT -Version ${CPPWINRT_VERSION} -OutputDirectory packages
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    RESULT_VARIABLE ret)
if (NOT ret EQUAL 0)
    message(FATAL_ERROR "Failed to install nuget package Microsoft.Windows.CppWinRT.${CPPWINRT_VERSION}")
endif()

set(CPPWINRT ${CMAKE_BINARY_DIR}/packages/Microsoft.Windows.CppWinRT.${CPPWINRT_VERSION}/bin/cppwinrt.exe)
execute_process(COMMAND
    ${CPPWINRT} -input sdk ${CMAKE_BINARY_DIR}/packages/Microsoft.WindowsAppSDK.${WAS_VERSION}/lib/uap10.0/Microsoft.Windows.AppNotifications.winmd -output include
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    RESULT_VARIABLE ret)
if (NOT ret EQUAL 0)
    message(FATAL_ERROR "Failed to run cppwinrt.exe")
endif()

add_library(${PLUGIN_NAME} SHARED
  "awesome_notifications_plugin.cpp"
  "notifications/Models/AbstractModel.h"
  "notifications/Models/AbstractModel.cpp"
  "notifications/Models/NotificationModel.h"
  "notifications/Models/NotificationModel.cpp"
  "notifications/Models/NotificationContentModel.h"
  "notifications/Models/NotificationContentModel.cpp"
  "notifications/Models/NotificationMessageModel.h"
  "notifications/Models/NotificationMessageModel.cpp"
  "notifications/Models/NotificationScheduleModel.h"
  "notifications/Models/NotificationScheduleModel.cpp"
  "notifications/Models/NotificationButtonModel.h"
  "notifications/Models/NotificationButtonModel.cpp"
  "notifications/Models/NotificationCalendarModel.h"
  "notifications/Models/NotificationCalendarModel.cpp"
  "notifications/Models/NotificationChannelGroupModel.h"
  "notifications/Models/NotificationChannelGroupModel.cpp"
  "notifications/Models/NotificationChannelModel.h"
  "notifications/Models/NotificationChannelModel.cpp"
  "notifications/Models/returnedData/NotificationReceived.h"
  "notifications/Models/returnedData/NotificationReceived.cpp"
  "notifications/Models/returnedData/ActionReceived.h"
  "notifications/Models/returnedData/ActionReceived.cpp"
  "notifications/enums/ActionButtonType.h"
  "notifications/enums/ActionButtonType.cpp"
  "notifications/enums/NotificationPrivacy.h"
  "notifications/enums/NotificationPrivacy.cpp"
  "notifications/enums/NotificationLayout.h"
  "notifications/enums/NotificationLayout.cpp"
  "notifications/enums/NotificationCategory.h"
  "notifications/enums/NotificationCategory.cpp"
  "notifications/enums/NotificationSource.h"
  "notifications/enums/NotificationSource.cpp"
  "notifications/enums/NotificationLifeCycle.h"
  "notifications/enums/NotificationLifeCycle.cpp"
  "notifications/enums/NotificationImportance.h"
  "notifications/enums/NotificationImportance.cpp"
  "notifications/enums/GroupSort.h"
  "notifications/enums/GroupSort.cpp"
  "notifications/enums/GroupAlertBehaviour.h"
  "notifications/enums/GroupAlertBehaviour.cpp"
  "notifications/enums/DefaultRingtoneType.h"
  "notifications/enums/DefaultRingtoneType.cpp"
  "notifications/exceptions/AwesomeNotificationException.h"
  "notifications/NotificationSender.h"
  "notifications/NotificationSender.cpp"
  "notifications/NotificationBuilder.h"
  "notifications/NotificationBuilder.cpp"
  "utils/JsonUtils.h"
  "utils/JsonUtils.cpp"
  "utils/StringUtils.h"
  "utils/StringUtils.cpp"
  "utils/IntegerUtils.h"
  "utils/IntegerUtils.cpp"
  "utils/MapUtils.h"
  "utils/DateUtils.h"
  "utils/DateUtils.cpp"
  "definitions.h"
)
apply_standard_settings(${PLUGIN_NAME})
set_target_properties(${PLUGIN_NAME} PROPERTIES
  CXX_VISIBILITY_PRESET hidden)
target_compile_features(${PLUGIN_NAME} PRIVATE cxx_std_20)
target_compile_options(${PLUGIN_NAME} PRIVATE /await)
target_compile_definitions(${PLUGIN_NAME} PRIVATE FLUTTER_PLUGIN_IMPL)
target_include_directories(${PLUGIN_NAME} INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_include_directories(${PLUGIN_NAME} PRIVATE
  "${CMAKE_BINARY_DIR}/include")

SET_PROPERTY( TARGET ${PLUGIN_NAME} PROPERTY VS_USER_PROPS
  ${CMAKE_BINARY_DIR}/packages/Microsoft.WindowsAppSDK.${WAS_VERSION}/build/Microsoft.WindowsAppSDK.props
  ${CMAKE_BINARY_DIR}/packages/Microsoft.WindowsAppSDK.${WAS_VERSION}/build/native/WindowsAppSDK-Nuget-Native.C.props
  ${CMAKE_BINARY_DIR}/packages/Microsoft.Windows.CppWinRT.${CPPWINRT_VERSION}/build/native/Microsoft.Windows.CppWinRT.props
  "${CMAKE_CURRENT_SOURCE_DIR}/Directory.Build.props")

target_link_libraries(${PLUGIN_NAME} PRIVATE ${CMAKE_BINARY_DIR}/packages/Microsoft.Windows.CppWinRT.${CPPWINRT_VERSION}/build/native/Microsoft.Windows.CppWinRT.targets)
target_link_libraries(${PLUGIN_NAME} PRIVATE ${CMAKE_BINARY_DIR}/packages/Microsoft.Windows.ImplementationLibrary.${WIL_VERSION}/build/native/Microsoft.Windows.ImplementationLibrary.targets)
target_link_libraries(${PLUGIN_NAME} PRIVATE ${CMAKE_BINARY_DIR}/packages/Microsoft.WindowsAppSDK.${WAS_VERSION}/build/Microsoft.WindowsAppSDK.targets)

target_link_libraries(${PLUGIN_NAME} PRIVATE flutter flutter_wrapper_plugin windowsapp nlohmann_json::nlohmann_json Microsoft.WindowsAppRuntime.Bootstrap)

# List of absolute paths to libraries that should be bundled with the plugin
set(awesome_notifications_bundled_libraries
  "$<TARGET_FILE:${PLUGIN_NAME}>/../Microsoft.WindowsAppRuntime.Bootstrap.dll"
  PARENT_SCOPE
)
