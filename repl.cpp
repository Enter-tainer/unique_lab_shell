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
  bool matched = false;
  for (size_t i = 0; i < cmp.size(); ++i) {
    if (cmp[i] == 0) {
      switch (i) { // NOLINT(hicpp-multiway-paths-covered)
        case kEcho: {
          mgt::cmd::echo(mgt::str::split_and_return_last(input));
          matched = true;
          break;
        }
        case kExit: {
          mgt::cmd::exit();
          matched = true;
          break;
        }
        case kCd: {
          mgt::cmd::cd(mgt::str::split_and_return_last(input));
          matched = true;
          break;
        }
        case kPwd: {
          mgt::cmd::pwd();
          matched = true;
          break;
        }
        case kKill: {
          mgt::cmd::kill(mgt::str::split_and_return_last(input));
          matched = true;
          break;
        }
      }
    }
  }
  if (!matched && !input.empty()) {
    // run external command
    std::vector<std::string> argv = mgt::str::split(input);
    mgt::cmd::run(input, argv);
  }
}
}