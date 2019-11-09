//
// Created by mgt on 11/9/19.
//

#ifndef UNIQUE_LAB_SHELL_EVAL_H
#define UNIQUE_LAB_SHELL_EVAL_H

#include "ast_node.h"

namespace mgt::parse::eval {
void eval(const std::shared_ptr<ast::Node> &root);

void eval_pipe(const std::shared_ptr<ast::CommandNode> &l, const std::shared_ptr<ast::CommandNode> &r);
} //namespace mgt::parse::eval
#endif //UNIQUE_LAB_SHELL_EVAL_H
