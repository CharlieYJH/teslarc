#ifndef _UTIL_USER_PROMPT_H_
#define _UTIL_USER_PROMPT_H_

namespace teslarc {
namespace util {

enum prompt_settings {
    PROMPT_SETTINGS_SHOW_INPUT,
    PROMPT_SETTINGS_HIDE_INPUT
};

void prompt_user_input(const std::string &msg, std::string *var, enum prompt_settings setting = PROMPT_SETTINGS_SHOW_INPUT);
std::string prompt_username();
std::string prompt_password();

} // namespace util
} // namespace teslarc

#endif
