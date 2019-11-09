//
// Created by mgt on 11/5/19.
//

#include "fork_and_exec.h"
#include "../readline.h"
#include "../shell/cd.h"
#include "../shell/echo.h"
#include "../shell/exit.h"
#include "../shell/kill.h"
#include "../shell/pwd.h"

void mgt::cmd::run(const std::string &file_name, const std::vector<std::string> &argv,
                   int in_fd,
                   int out_fd) {
  std::vector<std::string> commands{
      "echo",
      "exit",
      "cd",
      "pwd",
      "kill"
  };
  enum CommandType {
    kEcho, kExit, kCd, kPwd, kKill
  };
  bool matched = false;
  CommandType cmd{kEcho};
  for (int i = 0; i < commands.size(); ++i) {
    if (commands[i] == file_name) {
      matched = true;
      cmd = CommandType(i);
    }
  }
  if (!matched) {
    run_external(file_name, argv, in_fd, out_fd);
  } else {
    pid_t pid = mgt::sys_wrapped::fork();
    if (pid == 0) {
      mgt::sys_wrapped::dup2(in_fd, STDIN_FILENO);
      mgt::sys_wrapped::dup2(out_fd, STDOUT_FILENO);
      if (in_fd != STDIN_FILENO)
        sys_wrapped::close(in_fd);
      if (out_fd != STDOUT_FILENO)
        sys_wrapped::close(out_fd);
      switch (cmd) { // NOLINT(hicpp-multiway-paths-covered)
        case kEcho: {
          std::string res;
          for (auto &i : argv)
            res += i;
          mgt::cmd::echo(res);
          break;
        }
        case kExit: {
          mgt::cmd::exit();
          break;
        }
        case kCd: {
          mgt::cmd::cd(argv[1]);
          break;
        }
        case kPwd: {
          mgt::cmd::pwd();
          break;
        }
        case kKill: {
          mgt::cmd::kill(argv[1]);
          break;
        }
      }
      ::exit(0);
    } else {
      int status;
      mgt::sys_wrapped::waitpid(pid, &status, 0);
      if (in_fd != STDIN_FILENO)
        sys_wrapped::close(in_fd);
      if (out_fd != STDOUT_FILENO)
        sys_wrapped::close(out_fd);
    }
  }
}

void mgt::cmd::run(const std::string &file_name, char *const *argv,
                   int in_fd,
                   int out_fd) {
  pid_t pid = mgt::sys_wrapped::fork();
  if (pid == 0) {
    mgt::sys_wrapped::dup2(in_fd, STDIN_FILENO);
    mgt::sys_wrapped::dup2(out_fd, STDOUT_FILENO);
    if (in_fd != STDIN_FILENO)
      sys_wrapped::close(in_fd);
    if (out_fd != STDOUT_FILENO)
      sys_wrapped::close(out_fd);
    mgt::sys_wrapped::execvp(file_name.c_str(), argv);
    ::exit(0);
  } else {
    int status;
    mgt::sys_wrapped::waitpid(pid, &status, 0);
  }
}

void mgt::cmd::run_external(const std::string &file_name, const std::vector<std::string> &argv, int in_fd, int out_fd) {
  pid_t pid = mgt::sys_wrapped::fork();
  if (pid == 0) {
    char **c_argv = new char *[argv.size() + 1];
    for (size_t i = 0; i < argv.size(); ++i)
      c_argv[i] = const_cast<char *>(argv[i].data());
    c_argv[argv.size()] = nullptr;
    mgt::sys_wrapped::dup2(in_fd, STDIN_FILENO);
    mgt::sys_wrapped::dup2(out_fd, STDOUT_FILENO);
    if (in_fd != STDIN_FILENO)
      sys_wrapped::close(in_fd);
    if (out_fd != STDOUT_FILENO)
      sys_wrapped::close(out_fd);
    mgt::sys_wrapped::execvp(file_name.c_str(), c_argv);
    delete[] c_argv;
    ::exit(0);
  } else {
    int status;
    mgt::sys_wrapped::waitpid(pid, &status, 0);
    if (in_fd != STDIN_FILENO)
      sys_wrapped::close(in_fd);
    if (out_fd != STDOUT_FILENO)
      sys_wrapped::close(out_fd);
  }
}
