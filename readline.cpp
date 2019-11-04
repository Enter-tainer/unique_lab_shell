//
// Created by mgt on 11/4/19.
//
#include <stdexcept>

#include "readline.h"

std::string mgt::readline(const std::string &prompt) {
  char *tmp = ::readline(prompt.c_str());
  if (tmp == nullptr)
    throw std::logic_error("EOF");
  std::string res(tmp);
  std::free(tmp);
  return res;
}

void mgt::add_history(const std::string &cmd) {
  ::add_history(cmd.c_str());
}
