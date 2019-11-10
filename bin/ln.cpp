//
// Created by mgt on 11/10/19.
//

#include <cstring>
#include <string>
#include <iostream>

#include "../system_call.h"

int main(int argc, char **argv) {
  if (argc <= 2) {
    std::cout << "Too few arguments" << std::endl;
    ::exit(0);
  } else if (argc == 3) {
    mgt::sys_wrapped::link(argv[1], argv[2]);
    ::exit(0);
  } else if (argc == 4) {
    if (!strcmp(argv[1], "-s")) {
      mgt::sys_wrapped::symlink(argv[1], argv[2]);
    } else {
      std::cout << "Argument Error" << std::endl;
      ::exit(0);
    }
  }
}