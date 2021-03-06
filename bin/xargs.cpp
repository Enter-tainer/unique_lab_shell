//
// Created by mgt on 11/6/19.
//

#include "../system_call.h"
#include "../shell/fork_and_exec.h"

#include <string>
#include <cstring>
#include <iostream>

int main(int argc, char **argv) {
  char delim = '\n';
  if (argc >= 2) {
    auto tmp = std::string(argv[1]);
    if (tmp.find("-d") == 0) {
      delim = argv[2][0];
      for (int i = 1; i + 2 < argc; ++i) {
        argv[i] = argv[i + 2];
      }
      argc -= 2;
    }
  }
  std::string arg;
  while (std::getline(std::cin, arg, delim)) {
    char **new_argv = new char *[argc + 1];
    for (int i = 1; i < argc; ++i)
      new_argv[i - 1] = argv[i];
    new_argv[argc - 1] = const_cast<char *>(arg.c_str());
    new_argv[argc] = nullptr;
    mgt::cmd::run(new_argv[0], new_argv);
    delete[] new_argv;
  }
}