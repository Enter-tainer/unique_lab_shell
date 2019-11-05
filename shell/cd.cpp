//
// Created by mgt on 11/4/19.
//

#include "cd.h"

void mgt::cmd::cd(const std::string &path) {
  if (path.empty())
    return;
  mgt::sys_wrapped::chdir(path.c_str());
}
