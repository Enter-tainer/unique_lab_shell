//
// Created by mgt on 11/9/19.
//

#include <algorithm>
#include "eval.h"
#include "../shell/fork_and_exec.h"
#include "../system_call.h"

namespace mgt::parse {

void eval(const std::vector<std::shared_ptr<ast::Node>> &cmd) {
  bool sync = cmd.end() == std::find_if(cmd.begin(), cmd.end(), [](auto x) {
    return std::dynamic_pointer_cast<ast::BackgroundNode>(x);
  });
  basic_eval(cmd, sync);
}

void basic_eval(const std::vector<std::shared_ptr<ast::Node>> &cmd, bool sync) {
  int pipe_count = 0;
  for (auto &i : cmd) {
    if (std::dynamic_pointer_cast<ast::PipeNode>(i))
      ++pipe_count;
  }
  if (pipe_count == 0) {
    auto x = std::dynamic_pointer_cast<ast::CommandNode>(cmd[0]);
    if (x->redirectR) {
      int fd = sys_wrapped::open(x->redirectR->path.c_str(), O_WRONLY | O_CREAT, 0644);
      mgt::cmd::run(x->cmd, x->argv, STDIN_FILENO, fd, sync);
    } else if (x->redirectL) {
      int fd = sys_wrapped::open(x->redirectL->path.c_str(), O_RDONLY);
      mgt::cmd::run(x->cmd, x->argv, fd, STDOUT_FILENO, sync);
    } else {
      mgt::cmd::run(x->cmd, x->argv, STDIN_FILENO, STDOUT_FILENO, sync);
    }
    return;
  }
  std::vector<std::array<int, 2>> pipes(pipe_count);
  for (auto &i : pipes) {
    sys_wrapped::pipe(i.data());
  }
  for (int i = 0, j = 0; i < cmd.size(); ++i) {
    if (std::dynamic_pointer_cast<ast::PipeNode>(cmd[i])) {
      ++j;
      continue;
    } else if (std::dynamic_pointer_cast<ast::BackgroundNode>(cmd[i])) {
      continue;
    } else {
      auto x = std::dynamic_pointer_cast<ast::CommandNode>(cmd[i]);
      if (x->redirectR) {
        int fd = sys_wrapped::open(x->redirectR->path.c_str(), O_WRONLY | O_CREAT, 0644);
        mgt::cmd::run(x->cmd, x->argv, pipes[j - 1][0], fd, sync);
      } else if (x->redirectL) {
        int fd = sys_wrapped::open(x->redirectL->path.c_str(), O_RDONLY);
        mgt::cmd::run(x->cmd, x->argv, fd, pipes[0][1], sync);
      } else {
        if (j == 0) {
          mgt::cmd::run(x->cmd, x->argv, STDIN_FILENO, pipes[0][1], sync);
        } else if (j == pipe_count) {
          mgt::cmd::run(x->cmd, x->argv, pipes[j - 1][0], STDOUT_FILENO, sync);
        } else {
          mgt::cmd::run(x->cmd, x->argv, pipes[j - 1][0], pipes[j][1], sync);
        }
      }
    }
  }
}
} // namespace mgt::parse::eval