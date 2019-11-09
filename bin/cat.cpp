#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-narrowing-conversions"
//
// Created by mgt on 11/5/19.
//

#include "../system_call.h"

namespace mgt::bin {
char getchar(int fd) {
  char tmp[2] = {0};
  mgt::sys_wrapped::read(fd, tmp, 1);
  return tmp[0];
}

void putchar(int fd, char ch) {
  char tmp[2] = {0};
  tmp[0] = ch;
  mgt::sys_wrapped::write(fd, tmp, 1);
}
} // namespace mgt::bin

int main(int argc, char **argv) {
  if (argc == 1) {
    char c;
    while ((c = mgt::bin::getchar(STDIN_FILENO)) > 0) {
      mgt::bin::putchar(STDOUT_FILENO, c);
    }
  }
  for (int i = 1; i < argc; ++i) {
    int fd = mgt::sys_wrapped::open(argv[1], O_RDONLY);
    char c;
    while ((c = mgt::bin::getchar(fd)) > 0) {
      mgt::bin::putchar(STDOUT_FILENO, c);
    }
    mgt::sys_wrapped::close(fd);
  }
}