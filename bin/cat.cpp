#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-narrowing-conversions"
//
// Created by mgt on 11/5/19.
//

#include "../system_call.h"
#include "util.h"

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