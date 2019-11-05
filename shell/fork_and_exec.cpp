//
// Created by mgt on 11/5/19.
//

#include "fork_and_exec.h"
#include "../readline.h"

void mgt::cmd::run(const std::string &file_name, const std::vector<std::string> &argv) {
  pid_t pid = mgt::sys_wrapped::fork();
  if (pid == 0) {
    char **c_argv = new char *[argv.size() + 1];
    for (size_t i = 0; i < argv.size(); ++i)
      c_argv[i] = const_cast<char *>(argv[i].data());
    c_argv[argv.size()] = nullptr;
    mgt::sys_wrapped::execvp(file_name.c_str(), c_argv);
    delete[] c_argv;
    ::exit(0);
  } else {
    int status;
    mgt::sys_wrapped::waitpid(pid, &status, 0);
  }
}
