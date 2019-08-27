#ifndef _TESLARC_CHARGE_H_
#define _TESLARC_CHARGE_H_

#include "session.h"

namespace teslarc {
namespace module {

int charge(teslarc::Session *session, int argc, const char *argv[]);

} // namespace app
} // namespace teslarc

#endif
