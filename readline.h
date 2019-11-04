//
// Created by mgt on 11/4/19.
//

#ifndef UNIQUE_LAB_SHELL_READLINE_H
#define UNIQUE_LAB_SHELL_READLINE_H

#include <string>

#include<readline/readline.h>
#include<readline/history.h>

namespace mgt {
std::string readline(const std::string &prompt);

void add_history(const std::string &cmd);
}
#endif //UNIQUE_LAB_SHELL_READLINE_H
