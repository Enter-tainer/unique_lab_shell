#include <cstdlib>
#include <cstdio>
#include <string>

#include "readline.h"
#include "system_call.h"
#include "repl.h"

void sig_handle(int sig) {
  if (sig == SIGINT) {
    mgt::refresh_prompt();
  }
}

int main() {
  mgt::load_config("/home/mgt/.mgt.sh.rc");
  mgt::sys_wrapped::signal(SIGINT, sig_handle);
  mgt::sys_wrapped::dup2(1, 2);
  mgt::repl();
  return 0;
}