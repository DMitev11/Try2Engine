#include "logger.h"
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

void logger::createConsoleLogger(
    std::string name, ConsoleLoggerTypes loggerType) {
    // Only multithreaded implementations used
    switch (loggerType) {
    case ConsoleLoggerTypes::kConsole:
        spdlog::stdout_color_mt(name);
        break;
    case ConsoleLoggerTypes::kConsoleError:
        spdlog::stderr_color_mt(name);
        break;
    }
}

template <typename... Args>
void logger::createFileLogger(std::string name,
                              FileLoggerTypes loggerType,
                              Args... args) {
    switch (loggerType) {
    case FileLoggerTypes::kBasicFile:
        spdlog::basic_logger_mt(name, args...);
        break;
    case FileLoggerTypes::kMultipleFiles:
        spdlog::rotating_logger_mt(name, args...);
        break;
    case FileLoggerTypes::kDailyFile:
        spdlog::daily_logger_mt(name, args...);
        break;
    }
};

void createSink(spdlog::sink_ptr sink,
                std::string loggerName,
                logger::LogLevel logLevel,
                std::string pattern) {
    sink->set_pattern(pattern);
    sink->set_level((spdlog::level::level_enum)logLevel);
    spdlog::get(loggerName)->sinks().push_back(sink);
}

void logger::createConsoleSink(std::string loggerName,
                               ConsoleLoggerTypes sinkType,
                               LogLevel logLevel,
                               std::string pattern) {
    switch (sinkType) {
    case ConsoleLoggerTypes::kConsole:
        return createSink(
            std::make_shared<
                spdlog::sinks::stdout_color_sink_mt>(),
            loggerName, logLevel, pattern);
    case ConsoleLoggerTypes::kConsoleError:
        return createSink(
            std::make_shared<
                spdlog::sinks::stdout_color_sink_mt>(),
            loggerName, logLevel, pattern);
    };
}
template <typename... Args>
void logger::createFileSink(std::string loggerName,
                            Args... args,
                            FileLoggerTypes sinkType,
                            LogLevel logLevel,
                            std::string pattern) {
    switch (sinkType) {
    case FileLoggerTypes::kBasicFile:
        return createSink(
            std::make_shared<
                spdlog::sinks::basic_file_sink_mt>(args...),
            loggerName, logLevel, pattern);
    case FileLoggerTypes::kMultipleFiles:
        return createSink(
            std::make_shared<
                spdlog::sinks::rotating_file_sink_mt>(
                args...),
            loggerName, logLevel, pattern);
    case FileLoggerTypes::kDailyFile:
        return createSink(
            std::make_shared<
                spdlog::sinks::rotating_file_sink_mt>(
                args...),
            loggerName, logLevel, pattern);
    }
}
void logger::setLoggerPattern(std::string loggerName,
                              std::string pattern) {
    return spdlog::get(loggerName)->set_pattern(pattern);
}
void logger::setLoggerLevel(std::string loggerName,
                            logger::LogLevel logLevel) {
    return spdlog::get(loggerName)
        ->set_level((spdlog::level::level_enum)logLevel);
}

void logger::log(std::string loggerName, LogLevel logLevel,
                 const char *msg) {
    switch (logLevel) {
    case logger::LogLevel::kTrace:
        return spdlog::get(loggerName)->trace(msg);
    case logger::LogLevel::kDebug:
        return spdlog::get(loggerName)->debug(msg);
    case logger::LogLevel::kInfo:
        return spdlog::get(loggerName)->info(msg);
    case logger::LogLevel::kWarn:
        return spdlog::get(loggerName)->warn(msg);
    case logger::LogLevel::kErr:
        return spdlog::get(loggerName)->error(msg);
    case logger::LogLevel::kCritical:
        return spdlog::get(loggerName)->critical(msg);
    }
}