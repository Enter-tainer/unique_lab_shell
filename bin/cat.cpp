#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-narrowing-conversions"
//
// Created by mgt on 11/5/19.
//

#include "../system_call.h"

namespace mgt::bin {
char getchar(int fd) {
  char ch;
  mgt::sys_wrapped::read(fd, &ch, 1);
  return ch;
}

void putchar(int fd, char ch) {
  mgt::sys_wrapped::write(fd, &ch, 1);
}
}

int main(int argc, char **argv) {
  for (int i = 1; i < argc; ++i) {
    int fd = mgt::sys_wrapped::open(argv[1], O_RDONLY, 0755);
    char c;
    while ((c = mgt::bin::getchar(fd))) {
      mgt::bin::putchar(fd, c);
    }
    mgt::sys_wrapped::close(fd);
  }
}