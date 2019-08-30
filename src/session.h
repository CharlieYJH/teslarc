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
    rapidjson::Document vdata_;
    size_t vidx_;

    public:

    Session();

    void query_email();
    void query_password();
    bool query_access_token();
    bool query_vehicles();
    bool query_current_vehicle();

    bool wake() const;
    bool ping();

    const std::string &email() const;
    const std::string &access_token() const;
    const rapidjson::Document &vehicles() const;
    const rapidjson::Document &vehicle_data() const;
    const std::string id() const;
};

} // namespace teslarc

#endif
