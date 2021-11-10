#include "Loggable.h"

void Loggable::LogActive() {
    logging_active_ = true;
}

void Loggable::LogDisable() {
    logging_active_ = false;
}

void Loggable::LogInfo(int mode, int style, std::string message) {
    if (logging_active_) {
        if (mode & LogMode::kFile) {
            LogFile log_file = LogFile(message, static_cast<LogStyle>(style));
            Logger::getInstance() << log_file;
        }
        if (mode & LogMode::kConsole) {
            LogConsole log_console = LogConsole(message, static_cast<LogStyle>(style));
            Logger::getInstance() << log_console;
        }
    }
}
