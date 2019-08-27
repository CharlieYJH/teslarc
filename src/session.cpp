#include "session.h"
#include "teslarc_defs.h"
#include "util/log.h"
#include "util/oauth.h"
#include "util/user_prompt.h"
#include "rapidjson/document.h"
#include "rapidjson/error/en.h"
#include "rapidjson/writer.h"

namespace teslarc {

Session::Session() :
    vidx_(0)
{}

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

    vehicles_.SetObject();
    vidx_ = 0;

    if (access_token_.empty() && !query_access_token()) {
        return false;
    }

    if (!util::oauth_do_get_request(TESLA_API_URL_BASE TESLA_API_URL_VEHICLE, access_token_, &data)) {
        LOGGER(ERROR, "Failed to obtain vehicle information");
        return false;
    }

    rapidjson::Document doc;
    doc.Parse(data.c_str());

    if (doc.HasParseError()) {
        LOGGER(ERROR, "%s", GetParseError_En(doc.GetParseError()));
        return false;
    }

    rapidjson::Value::ConstMemberIterator response = doc.FindMember("response");

    if (response == doc.MemberEnd() || !response->value.IsArray()) {
        LOGGER(ERROR, "No response field in JSON reply");
        return false;
    }

    rapidjson::Document::AllocatorType &alloc = vehicles_.GetAllocator();
    vehicles_.CopyFrom(response->value, alloc);

    return true;
}

bool Session::query_current_vehicle()
{
    const char *first = NULL;

    if (!vehicles_.IsArray() || vehicles_.Empty()) {
        return false;
    }

    printf("\nVehicles for %s:\n", email_.c_str());

    for (size_t i = 0; i < vehicles_.Size(); ++i) {
        const rapidjson::Value &entry = vehicles_.GetArray()[i];
        rapidjson::Value::ConstMemberIterator vin = entry.FindMember("vin");

        if (vin == entry.MemberEnd() || !vin->value.IsString()) {
            continue;
        }

        if (i == 0) {
            first = vin->value.GetString();
        }

        printf("  [%lu] %s\n", i, vin->value.GetString());
    }

    printf("\n");

    if (vehicles_.Size() == 1 && first) {
        printf("Choosing %s by default\n", first);
        vidx_ = 0;
        return true;
    }

    do {
        std::string input;
        size_t idx;
        util::prompt_user_input("Please select a vehicle index [#]: ", &input);

        try {
            idx = std::stoull(input);
        } catch (std::invalid_argument) {
            fprintf(stderr, "Unknown input: %s\n", input.c_str());
            continue;
        } catch (std::out_of_range) {
            fprintf(stderr, "Given index is outside of the range representable by a 64-bit unsigned integer\n");
            continue;
        }

        if (idx >= vehicles_.Size()) {
            fprintf(stderr, "Given index is not within range of the list\n");
            continue;
        }

        vidx_ = idx;
        break;
    } while (true);

    return true;
}

const std::string &Session::email() const
{
    return email_;
}

const std::string &Session::access_token() const
{
    return access_token_;
}

const rapidjson::Document &Session::vehicles() const
{
    return vehicles_;
}

uint64_t Session::vehicle_id() const
{
    if (!vehicles_.IsArray() || vidx_ >= vehicles_.Size()) {
        return 0;
    }

    const rapidjson::Value &vehicle = vehicles_.GetArray()[vidx_];
    rapidjson::Value::ConstMemberIterator vehicle_id = vehicle.FindMember("vehicle_id");

    if (vehicle_id == vehicle.MemberEnd() || !vehicle_id->value.IsInt()) {
        return 0;
    }

    return vehicle_id->value.GetInt();
}

} // namespace teslarc
