#include <iostream>
#include <vector>
namespace logger {

    // Priority is set bottom to top
    // If logger level is set to Trace
    // => all messages would emit
    // If set to Warn
    // => all messages from Warn to Critical would emit,
    // but anything before(Debug, Info, Trace) would not
    enum LogLevel : int {
        kTrace,
        kDebug,
        kInfo,
        kWarn,
        kErr,
        kCritical
    };

    enum ConsoleLoggerTypes {
        kConsole,
        kConsoleError,
    };

    enum FileLoggerTypes {
        kBasicFile,
        kMultipleFiles,
        kDailyFile,
    };

    // Collective for pushing messages to all sinks
    void createConsoleLogger(std::string name,
                             ConsoleLoggerTypes loggerType);

    template <typename... Args>
    void createFileLogger(std::string name,
                          FileLoggerTypes loggerType,
                          Args... args);
    // Can have different differrent message pattern,
    // stylization and level
    // Its one of many (1...n) outputs of 1 logger
    void createConsoleSink(
        std::string loggerName,
        ConsoleLoggerTypes sinkType =
            ConsoleLoggerTypes::kConsole,
        LogLevel logLevel = LogLevel::kTrace,
        // https://github.com/gabime/spdlog/wiki/3.-Custom-formatting#pattern-flags
        std::string pattern = ("[%l] %n %v (%s)"));
    template <typename... Args>
    void createFileSink(
        std::string loggerName, Args... args,
        FileLoggerTypes sinkType =
            FileLoggerTypes::kBasicFile,
        LogLevel logLevel = LogLevel::kTrace,
        std::string pattern = ("[%l] %n %v (%s)"));
    void setLoggerPattern(std::string loggerName,
                          std::string pattern);
    void setLoggerLevel(std::string loggerName,
                        LogLevel logLevel);
    void log(std::string loggerName, LogLevel logLevel,
             char const *msg);
} // namespace logger