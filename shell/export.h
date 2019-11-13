//
// Created by mgt on 11/13/19.
//

#ifndef UNIQUE_LAB_SHELL_EXPORT_H
#define UNIQUE_LAB_SHELL_EXPORT_H

#include <iostream>
#include <cstring>
#include <string>

#include "../system_call.h"

namespace mgt::cmd {
void export_env(const std::string &name, const std::string &value);
}
#endif //UNIQUE_LAB_SHELL_EXPORT_H
