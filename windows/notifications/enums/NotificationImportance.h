#pragma once

#include <optional>
#include <string>

enum class NotificationImportance {
    None,
    Min,
    Low,
    Default,
    High,
    Max
};

std::string NotificationImportanceToString(NotificationImportance notificationImportance);

/*
static int ToWindowsPriority(std::optional<NotificationImportance> importance);

static int ToWindowsImportance(std::optional<NotificationImportance> importance);

static NotificationImportance FromWindowsPriority(int ordinal);

static NotificationImportance FromWindowsImportance(int ordinal);
*/