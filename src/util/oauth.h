#ifndef _UTIL_OAUTH_H_
#define _UTIL_OAUTH_H_

#include <string>

namespace teslarc {
namespace util {

bool oauth_get_access_token(const std::string &email, const std::string &password, std::string *token);
bool oauth_get(const std::string &url, const std::string &token, std::string *data);
bool oauth_post(const std::string &url, const std::string &token, const std::string &fields, std::string *data);

} // namespace util
} // namespace teslarc

#endif
