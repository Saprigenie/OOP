#include "Logger.h"

Logger* Logger::logger_inst = nullptr;

Logger::Logger() {
    log_path_ = "log.txt";
    file_stream_.open(log_path_);
    if (!file_stream_.is_open()) {
        std::string error_msg = "Can't open file with path: " + log_path_;
        throw new std::invalid_argument(error_msg);
    }

    log_count_ = 0;
}

Logger& Logger::getInstance() {
    if (logger_inst == nullptr) {
        logger_inst = new Logger();
    }
    return *logger_inst;
}

void Logger::setLogPath(std::string new_path) {
    file_stream_.close();
    log_path_ = new_path;
    file_stream_.open(log_path_);
}

Logger& Logger::operator << (LogFile& log_info) {
    if (log_info.getStyle() & LogStyle::kNumbered)
        log_count_++;
    file_stream_ << stylize_log(log_info);
    file_stream_.flush();
    return *logger_inst;
}

Logger& Logger::operator << (LogConsole& log_info) {
    if (log_info.getStyle() & LogStyle::kNumbered)
        log_count_++;
    std::cout << stylize_log(log_info);
    fflush(stdout);
    return *logger_inst;
}

std::string Logger::stylize_log(Log& log_info) {
    std::string message = "";

    if (log_info.getStyle() & LogStyle::kCapitalise) {
        message = log_info.getMessage();
        for (auto it = message.begin(); it < message.end(); it++) {
            *it = toupper(*it);
        }
    }  else {
        message = log_info.getMessage();
    }
    if (log_info.getStyle() & LogStyle::kTime) {
        time_t curr_sec = time(nullptr);
        std::string curr_time = asctime(localtime(&curr_sec));
        curr_time.pop_back();
        message = "(" + curr_time + ") " + message;
    }

    if (log_info.getStyle() & LogStyle::kNumbered) {
        message = "[" + std::to_string(log_count_) + "] " + message;
    }

    message += "\n";

    return message;
}

Logger::~Logger() {
    file_stream_.close();
}
