//
// Created by mgt on 11/4/19.
//

#ifndef UNIQUE_LAB_SHELL_REPL_H
#define UNIQUE_LAB_SHELL_REPL_H

#include <optional>
#include <string>
#include <cstdio>
#include <iostream>

#include "readline.h"


namespace mgt {

static const std::string prompt{">>="}; // NOLINT(cert-err58-cpp)

void process_input(const std::string &input);

void repl();
}

#endif //UNIQUE_LAB_SHELL_REPL_H