#pragma once
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <vector>
namespace logger {

    static const char *const kDefaultPattern =
        "[logger: %n] [level: %l] [ts: %c] [msg: %v] "
        "[caller: %g:%#]";

    /**
     * @brief All levels of logging
     *
     * @attention Priority is set bottom to top.\n
     * If logger level is set to Trace
     * => all messages would emit.
     * If set to Warn
     * => all messages from Warn to Critical would emit,
     * but anything before(Debug, Info, Trace) would not.
     *
     */
    enum LogLevel {
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

    /**
     * @brief Create a logger to emit messages
     *
     * @attention Its a collective of sinks.
     * @see logger::createConsoleSink
     *
     * @param name Used for distinct it from other loggers
     * @param loggerType Normal console messages, or very
     * urgent program breaking errors
     */
    void createConsoleLogger(std::string name,
                             ConsoleLoggerTypes loggerType);

    template <typename... Args>
    void createFileLogger(std::string name,
                          FileLoggerTypes loggerType,
                          Args... args);

    /**
     * @brief Create a sink, to which a logger can emit
     * messages.
     *
     * @attention Its one of many (1...n) outputs of 1
     * logger.\n
     * Can have different differrent message pattern,
     * stylization and level.\n
     *
     * @see logger::createConsoleSink
     *
     * @param loggerName Logger to attach this sink to
     * @param sinkType Same as console logger types
     * @param logLevel Same as console logger levels
     * @see logger::createConsoleLogger
     *
     * @param pattern Defines a message pattern to be used
     * for logging
     * @see
     * https://github.com/gabime/spdlog/wiki/3.-Custom-formatting#pattern-flags
     */
    void createConsoleSink(
        std::string loggerName,
        ConsoleLoggerTypes sinkType =
            ConsoleLoggerTypes::kConsole,
        LogLevel logLevel = LogLevel::kTrace,
        std::string pattern = kDefaultPattern);

    template <typename... Args>
    void
    createFileSink(std::string loggerName, Args... args,
                   FileLoggerTypes sinkType =
                       FileLoggerTypes::kBasicFile,
                   LogLevel logLevel = LogLevel::kTrace,
                   std::string pattern = kDefaultPattern);

    void setLoggerPattern(std::string loggerName,
                          std::string pattern);

    void setLoggerLevel(std::string loggerName,
                        LogLevel logLevel);

    void log(char *const filename, int fileLine,
             std::string loggerName, LogLevel logLevel,
             char const *msg);

    bool loggerExists(std::string loggerName);

    class StaticLogger {
      private:
        explicit StaticLogger(char *const name)
            : name(name){};
        ~StaticLogger() = default;
        char *const name;

      public:
        static StaticLogger *getClientLogger() {
            if (!logger::loggerExists("Client")) {
                logger::createConsoleLogger(
                    "Client", ConsoleLoggerTypes::kConsole);
                logger::setLoggerPattern("Client",
                                         kDefaultPattern);
            }

            static StaticLogger clientLogger("Client");
            return &clientLogger;
        }
        static StaticLogger *getEngineLogger() {
            if (!logger::loggerExists("Engine")) {
                logger::createConsoleLogger(
                    "Engine", ConsoleLoggerTypes::kConsole);
                logger::setLoggerPattern("Engine",
                                         kDefaultPattern);
            }

            static StaticLogger engineLogger("Engine");
            return &engineLogger;
        }
        inline static void
        engineLog(char *const filename, int line,
                  logger::LogLevel logLevel,
                  char *const msg) {
            logger::log(
                filename, line,
                StaticLogger::getEngineLogger()->name,
                logLevel, msg);
        }
        inline static void
        clientLog(char *const filename, int line,
                  logger::LogLevel logLevel,
                  char *const msg) {
            logger::log(
                filename, line,
                StaticLogger::getEngineLogger()->name,
                logLevel, msg);
        }
    };

    inline char *concatMessage(const char *prefix,
                               const char *msg) {
        size_t len = std::strlen(prefix) + std::strlen(msg);
        char *fullMessage = new char[len + 1];
        strcpy(fullMessage, prefix);
        strcat(fullMessage, msg);
        return fullMessage;
    }

    /**
     * @brief Log engine dedicated messages.
     *
     * @note Use LOG_CLIENT_<TYPE> (ex. LOG_CLIENT_INFO)
     *
     * @param filename __FILE__
     */
#define LOG_ENGINE(filename, line, logLevel, prefix,       \
                   error)                                  \
    logger::StaticLogger::engineLog(                       \
        __FILE__, __LINE__, logLevel,                      \
        logger::concatMessage(prefix, error))

    /**
     * @brief Log client dedicated messages.
     *
     */
#define LOG_CLIENT(filename, line, logLevel, prefix,       \
                   error)                                  \
    logger::StaticLogger::clientLog(                       \
        __FILE__, __LINE__, logLevel,                      \
        logger::concatMessage(prefix, error))

#define LOG_ENGINE_ERROR(prefix, error)                    \
    LOG_ENGINE(__FILE__, __LINE__, logger::LogLevel::kErr, \
               prefix, error)
#define LOG_ENGINE_CRITICAL(prefix, error)                 \
    LOG_ENGINE(__FILE__, __LINE__,                         \
               logger::LogLevel::kCritical, prefix, error)
#define LOG_ENGINE_INFO(prefix, error)                     \
    LOG_ENGINE(__FILE__, __LINE__,                         \
               logger::LogLevel::kInfo, prefix, error)
#define LOG_ENGINE_WARN(prefix, error)                     \
    LOG_ENGINE(__FILE__, __LINE__,                         \
               logger::LogLevel::kWarn, prefix, error)

#define LOG_CLIENT_ERROR(prefix, error)                    \
    LOG_CLIENT(__FILE__, __LINE__, logger::LogLevel::kErr, \
               prefix, error)
#define LOG_CLIENT_CRITICAL(prefix, error)                 \
    LOG_CLIENT(__FILE__, __LINE__,                         \
               logger::LogLevel::kCritical, prefix, error)
#define LOG_CLIENT_INFO(prefix, error)                     \
    LOG_CLIENT(__FILE__, __LINE__,                         \
               logger::LogLevel::kInfo, prefix, error)
#define LOG_CLIENT_WARN(prefix, error)                     \
    LOG_CLIENT(__FILE__, __LINE__,                         \
               logger::LogLevel::kWarn, prefix, error)
} // namespace logger