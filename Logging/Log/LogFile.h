#ifndef LOGFILE_H
#define LOGFILE_H

#include "Log.h"

class LogFile: public Log {
public:
    LogFile(std::string message, LogStyle style);
};

#endif // LOGFILE_H
