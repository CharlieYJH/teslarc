#ifndef _SESSION_H_
#define _SESSION_H_

#include <string>

#include "rapidjson/document.h"

namespace teslarc {

class Session
{
    std::string email_;
    std::string password_;
    std::string access_token_;
    rapidjson::Document vehicles_;
    size_t vidx_;

    public:

    Session();

    void query_email();
    void query_password();
    bool query_access_token();
    bool query_vehicles();
    bool query_current_vehicle();

    const std::string &email() const;
    const std::string &access_token() const;
    const rapidjson::Document &vehicles() const;
    uint64_t vehicle_id() const;
};

} // namespace teslarc

#endif
