//
// Created by mgt on 11/4/19.
//

#ifndef UNIQUE_LAB_SHELL_PWD_H
#define UNIQUE_LAB_SHELL_PWD_H

#include <unistd.h>

#include <string>
#include <iostream>
namespace mgt::cmd {
static std::string get_cwd();
void pwd();
}
#endif //UNIQUE_LAB_SHELL_PWD_H