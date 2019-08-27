#ifndef _SESSION_H_
#define _SESSION_H_

#include <string>

namespace teslarc {

class Session
{
    std::string email_;
    std::string password_;
    std::string access_token_;

    public:

    void query_email();
    void query_password();
    bool query_access_token();
    bool query_vehicles();
};

} // namespace teslarc

#endif
