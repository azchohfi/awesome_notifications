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

constexpr std::initializer_list<NotificationImportance> All_NotificationImportance = { NotificationImportance::None,
    NotificationImportance::Min,
    NotificationImportance::Low,
    NotificationImportance::Default,
    NotificationImportance::High,
    NotificationImportance::Max };

/*
static int ToWindowsPriority(std::optional<NotificationImportance> importance);

static int ToWindowsImportance(std::optional<NotificationImportance> importance);

static NotificationImportance FromWindowsPriority(int ordinal);

static NotificationImportance FromWindowsImportance(int ordinal);
*/