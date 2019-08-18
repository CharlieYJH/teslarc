#include "teslarc.h"
#include "util/log.h"

int main(int argc, char const *argv[])
{
    if (argc > 1) {
        teslarc::run_once(argc, argv);
    } else {
        teslarc::run_loop();
    }

    return 0;
}
