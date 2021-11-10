#ifndef LOG_H
#define LOG_H

#include "string"

#include "../UtilityEnums/LogStyle.h"

class Log {
private:
    std::string log_message_;
    int log_style_;
public:
    Log(std::string message, LogStyle style);

    std::string getMessage();
    int getStyle();
};

#endif // LOG_H
