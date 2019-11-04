//
// Created by mgt on 11/4/19.
//

#include "pwd.h"

std::string mgt::cmd::get_cwd() {
  char *s = ::get_current_dir_name();
  std::string res(s);
  free(s);
  return res;
}

void mgt::cmd::pwd() {
  std::cout << get_cwd() << std::endl;
}
