//
// Created by mgt on 11/4/19.
//

#ifndef UNIQUE_LAB_SHELL_READLINE_H
#define UNIQUE_LAB_SHELL_READLINE_H

#include <string>
#include <optional>

#include<readline/readline.h>
#include<readline/history.h>

#include "string_opt.h"

namespace mgt {
std::optional<std::string> readline(const std::string &prompt);

void add_history(const std::string &cmd);

void refresh_prompt();
} // namespace mgt
#endif //UNIQUE_LAB_SHELL_READLINE_H
