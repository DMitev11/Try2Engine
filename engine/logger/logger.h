#pragma once
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <vector>
/**
 * @brief Based on the spdlog's implementation. \n Use to
 * emit engine and client logs to a separate logger, instead
 * of cout (which emits to a default output stream)
 */
namespace logger {

    /**
     * @brief Based on the spdlog's patterns. \n Equal to:
     * [<name of logger>] [<level of emit (trade, debug
     * etc.)] [<when>] [<message>] [<file, which called the
     * function>:<line>]
     *
     */
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

    /**
     * @brief Types of console loggers
     *
     */
    enum ConsoleLoggerTypes {
        kConsole,
        kConsoleError,
    };

    /**
     * @brief Types of file loggers
     * @warning not tested
     */
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

    /**
     * @see createConsoleLogger
     *
     * @tparam Args variadic, as different parameters are
     * used to initialize file loggers, based on the type
     */
    template <typename... Args>
    void createFileLogger(std::string name,
                          FileLoggerTypes loggerType,
                          Args... args);

    /**
     * @brief Create a sink, to which a logger can emit
     * messages.
     *
     * @note Its one of many (1...n) outputs of 1
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

    /**
     * @see createConsoleSink
     */
    template <typename... Args>
    void
    createFileSink(std::string loggerName, Args... args,
                   FileLoggerTypes sinkType =
                       FileLoggerTypes::kBasicFile,
                   LogLevel logLevel = LogLevel::kTrace,
                   std::string pattern = kDefaultPattern);

    /**
     * @brief Set logger pattern to be used by a logger
     *
     * @note Patterns could be set to a whole
     * logger(overwrites its sink patterns), or a specific
     * sink \n As sinks can have their patterns set during
     * initialization, patterns for loggers could be set
     * explicitly
     * @param loggerName
     * @param pattern
     *
     * @see
     * https://github.com/gabime/spdlog/wiki/3.-Custom-formatting#pattern-flags
     */
    void setLoggerPattern(std::string loggerName,
                          std::string pattern);

    /**
     * @brief Set the logging level of a logger
     *
     * @see LogLevel
     */
    void setLoggerLevel(std::string loggerName,
                        LogLevel logLevel);

    /**
     * @brief Log a message to a specific logger
     *
     * @param filename File of which the message comes from
     * @param fileLine File line which calls this message
     * log
     * @param loggerName Logger which will emit the message
     * @param logLevel
     * @see LogLevel
     *
     * @param msg
     */
    void log(char *const filename, int fileLine,
             std::string loggerName, LogLevel logLevel,
             char const *msg);

    /**
     * @brief Returns if a specific logger exists for
     * logging
     *
     * @param loggerName
     * @return bool
     */
    bool loggerExists(std::string loggerName);

    /**
     * @brief Generalization in the project
     * @note Used to emit messages from around the project,
     * without the necessity to create instances of loggers
     * and emit from each. \n
     * "Client" logger should be used to emit
     * application-based messages "Engine" logger shoule be
     * used to emit messages from modules
     *
     */
    class StaticLogger {
      private:
        explicit StaticLogger(char *const name)
            : kName(name){};
        ~StaticLogger() = default;
        char *const kName;

      public:
        /**
         * @brief Retrieve "Client" logger
         * @see StaticLogger
         *
         * @return StaticLogger* static, instance of spdlog
         * logger created if it does not exist already
         */
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

        /**
         * @brief Retrieve "Engine" logger
         * @see StaticLogger
         *
         * @return StaticLogger* static, instance of spdlog
         * logger created if it does not exist already
         */
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

        /**
         * @brief Log messages to
         * StaticLogger::getEngineLogger() logger
         * ("Engine" logger)
         * @see logger::log
         */
        inline static void
        engineLog(char *const filename, int line,
                  logger::LogLevel logLevel,
                  char *const msg) {
            logger::log(
                filename, line,
                StaticLogger::getEngineLogger()->kName,
                logLevel, msg);
        }

        /**
         * @brief Log messages to
         * StaticLogger::getEngineLogger() logger
         * ("Client" logger)
         * @see logger::log
         */
        inline static void
        clientLog(char *const filename, int line,
                  logger::LogLevel logLevel,
                  char *const msg) {
            logger::log(
                filename, line,
                StaticLogger::getClientLogger()->kName,
                logLevel, msg);
        }
    };

