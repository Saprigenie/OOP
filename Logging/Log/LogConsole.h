#ifndef LOGCONSOLE_H
#define LOGCONSOLE_H

#include "Log.h"

class LogConsole: public Log {
public:
    LogConsole(std::string message, LogStyle style);
};

#endif // LOGCONSOLE_H
