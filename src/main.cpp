#include "curl/curl.h"
#include "application.h"
#include "util/log.h"

static void teslarc_print_help()
{
    printf("TeslaRC: Remote Tesla Controller Tool\n\n");
    printf("Usage: teslarc (command)\n\n");
    printf("Commands:\n");
    printf("  charge (get | set <percentage>)\n");
}

int main(int argc, char const *argv[])
{
    teslarc::Session session;

    curl_global_init(CURL_GLOBAL_ALL);

    if (argc < 2) {
        teslarc_print_help();
        return 1;
    }

    teslarc::run_once(&session, argc - 1, argv + 1);

    curl_global_cleanup();

    return 0;
}
