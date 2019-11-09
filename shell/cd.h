//
// Created by mgt on 11/4/19.
//

#ifndef UNIQUE_LAB_SHELL_CD_H
#define UNIQUE_LAB_SHELL_CD_H

#include <iostream>
#include <string>

#include <unistd.h>
#include "../system_call.h"

namespace mgt::cmd {
void cd(const std::string &path);
} // namespace mgt::cmd
#endif //UNIQUE_LAB_SHELL_CD_H
