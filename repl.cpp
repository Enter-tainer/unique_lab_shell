//
// Created by mgt on 11/4/19.
//

#include "repl.h"
#include "parser/parser.h"
#include "parser/ast_node.h"
#include "readline.h"
#include "parser/eval.h"

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
  if (input.empty())
    return;
  auto x = mgt::parse::parse(input);
  mgt::parse::eval(x);
}
}