#ifndef _UTIL_LOG_H_
#define _UTIL_LOG_H_

#include <stdio.h>
#include <string.h>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define LOG_INFO(fmt, ...) printf("[INFO %s:%s:%d] " fmt "\n", __FILENAME__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...) printf("[DEBUG %s:%s:%d] " fmt "\n", __FILENAME__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) printf("\033[1;31m[ERROR %s:%s:%d] " fmt "\033[0m\n", __FILENAME__, __FUNCTION__, __LINE__, ##__VA_ARGS__)

#ifdef TESLARC_DEBUG_ENABLED
#define LOGGER(level, fmt, ...) LOG_##level(fmt, ##__VA_ARGS__)
#else
#define LOGGER(level, fmt, ...)
#endif

#define MODULE_INFO_LOG(mod, fmt, ...) printf("\033[1;32m["#mod":INFO]\033[0m " fmt "\n", ##__VA_ARGS__)
#define MODULE_ERROR_LOG(mod, fmt, ...) fprintf(stderr, "\033[1;31m["#mod":ERROR]\033[0m " fmt "\n", ##__VA_ARGS__)
#define MODULE_LOG(mod, level, fmt, ...) do { \
    MODULE_##level##_LOG(mod, fmt, ##__VA_ARGS__); \
    LOGGER(level, fmt, ##__VA_ARGS__); \
} while (0)

#endif
