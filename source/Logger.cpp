#include "Logger.hpp"

#include <cstdio>
#include <cstdarg>

// Definicja i inicjalizacja statycznej zmiennej logLevel
LogLevel Logger::logLevel = INFO; // Ustaw domyślny poziom logowania na INFO

void Logger::log(LogLevel level, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    if(level >= logLevel) {
        printf("%s[%s]%s ", logLevelToColor(level), logLevelToString(level), ANSI_COLOR_RESET);
        vprintf(format, args);
        printf("\n");
        fflush(stdout);
    }

    va_end(args);
}

const char* Logger::logLevelToString(LogLevel level)
{
    switch (level) {
      case LogLevel::DEBUG: return "DEBUG";
      case LogLevel::INFO: return "INFO";
      case LogLevel::WARNING: return "WARNING";
      case LogLevel::ERROR: return "ERROR";
      default: return "UNKNOWN";
    }
}

const char* Logger::logLevelToColor(LogLevel level)
{
    switch (level) {
      case LogLevel::DEBUG: return ANSI_COLOR_CYAN;
      case LogLevel::INFO: return ANSI_COLOR_GREEN;
      case LogLevel::WARNING: return ANSI_COLOR_YELLOW;
      case LogLevel::ERROR: return ANSI_COLOR_RED;
      default: return "";
    }
}

void Logger::setLogLevel(LogLevel level)
{
    logLevel = level;
}
