#ifndef _UTIL_OAUTH_H_
#define _UTIL_OAUTH_H_

#include <string>

namespace teslarc {
namespace util {

bool oauth_get_access_token(const std::string &email, const std::string &password, std::string *token);
bool oauth_do_get_request(const std::string &url, const std::string &token, std::string *data);

} // namespace util
} // namespace teslarc

#endif
