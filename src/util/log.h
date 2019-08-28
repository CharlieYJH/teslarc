#ifndef _UTIL_LOG_H_
#define _UTIL_LOG_H_

#include <stdio.h>
#include <string.h>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define LOG_INFO(fmt, ...) printf("\033[1;32m[INFO %s:%s:%d]\033[0m " fmt "\n", __FILENAME__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#ifdef TESLARC_DEBUG_ENABLED
#define LOG_DEBUG(fmt, ...) printf("[DEBUG %s:%s:%d] " fmt "\n", __FILENAME__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define LOG_DEBUG(fmt, ...)
#endif
#define LOG_ERROR(fmt, ...) printf("\033[1;31m[ERROR %s:%s:%d]\033[0m " fmt "\n", __FILENAME__, __FUNCTION__, __LINE__, ##__VA_ARGS__)

// General purpose logging
#define LOGGER(level, fmt, ...) LOG_##level(fmt, ##__VA_ARGS__)

#define MODULE_INFO_LOG(mod, fmt, ...) printf("\033[1;32m["#mod":INFO]\033[0m " fmt "\n", ##__VA_ARGS__)
#define MODULE_ERROR_LOG(mod, fmt, ...) fprintf(stderr, "\033[1;31m["#mod":ERROR]\033[0m " fmt "\n", ##__VA_ARGS__)

// Module runtime logging
#ifdef TESLARC_DEBUG_ENABLED
#define MODULE_LOG(mod, level, fmt, ...) LOGGER(level, fmt, ##__VA_ARGS__)
#else
#define MODULE_LOG(mod, level, fmt, ...) MODULE_##level##_LOG(mod, fmt, ##__VA_ARGS__)
#endif

#endif
