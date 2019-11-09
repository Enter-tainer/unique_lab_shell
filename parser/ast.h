//
// Created by mgt on 11/9/19.
//

#ifndef UNIQUE_LAB_SHELL_AST_H
#define UNIQUE_LAB_SHELL_AST_H

#include "ast_node.h"
#include "eval.h"

namespace mgt::parse::ast {
class AST {
 private:
  std::shared_ptr <Node> root_;
 public:
  explicit AST(std::shared_ptr <Node> root) : root_(std::move(root)) {};

  void eval();
};
}
#endif //UNIQUE_LAB_SHELL_AST_H
