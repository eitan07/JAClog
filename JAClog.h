#pragma once

#ifdef JACLOG_EXPORTS
#define JACLOG_API __declspec(dllexport)
#else
#define JACLOG_API __declspec(dllimport)
#endif

#ifdef CLOG_FUNC_ALIASES
#define D LogDebug
#define I LogInfo
#define W LogWarn
#define E LogError
#endif

typedef enum _JaclogOption {
	JACLOG_DISABLE_TIME_LOGGING
} JaclogOption;

JACLOG_API void LogDebug(const char* format, ...);
JACLOG_API void LogInfo(const char* format, ...);
JACLOG_API void LogWarn(const char* format, ...);
JACLOG_API void LogError(const char* format, ...);
JACLOG_API void SetJaclogProgTag(const char* tag);
JACLOG_API void DisableJaclogFeature(JaclogOption opt);