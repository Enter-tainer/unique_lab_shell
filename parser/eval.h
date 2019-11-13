//
// Created by mgt on 11/9/19.
//

#ifndef UNIQUE_LAB_SHELL_EVAL_H
#define UNIQUE_LAB_SHELL_EVAL_H

#include "ast_node.h"

namespace mgt::parse {
void eval(const std::vector<std::shared_ptr<ast::Node>> &cmd);

void basic_eval(const std::vector<std::shared_ptr<ast::Node>> &cmd, bool sync);
} //namespace mgt::parse::eval
#endif //UNIQUE_LAB_SHELL_EVAL_H
