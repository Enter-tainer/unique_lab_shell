#include <cstdlib>
#include <cstdio>
#include <string>

#include <readline/readline.h>

#include "readline.h"
#include "system_call.h"
#include "repl.h"

void sig_handle(int sig) {
  if (sig == SIGINT) {
    putchar('\n');
    rl_on_new_line(); // Regenerate the prompt on a newline
    rl_replace_line("", 0); // Clear the previous text
    rl_redisplay();
  }
}

int main() {
  std::string prompt = "user>>= ";
  std::string line_input;
  int i = 0;
  mgt::sys_wrapped::signal(SIGINT, sig_handle);
  repl();
  return 0;
}