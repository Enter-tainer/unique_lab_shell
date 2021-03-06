//
// Created by mgt on 11/5/19.
//

#ifndef UNIQUE_LAB_SHELL_FORK_AND_EXEC_H
#define UNIQUE_LAB_SHELL_FORK_AND_EXEC_H

#include "../system_call.h"

#include <string>
#include <vector>

namespace mgt::cmd {

void basic_run_external(const std::string &file_name, const std::vector<std::string> &argv,
                        int in_fd = STDIN_FILENO,
                        int out_fd = STDOUT_FILENO,
                        bool sync = true);

void run_external_sync(const std::string &file_name, const std::vector<std::string> &argv,
                       int in_fd = STDIN_FILENO,
                       int out_fd = STDOUT_FILENO);

void run_external_async(const std::string &file_name, const std::vector<std::string> &argv,
                        int in_fd = STDIN_FILENO,
                        int out_fd = STDOUT_FILENO);

void run(const std::string &file_name, const std::vector<std::string> &argv, int in_fd, int out_fd, bool sync);

void run(const std::string &file_name, char *const *argv,
         int in_fd = STDIN_FILENO,
         int out_fd = STDOUT_FILENO);
} // namespace mgt::cmd
#endif //UNIQUE_LAB_SHELL_FORK_AND_EXEC_H
