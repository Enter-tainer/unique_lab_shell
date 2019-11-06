//
// Created by mgt on 11/6/19.
//

#include "../system_call.h"

#include <iostream>

namespace mgt::bin {
void mkdir(const char *path) {
  sys_wrapped::mkdir(path, 0755);
}
}

int main(int argc, char **argv) {
  if (argc == 1) {
    std::cout << "Missing operands" << std::endl;
    return 1;
  } else {
    for (int i = 1; i < argc; ++i) {
      mgt::bin::mkdir(argv[i]);
    }
  }
}