#include <stdio.h>

#include "teslarc.h"
#include "charge.h"
#include "util/log.h"

namespace teslarc {

int run_loop()
{
    LOGGER(DEBUG, "Running loop");
    return 0;
};

int run_once(int argc, const char *argv[])
{
    const char *cmd = argv[1];

#define CHECK_SUBROUTINE(cmd, subroutine) strcmp(cmd, subroutine) == 0

    if (CHECK_SUBROUTINE(cmd, "charge")) {
        return run_charge(argc, argv);
    }

#undef CHECK_SUBROUTINE

    return 0;
}

} // namespace teslarc
