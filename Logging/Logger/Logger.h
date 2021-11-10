#ifndef LOGGER_H
#define LOGGER_H

#include <time.h>

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>

#include "../Log/LogFile.h"
#include "../Log/LogConsole.h"
#include "../UtilityEnums/LogStyle.h"

class Logger {
private:
    static Logger* logger_inst;
    std::ofstream file_stream_;
    std::string log_path_;

    long long int log_count_;

    Logger();

public:
    static Logger& getInstance();
    Logger(const Logger& from) = delete;
    Logger& operator =(const Logger& from) = delete;

    void setLogPath(std::string new_path);

    Logger& operator << (LogFile& log_info);
    Logger& operator << (LogConsole& log_info);

    std::string stylize_log(Log& log_info);

    ~Logger();
};

#endif // LOGGER_H
