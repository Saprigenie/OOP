#ifndef LOGGABLE_H
#define LOGGABLE_H

#include "string"

#include "../UtilityEnums/LogMode.h"
#include "../UtilityEnums/LogStyle.h"
#include "../Logger/Logger.h"
#include "../Log/LogFile.h"
#include "../Log/LogConsole.h"

class Loggable {
    bool logging_active_ = false;
public:
    void LogActive();
    void LogDisable();
    void LogInfo(int mode, int style, std::string message);
};

#endif // LOGGABLE_H
