#include <iostream>
#include <string>

#include "charge.h"
#include "util/user_prompt.h"

namespace teslarc {

int run_charge(int argc, const char *argv[])
{
    std::string username = util::prompt_username();
    std::string password = util::prompt_password();

    return 0;
}

} // namespace teslarc
