#include "curl/curl.h"
#include "session.h"
#include "util/log.h"

int main(int argc, char const *argv[])
{
    teslarc::SessionInfo session;

    curl_global_init(CURL_GLOBAL_ALL);

    curl_global_cleanup();

    return 0;
}
