//
// Created by mgt on 11/10/19.
//

#include <iostream>
#include <string>

#include "../system_call.h"

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "Too few arguments" << std::endl;
    ::exit(0);
  } else {
    for (int i = 1; i < argc; ++i) {
      mgt::sys_wrapped::unlink(argv[i]);
    }
  }
}