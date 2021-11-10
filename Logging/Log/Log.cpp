#include "Log.h"

Log::Log(std::string message, LogStyle style) {
    log_message_ = message;
    log_style_ = style;
}

std::string Log::getMessage() {
    return log_message_;
}

int Log::getStyle() {
    return log_style_;
}
