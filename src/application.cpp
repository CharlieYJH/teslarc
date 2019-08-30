#include <unistd.h>

#include "application.h"
#include "module/charge.h"
#include "util/log.h"

namespace teslarc {
namespace internal {

bool check_valid_command(const char *cmd);

} // namespace internal

using namespace internal;

int run_once(teslarc::Session *session, int argc, const char *argv[])
{
    const char *cmd = argv[0];

    printf("\n=======================================================\n");
    printf("  TeslaRC: Remote Tesla Controller\n");
    printf("=======================================================\n\n");

    if (!check_valid_command(cmd)) {
        fprintf(stderr, "Unknown command: %s\n", cmd);
        return 1;
    }

    if (!session->query_vehicles()) {
        LOGGER(ERROR, "Failed to query vehicle list");
        return 1;
    }

    if (!session->query_current_vehicle()) {
        LOGGER(ERROR, "Failed to select a vehicle");
        return 1;
    }

    if (!session->wake()) {
        LOGGER(ERROR, "Failed to wake vehicle");
        return 1;
    }

    for (int retries = 10; !session->ping() && retries >= 0; --retries, sleep(1)) {
        LOGGER(INFO, "Getting vehicle data...");
    }

    if (strcmp(cmd, "charge") == 0) {
        teslarc::module::charge(session, argc - 1, argv + 1);
    }

    return 0;
}

namespace internal {

bool check_valid_command(const char *cmd)
{
    if (!cmd) {
        return false;
    }

    if (strcmp(cmd, "charge") == 0) {
        return true;
    }

    return false;
}

} // namespace internal
} // namespace teslarc
