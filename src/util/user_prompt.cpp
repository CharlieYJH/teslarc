#include <termios.h>
#include <unistd.h>
#include <iostream>

#include "user_prompt.h"

namespace teslarc {
namespace util {
namespace internal {

struct termios t_old;

void show_terminal_input();
void hide_terminal_input();

} // namespace internal

using namespace internal;

void prompt_user_input(const std::string &msg, std::string *var, enum prompt_settings setting)
{
    std::cout << msg;

    if (setting == PROMPT_SETTINGS_HIDE_INPUT) {
        hide_terminal_input();
    }

    std::cin >> *var;

    if (setting == PROMPT_SETTINGS_HIDE_INPUT) {
        show_terminal_input();
        std::cout << std::endl;
    }
}

std::string prompt_username()
{
    std::string name;
    prompt_user_input("Enter your Tesla email: ", &name, PROMPT_SETTINGS_SHOW_INPUT);
    return name;
}

std::string prompt_password()
{
    std::string pass;
    prompt_user_input("Password: ", &pass, PROMPT_SETTINGS_HIDE_INPUT);
    return pass;
}

namespace internal {

void show_terminal_input()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &t_old);
}

void hide_terminal_input()
{
    tcgetattr(STDIN_FILENO, &t_old);
    struct termios t_new = t_old;
    t_new.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &t_new);
}

} // namespace internal
} // namespace util
} // namespace teslarc
