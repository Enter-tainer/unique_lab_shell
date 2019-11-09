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
    auto lc = std::dynamic_pointer_cast<ast::CommandNode>(x->lc),
        rc = std::dynamic_pointer_cast<ast::CommandNode>(x->rc);
    pid_t pid = sys_wrapped::fork();
    if (pid == 0) {
      eval_pipe(lc, rc);
    } else {
      int status;
      sys_wrapped::waitpid(pid, &status, 0);
    }
  }
}

void eval_pipe(std::shared_ptr<ast::CommandNode> l, std::shared_ptr<ast::CommandNode> r) {
  int fd[2];
  sys_wrapped::pipe(fd);
  int in = STDIN_FILENO, out = STDOUT_FILENO;
  if (r->redirectR) {
    out = sys_wrapped::open(r->redirectR->path.c_str(), O_CREAT | O_WRONLY, 0644);
  }
  if (l->redirectL) {
    in = sys_wrapped::open(l->redirectL->path.c_str(), O_RDONLY);
  }
  cmd::run(l->cmd, l->argv, in, fd[1]);
  cmd::run(r->cmd, r->argv, fd[0], out);
  ::exit(0);
}
}