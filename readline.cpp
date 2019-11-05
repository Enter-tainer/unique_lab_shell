//
// Created by mgt on 11/4/19.
//
#include <optional>

#include "readline.h"
#include "string_opt.h"

std::optional<std::string> mgt::readline(const std::string &prompt) {
  char *tmp = ::readline(prompt.c_str());
  if (tmp == nullptr)
    return {};
  std::string res(tmp);
  std::free(tmp);
  return mgt::str::trim(res);
}

void mgt::add_history(const std::string &cmd) {
  ::add_history(cmd.c_str());
}

void mgt::refresh_prompt() {
  putchar('\n');
  rl_on_new_line(); // Regenerate the prompt on a newline
  rl_replace_line("", 0); // Clear the previous text
  rl_redisplay();
}
