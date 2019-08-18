#include <stdio.h>

#include "teslarc.h"
#include "util/log.h"

namespace teslarc {

int run_loop()
{
    LOGGER(INFO, "Running loop\n");
    return 0;
};

int run_once(int argc, const char *argv[])
{
    LOGGER(DEBUG, "Running once");
    return 0;
}

} // namespace teslarc
