//
// Created by mgt on 11/4/19.
//

#ifndef UNIQUE_LAB_SHELL_KILL_H
#define UNIQUE_LAB_SHELL_KILL_H

#include <string>

#include "../system_call.h"

namespace mgt::cmd {
void kill(const std::string &pid);
}
#endif //UNIQUE_LAB_SHELL_KILL_H
