#include "oauth.h"
#include "log.h"
#include "../teslarc_defs.h"
#include "curl/curl.h"
#include "rapidjson/document.h"
#include "rapidjson/error/en.h"

namespace teslarc {
namespace util {
namespace internal {

size_t oauth_curl_callback(char *data, size_t size, size_t nmemb, void *userdata);

} // namespace internal

using namespace internal;

#define OAUTH_DUMMY_USERAGENT "curl"

bool oauth_get_access_token(const std::string &email, const std::string &password, std::string *token)
{
    CURL *curl = curl_easy_init();
    CURLcode res;

    if (!curl) {
        return false;
    }

    std::string outdata;
    std::string fields(
        "grant_type=password"
        "&client_id=" TESLA_API_CLIENT_ID
        "&client_secret=" TESLA_API_CLIENT_SECRET
        "&email=" + email +
        "&password=" + password
    );

    curl_easy_setopt(curl, CURLOPT_URL, TESLA_API_URL_BASE TESLA_API_URL_TOKEN);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, fields.c_str());
    curl_easy_setopt(curl, CURLOPT_USERAGENT, OAUTH_DUMMY_USERAGENT);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &outdata);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, oauth_curl_callback);

    if ((res = curl_easy_perform(curl)) != CURLE_OK) {
        LOGGER(ERROR, "%s", curl_easy_strerror(res));
    } else {
        LOGGER(DEBUG, "Received: %s", outdata.c_str());
    }

    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        return false;
    }

    rapidjson::Document doc;
    doc.Parse(outdata.c_str());

    if (doc.HasParseError()) {
        LOGGER(ERROR, "%s", GetParseError_En(doc.GetParseError()));
        return false;
    }

    rapidjson::Value::ConstMemberIterator access_token = doc.FindMember("access_token");

    if (access_token == doc.MemberEnd() || !access_token->value.IsString()) {
        LOGGER(ERROR, "Failed to retrieve access_token field from JSON reply");
        return false;
    }

    *token = access_token->value.GetString();
    LOGGER(DEBUG, "Retrieved access_token: %s", access_token->value.GetString());

    return res == CURLE_OK;
}

bool oauth_do_get_request(const std::string &url, const std::string &token, std::string *data)
{
    CURL *curl = curl_easy_init();
    CURLcode res;

    if (!curl) {
        return false;
    }

    std::string header("Authorization: Bearer " + token);
    struct curl_slist *slist = NULL;

    if (!(slist = curl_slist_append(slist, header.c_str()))) {
        LOGGER(ERROR, "Failed to append Authorization header");
        curl_easy_cleanup(curl);
        return false;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_USERAGENT, OAUTH_DUMMY_USERAGENT);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, data);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, oauth_curl_callback);

    if ((res = curl_easy_perform(curl)) != CURLE_OK) {
        LOGGER(ERROR, "%s", curl_easy_strerror(res));
    } else {
        LOGGER(DEBUG, "Received: %s", data->c_str());
    }

    curl_slist_free_all(slist);
    curl_easy_cleanup(curl);

    return res == CURLE_OK;
}

#undef OAUTH_DUMMY_USERAGENT

namespace internal {

size_t oauth_curl_callback(char *data, size_t size, size_t nmemb, void *userdata)
{
    static_cast<std::string *>(userdata)->assign(data, size * nmemb);
    return size * nmemb;
}

} // namespace internal
} // namespace util
} // namespace teslarc
