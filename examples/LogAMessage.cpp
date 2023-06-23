#include <logger/logger.h>

void LogAMessageStatically() {
    // A message can emitted statically to a default logging
    // sink
    LOG_CLIENT_ERROR(
        "<This is a prefix ex. [Your Application Name:]",
        "And this is my message ['my error message']");
    // There are different levels of emit
    LOG_CLIENT_WARN(
        "<This is a prefix ex. [Your Application Name:]",
        "And this is my message ['my warning message']");
    LOG_CLIENT_INFO(
        "<This is a prefix ex. [Your Application Name:]",
        "And this is my message ['my info message']");
    LOG_CLIENT_CRITICAL(
        "<This is a prefix ex. [Your Application Name:]",
        "And this is my message ['my critical message']");
    LOG_CLIENT_TRACE(
        "<This is a prefix ex. [Your Application Name:]",
        "And this is my message ['my critical message']");
    // or to an 'engine' sink
    LOG_ENGINE_CRITICAL(
        "<This is a prefix ex. [Module Name:]",
        "And this is my message ['my critical message']");
};

void createAConsoleLoggerAndASink() {
    // Create a logger with a name and type - console or
    // console error
    logger::createConsoleLogger(
        "arbitraryConsoleLogger",
        logger::ConsoleLoggerTypes::kConsole);
    // Create a sink to which the logger will emit to. Give
    // the sink a console type, a level from which messages
    // will be capture (this case Info->Critical, Trace is
    // skipped) and give it a pattern
    // https://github.com/gabime/spdlog/wiki/3.-Custom-formatting#pattern-flags
    logger::createConsoleSink(
        "arbitraryConsoleLogger",
        logger::ConsoleLoggerTypes::kConsole,
        logger::LogLevel::kInfo, "%g:%#");
};

int main(int argc, char const *argv[]) {
    LogAMessageStatically();
    createAConsoleLoggerAndASink();
}