#include <iostream>
#include <string>

#include "charge.h"
#include "teslarc_defs.h"
#include "util/oauth.h"
#include "util/log.h"

namespace teslarc {
namespace module {
namespace internal {

bool show_charge_data(teslarc::Session *session);

} // namespace internal

using namespace internal;

int charge(teslarc::Session *session, int argc, const char *argv[])
{
    if (argc == 1) {
        show_charge_data(session);
    }

    return 0;
}

namespace internal {

bool show_charge_data(teslarc::Session *session)
{
    if (!session->wake()) {
        return false;
    }

    std::string id(session->id());

    if (id.empty()) {
        return false;
    }

    std::string url(TESLA_API_URL_BASE TESLA_API_URL_VEHICLE "/" + id + "/data_request/charge_state");
    std::string data;

    if (!util::oauth_get(url, session->access_token(), &data)) {
        LOGGER(ERROR, "Failed to retrieve charge information");
        return false;
    }

    return true;
}

} // namespace internal
} // namespace module
} // namespace teslarc
