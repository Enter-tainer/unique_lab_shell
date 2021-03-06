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
#include "export.h"

void
mgt::cmd::run(const std::string &file_name, const std::vector<std::string> &argv, int in_fd, int out_fd, bool sync) {
  std::vector<std::string> commands{
      "echo",
      "exit",
      "cd",
      "pwd",
      "kill",
      "export"
  };
  enum CommandType {
    kEcho, kExit, kCd, kPwd, kKill, kExport
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
    if (sync)
      run_external_sync(file_name, argv, in_fd, out_fd);
    else
      run_external_async(file_name, argv, in_fd, out_fd);
  } else {
    switch (cmd) { // NOLINT(hicpp-multiway-paths-covered)
      case kEcho: {
        pid_t pid = mgt::sys_wrapped::fork();
        if (pid == 0) {
          mgt::sys_wrapped::dup2(in_fd, STDIN_FILENO);
          mgt::sys_wrapped::dup2(out_fd, STDOUT_FILENO);
          if (in_fd != STDIN_FILENO)
            sys_wrapped::close(in_fd);
          if (out_fd != STDOUT_FILENO)
            sys_wrapped::close(out_fd);
          std::string res;
          for (int i = 1; i < argv.size(); ++i)
            res += argv[i];
          mgt::cmd::echo(res);
          ::exit(0);
        } else {
          int status;
          mgt::sys_wrapped::waitpid(pid, &status, 0);
          if (in_fd != STDIN_FILENO)
            sys_wrapped::close(in_fd);
          if (out_fd != STDOUT_FILENO)
            sys_wrapped::close(out_fd);
        }
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
      case kExport: {
        std::string name, value;
        auto x = mgt::str::split(argv[1], '=');
        name = x[0], value = x[1];
        mgt::cmd::export_env(name, value);
        break;
      }
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

void
mgt::cmd::run_external_sync(const std::string &file_name, const std::vector<std::string> &argv, int in_fd, int out_fd) {
  basic_run_external(file_name, argv, in_fd, out_fd, true);
}

void mgt::cmd::basic_run_external(const std::string &file_name, const std::vector<std::string> &argv, int in_fd,
                                  int out_fd, bool sync) {
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
    if (sync) {
      mgt::sys_wrapped::waitpid(pid, &status, 0);
    }
    if (in_fd != STDIN_FILENO)
      sys_wrapped::close(in_fd);
    if (out_fd != STDOUT_FILENO)
      sys_wrapped::close(out_fd);
  }
}

void mgt::cmd::run_external_async(const std::string &file_name, const std::vector<std::string> &argv, int in_fd,
                                  int out_fd) {
  basic_run_external(file_name, argv, in_fd, out_fd, false);
}
