#pragma once
#ifndef LOGGING_H
#define LOGGING_H

#include <iostream>
#include <string>

#ifdef __APPLE__
#include <os/log.h>
#elif defined(__ANDROID__)
#include <android/log.h>
#endif

// Define log levels
enum class LogLevel { Debug, Info, Warning, Error };

inline void logMessage(LogLevel level, char const* tag, char const* format,
                       ...) {
  va_list args;
  va_start(args, format);

#ifdef __APPLE__
  // macOS (OSX) logging using os_log
  os_log_t oslog = os_log_create("simple-2d-engine", tag);

  switch (level) {
    case LogLevel::Debug:
      os_log(oslog, "DEBUG: %s", format);
      break;
    case LogLevel::Info:
      os_log(oslog, "INFO: %s", format);
      break;
    case LogLevel::Warning:
      os_log(oslog, "WARNING: %s", format);
      break;
    case LogLevel::Error:
      os_log(oslog, "ERROR: %s", format);
      break;
  }
#elif defined(__ANDROID__)
  // Android logging using __android_log_print
  int priority = ANDROID_LOG_UNKNOWN;

  switch (level) {
    case LogLevel::Debug:
      priority = ANDROID_LOG_DEBUG;
      break;
    case LogLevel::Info:
      priority = ANDROID_LOG_INFO;
      break;
    case LogLevel::Warning:
      priority = ANDROID_LOG_WARN;
      break;
    case LogLevel::Error:
      priority = ANDROID_LOG_ERROR;
      break;
  }

  __android_log_vprint(priority, tag, format, args);
#endif

  va_end(args);
}

inline void logMessage(LogLevel level, char const* tag, string const& format) {
  logMessage(level, tag, format.c_str());
}

#endif  // LOGGING_H