    /**
     * @brief Concatenate prefix of a message and the actual
     * message
     *
     * @note Should be replaced by variadic amount of const
     * char* messages, combined in a stream => const char*
     * @param prefix
     * @param msg
     * @return char*
     */
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
     * @note Catches __FILE__ and __LINE__ macros from the
     * file that called the macro
     *
     * @see logger::log
     */
#define LOG_ENGINE(filename, line, logLevel, prefix,       \
                   error)                                  \
    logger::StaticLogger::engineLog(                       \
        __FILE__, __LINE__, logLevel,                      \
        logger::concatMessage(prefix, error))

    /**
     * @brief Log engine dedicated messages.
     *
     * @see logger::LOG_ENGINE
     */
#define LOG_CLIENT(filename, line, logLevel, prefix,       \
                   error)                                  \
    logger::StaticLogger::clientLog(                       \
        __FILE__, __LINE__, logLevel,                      \
        logger::concatMessage(prefix, error))

    /**
     * @brief Log engine dedicated messages, at "Error"
     * level
     *
     * @see logger::LOG_ENGINE
     * @see logger::LogLevel
     */
#define LOG_ENGINE_ERROR(prefix, error)                    \
    LOG_ENGINE(__FILE__, __LINE__, logger::LogLevel::kErr, \
               prefix, error)

    /**
     * @brief Log engine dedicated messages, at "Critical"
     * level
     *
     * @see logger::LOG_ENGINE
     * @see logger::LogLevel
     */
#define LOG_ENGINE_CRITICAL(prefix, error)                 \
    LOG_ENGINE(__FILE__, __LINE__,                         \
               logger::LogLevel::kCritical, prefix, error)
    /**
     * @brief Log engine dedicated messages, at "Trace"
     * level
     *
     * @see logger::LOG_ENGINE
     * @see logger::LogLevel
     */
#define LOG_ENGINE_TRACE(prefix, error)                    \
    LOG_ENGINE(__FILE__, __LINE__,                         \
               logger::LogLevel::kTrace, prefix, error)

    /**
     * @brief Log engine dedicated messages, at "Info" level
     *
     * @see logger::LOG_ENGINE
     * @see logger::LogLevel
     */
#define LOG_ENGINE_INFO(prefix, error)                     \
    LOG_ENGINE(__FILE__, __LINE__,                         \
               logger::LogLevel::kInfo, prefix, error)

    /**
     * @brief Log engine dedicated messages, at "Warn" level
     *
     * @see logger::LOG_ENGINE
     * @see logger::LogLevel
     */
#define LOG_ENGINE_WARN(prefix, error)                     \
    LOG_ENGINE(__FILE__, __LINE__,                         \
               logger::LogLevel::kWarn, prefix, error)

    /**
     * @brief Log client dedicated messages, at "Error"
     * level
     *
     * @see logger::LOG_CLIENT
     * @see logger::LogLevel
     */
#define LOG_CLIENT_ERROR(prefix, error)                    \
    LOG_CLIENT(__FILE__, __LINE__, logger::LogLevel::kErr, \
               prefix, error)

    /**
     * @brief Log client dedicated messages, at "Critical"
     * level
     *
     * @see logger::LOG_CLIENT
     * @see logger::LogLevel
     */
#define LOG_CLIENT_CRITICAL(prefix, error)                 \
    LOG_CLIENT(__FILE__, __LINE__,                         \
               logger::LogLevel::kCritical, prefix, error)

    /**
     * @brief Log client dedicated messages, at "Info"
     * level
     *
     * @see logger::LOG_CLIENT
     * @see logger::LogLevel
     */
#define LOG_CLIENT_INFO(prefix, error)                     \
    LOG_CLIENT(__FILE__, __LINE__,                         \
               logger::LogLevel::kInfo, prefix, error)

    /**
     * @brief Log client dedicated messages, at "Warn"
     * level
     *
     * @see logger::LOG_CLIENT
     * @see logger::LogLevel
     */
#define LOG_CLIENT_WARN(prefix, error)                     \
    LOG_CLIENT(__FILE__, __LINE__,                         \
               logger::LogLevel::kWarn, prefix, error)
} // namespace logger