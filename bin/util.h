//
// Created by mgt on 11/12/19.
//

#ifndef UNIQUE_LAB_SHELL_UTIL_H
#define UNIQUE_LAB_SHELL_UTIL_H

#include "../system_call.h"

namespace mgt::bin {
char getchar(int fd) {
  char tmp[2] = {0};
  int cnt = mgt::sys_wrapped::read(fd, tmp, 1);
  if (cnt)
    return tmp[0];
  else
    return EOF;
}

void putchar(int fd, char ch) {
  char tmp[2] = {0};
  tmp[0] = ch;
  mgt::sys_wrapped::write(fd, tmp, 1);
}

} // namespace mgt::bin
#endif //UNIQUE_LAB_SHELL_UTIL_H
