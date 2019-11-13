//
// Created by mgt on 11/13/19.
//

#include "export.h"


void mgt::cmd::export_env(const std::string &name, const std::string &value) {
  sys_wrapped::setenv(name.c_str(), value.c_str(), true);
}
