#include "curl/curl.h"
#include "teslarc.h"
#include "util/log.h"

int main(int argc, char const *argv[])
{
    curl_global_init(CURL_GLOBAL_ALL);

    if (argc > 1) {
        teslarc::run_once(argc, argv);
    } else {
        teslarc::run_loop();
    }

    curl_global_cleanup();

    return 0;
}
