#include "session.h"
#include "teslarc_defs.h"
#include "util/log.h"
#include "util/oauth.h"
#include "util/user_prompt.h"

namespace teslarc {

void Session::query_email()
{
    email_ = util::prompt_username();
}

void Session::query_password()
{
    password_ = util::prompt_password();
}

bool Session::query_access_token()
{
    if (email_.empty()) {
        query_email();
    }

    if (password_.empty()) {
        query_password();
    }

    if (!util::oauth_get_access_token(email_, password_, &access_token_)) {
        LOGGER(ERROR, "Failed to acquire access_token");
        return false;
    }

    return true;
}

bool Session::query_vehicles()
{
    std::string data;

    if (access_token_.empty() && !query_access_token()) {
        return false;
    }

    if (!util::oauth_do_get_request(TESLA_API_URL_BASE TESLA_API_URL_VEHICLE, access_token_, &data)) {
        LOGGER(ERROR, "Failed to obtain vehicle information");
        return false;
    }

    return true;
}

} // namespace teslarc
