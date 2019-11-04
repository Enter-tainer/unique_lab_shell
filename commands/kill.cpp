//
// Created by mgt on 11/4/19.
//

#include "kill.h"

void mgt::cmd::kill(const std::string &pid) {
  mgt::sys_wrapped::kill(std::stoi(pid), SIGKILL);
}
