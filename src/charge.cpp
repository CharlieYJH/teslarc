#include <iostream>
#include <string>

#include "charge.h"
#include "teslarc_defs.h"
#include "util/user_prompt.h"
#include "util/oauth.h"
#include "util/log.h"

namespace teslarc {

int run_charge(int argc, const char *argv[])
{
    std::string username = util::prompt_username();
    std::string password = util::prompt_password();
    std::string access_token;
    std::string data;

    if (!util::oauth_get_access_token(username, password, &access_token)) {
        LOGGER(ERROR, "Failed to acquire access_token");
        return 1;
    }

    if (!util::oauth_do_get_request(TESLA_API_URL_BASE TESLA_API_URL_VEHICLE, access_token, &data)) {
        LOGGER(ERROR, "Failed to obtain vehicle information");
        return 1;
    }

    return 0;
}

} // namespace teslarc
