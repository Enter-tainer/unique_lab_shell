//
// Created by mgt on 11/9/19.
//

#include "eval.h"
#include "../shell/fork_and_exec.h"
#include "../system_call.h"

namespace mgt::parse::eval {

void eval(std::shared_ptr<ast::Node> root) {
  if (std::dynamic_pointer_cast<ast::CommandNode>(root)) {
    auto x = std::dynamic_pointer_cast<ast::CommandNode>(root);
    int in = STDIN_FILENO, out = STDOUT_FILENO;
    if (x->redirectL) {
      in = sys_wrapped::open(x->redirectL->path.c_str(), O_RDONLY);
    }
    if (x->redirectR) {
      out = sys_wrapped::open(x->redirectR->path.c_str(), O_CREAT | O_WRONLY, 0644);
    }
    mgt::cmd::run(x->cmd, x->argv, in, out);
  } else if (std::dynamic_pointer_cast<ast::PipeNode>(root)) {
    auto x = std::dynamic_pointer_cast<ast::PipeNode>(root);
    // assume that only one pipe operator
    int fd[2];
    sys_wrapped::pipe(fd);
    auto lc = std::dynamic_pointer_cast<ast::CommandNode>(x->lc),
        rc = std::dynamic_pointer_cast<ast::CommandNode>(x->rc);
  }
}

void eval_pipe(std::shared_ptr<ast::PipeNode> pipe, int write_end) {

}
}