#ifndef _UTIL_LOG_H_
#define _UTIL_LOG_H_

#include <stdio.h>
#include <string.h>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#ifdef TESLARC_DEBUG_ENABLED
#define LOG_DEBUG(fmt, ...) printf("[DEBUG %s:%s:%d] " fmt "\n", __FILENAME__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define LOG_DEBUG(fmt, ...)
#endif

#define LOG_ERROR(fmt, ...) printf("\033[1;31m[ERROR %s:%s:%d] " fmt "\033[0m\n", __FILENAME__, __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define LOGGER(level, fmt, ...) LOG_##level(fmt, ##__VA_ARGS__)

#endif
