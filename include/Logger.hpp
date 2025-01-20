#ifndef LOGGER_HPP
#define LOGGER_HPP

// Definicje kodów ANSI
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

enum LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

class Logger {
public:
  static void log(LogLevel level, const char* format, ...);
  static const char* logLevelToString(LogLevel level);
  static const char* logLevelToColor(LogLevel level);
  static void setLogLevel(LogLevel level);

private:
    static LogLevel logLevel;
};

#endif // LOGGER_HPP