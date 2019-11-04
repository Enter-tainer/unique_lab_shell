//
// Created by mgt on 11/4/19.
//

#include "repl.h"

namespace mgt {
void repl() {
  std::string line_input;
  while (true) {
    std::optional<std::string> res = mgt::readline(prompt);
    if (res.has_value())
      line_input = res.value();
    else
      break;
    mgt::add_history(line_input);
    process_input(line_input);
  }
}

void process_input(const std::string &input) {
  std::vector<std::string> commands{
    "echo",
    "exit",
    "cd",
    "pwd",
    "kill"
  };
  std::vector<int> cmp;
  enum {
    kEcho, kExit, kCd, kPwd, kKill
  };
  cmp.resize(commands.size());
  for (size_t i = 0; i < commands.size(); ++i)
    cmp[i] = input.find(commands[i]);

  for (size_t i = 0; i < cmp.size(); ++i) {
    if (cmp[i] == 0) {
      switch (i) { // NOLINT(hicpp-multiway-paths-covered)
        case kEcho: {
          mgt::cmd::echo(mgt::str::split_and_return_last(input));
          break;
        }
        case kExit: {
          break;
        }
        case kCd: {
          break;
        }
        case kPwd: {
          break;
        }
        case kKill: {
          break;
        }
      }
    }
  }
}
}