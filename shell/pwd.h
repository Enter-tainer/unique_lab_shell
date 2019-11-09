//
// Created by mgt on 11/4/19.
//

#ifndef UNIQUE_LAB_SHELL_PWD_H
#define UNIQUE_LAB_SHELL_PWD_H

#include <unistd.h>

#include <string>
#include <iostream>
namespace mgt::cmd {
std::string get_cwd();
void pwd();
} // namespace mgt::cmd
#endif //UNIQUE_LAB_SHELL_PWD_H
