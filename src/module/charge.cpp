#include <unistd.h>
#include <iostream>
#include <string>

#include "charge.h"
#include "teslarc_defs.h"
#include "util/oauth.h"
#include "util/log.h"
#include "rapidjson/error/en.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"

#define CHARGE_LOG(level, fmt, ...) MODULE_LOG(charge, level, fmt, ##__VA_ARGS__)

namespace teslarc {
namespace module {
namespace internal {

void print_help();
bool show_charge_data(teslarc::Session *session);
bool set_charge_limit(teslarc::Session *session, int argc, const char *argv[]);

} // namespace internal

using namespace internal;

int charge(teslarc::Session *session, int argc, const char *argv[])
{
    if (argc < 1) {
        CHARGE_LOG(ERROR, "Missing command\n");
        print_help();
        return 1;
    }

    const char *cmd = argv[0];

    if (strcmp(cmd, "show") == 0) {
        show_charge_data(session);
    } else if (strcmp(cmd, "set") == 0) {
        set_charge_limit(session, argc - 1, argv + 1);
    }

    return 0;
}

namespace internal {

void print_help()
{
    printf("Usage: teslarc charge (command)\n\n");
    printf("Commands:\n");
    printf("  show              Show the current charge information.\n");
    printf("  set <percentage>  Set the current charge limit.\n");
}

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

    rapidjson::Document doc;
    doc.SetObject();
    rapidjson::Value::ConstMemberIterator response = doc.MemberEnd();

    for (int retries = 10; (response == doc.MemberEnd() || !response->value.IsObject()) && retries >= 0; --retries, sleep(1)) {
        printf("%s", retries == 10 ? "Waiting for response..." : ".");
        fflush(stdout);

        if (!util::oauth_get(url, session->access_token(), &data)) {
            CHARGE_LOG(ERROR, "Failed to retrieve charge information");
            return false;
        }

        doc.Parse(data.c_str());

        if (doc.HasParseError()) {
            CHARGE_LOG(ERROR, "%s", GetParseError_En(doc.GetParseError()));
            return false;
        }

        response = doc.FindMember("response");
    }

    if (response == doc.MemberEnd() || !response->value.IsObject()) {
        CHARGE_LOG(ERROR, "Unable to get a response from the vehicle");
        return false;
    }

    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    response->value.Accept(writer);

    printf("\n\n=======================================================\n");
    printf("  Charge Information:\n");
    printf("-------------------------------------------------------\n");
    printf("%s\n", buffer.GetString());
    printf("=======================================================\n\n");

    return true;
}

bool set_charge_limit(teslarc::Session *session, int argc, const char *argv[])
{
    if (argc < 1) {
        CHARGE_LOG(ERROR, "Missing charge percentage");
        return false;
    }

    int percentage = 0;

    try {
        percentage = std::stoi(argv[0]);
    } catch (const std::exception &e) {
        CHARGE_LOG(ERROR, "Invalid charge percentage");
        return false;
    }

    if (percentage < 0) {
        CHARGE_LOG(INFO, "Percentage entered is under the minimum. Limiting to 0");
        percentage = 0;
    } else if (percentage > 100) {
        CHARGE_LOG(INFO, "Percentage entered is over the maximum. Limiting to 100");
        percentage = 100;
    }

    return true;
}

} // namespace internal
} // namespace module
} // namespace teslarc

#undef CHARGE_LOG
