#pragma once

#include <string>
#include <exception>

class AwesomeNotificationException : public std::exception {
 public:
    inline AwesomeNotificationException(const char* msg)
        : std::exception(msg) {
    }
};