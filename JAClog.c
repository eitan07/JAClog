#include "pch.h"
#include "JAClog.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define RESET_FORMATING "\033[0m"
#define PROG_TAG_COLOR "\033[38;5;222m"
#define PROG_TAG_MAX_LENGTH 64

typedef enum _LogLevel {
	DBUG,
	INFO,
	WARN,
	ERR
} LogLevel;

const char* levelTags[4] = {
	"DEBUG",
	"INFO",
	"WARN",
	"ERROR",
};

const char* levelColors[4] = {
	"\033[38;5;104m",
	"\033[38;5;82m",
	"\033[38;5;214m",
	"\033[38;5;160m"
};

void LogMessage(LogLevel level, const char* format, va_list args);

bool logTimeDate = true;
char* progTag = NULL;

void LogDebug(const char* format, ...) {
	va_list args;
	va_start(args, format);
	LogMessage(DBUG, format, args);
	va_end(args);
}

void LogInfo(const char* format, ...) {
	va_list args;
	va_start(args, format);
	LogMessage(INFO, format, args);
	va_end(args);
}

void LogWarn(const char* format, ...) {
	va_list args;
	va_start(args, format);
	LogMessage(WARN, format, args);
	va_end(args);
}
void LogError(const char* format, ...) {
	va_list args;
	va_start(args, format);
	LogMessage(ERR, format, args);
	va_end(args);
}

void SetJaclogProgTag(const char* tag) {
	if (strlen(tag)) {
		progTag = calloc(PROG_TAG_MAX_LENGTH, sizeof(char));
		progTag = (char*)tag;
	}
	else
		progTag = NULL;
}

void DisableJaclogFeature(JaclogOption opt) {
	switch (opt) {
	case JACLOG_DISABLE_TIME_LOGGING:
		logTimeDate = false;
		break;
	}
}

void LogMessage(LogLevel level, const char* format, va_list args) {

	// Print time and date if not disabled by user
	if (logTimeDate) {
		time_t timeSecs = time(NULL);
		struct tm* tm = localtime(&timeSecs);
		printf("%02d-%02d-%d %02d:%02d:%02d ", tm->tm_mday, tm->tm_mon, tm->tm_year + 1900, tm->tm_hour, tm->tm_min, tm->tm_sec);
	}

	if (progTag == NULL) {
		// Print log level
		printf("%s[%s]%s ", levelColors[level], levelTags[level], RESET_FORMATING);
	}
	else {
		// Print log level with program name tag
		printf("%s[%s]%s %s[%s]%s ", PROG_TAG_COLOR, progTag, RESET_FORMATING, levelColors[level], levelTags[level], RESET_FORMATING);
	}

	// Print the log message
	vprintf(format, args);
	printf("\n");
}