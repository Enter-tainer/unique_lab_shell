//
// Created by mgt on 11/4/19.
//

#ifndef UNIQUE_LAB_SHELL_REPL_H
#define UNIQUE_LAB_SHELL_REPL_H

#include <optional>
#include <string>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>

#include "readline.h"
#include "shell/echo.h"
#include "shell/exit.h"
#include "shell/pwd.h"
#include "shell/cd.h"
#include "shell/kill.h"
#include "shell/fork_and_exec.h"

namespace mgt {

static const std::string prompt{">>= "}; // NOLINT(cert-err58-cpp)

void process_input(const std::string &input);

void repl();

void load_config(const std::string &path);
} // namespace mgt

#endif //UNIQUE_LAB_SHELL_REPL_H