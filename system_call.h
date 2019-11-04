//
// Created by mgt on 11/3/19.
//

#ifndef UNIQUE_LAB_SHELL_SYSTEM_CALL_H
#define UNIQUE_LAB_SHELL_SYSTEM_CALL_H

#include <iostream>
#include <cstring>
#include <cerrno>
#include <cstdlib>

#include <unistd.h>
#include <signal.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>

namespace mgt {
namespace sys {
// this namespace re-wrap functions in sys folder
inline pid_t fork() {
  return ::fork();
}
inline pid_t waitpid(pid_t pid, int *status, int options) {
  return ::waitpid(pid, status, options);
}

inline pid_t wait(int *status) {
  return ::wait(status);
}
inline unsigned int sleep(unsigned int sec) {
  return ::sleep(sec);
}
inline int pause() {
  return ::pause();
}
inline int execve(const char *filename, char *const argv[], char *const envp[]) {
  return ::execve(filename, argv, envp);
}
inline int kill(pid_t pid, int sig) {
  return ::kill(pid, sig);
}

inline unsigned int alarm(unsigned int sec) {
  return ::alarm(sec);
}

inline sighandler_t signal(int sig, sighandler_t handle) {
  return ::signal(sig, handle);
}

inline int sigaction(int dig, const struct sigaction *__restrict act,
                     struct sigaction *__restrict old_act) {
  return ::sigaction(dig, act, old_act);
}

inline int chdir(const char *path) {
  return ::chdir(path);
}

} // namespace sys

namespace sys_wrapped {

// this namespace wrap sys calls with error handling
inline void unix_error(const char *msg) {
  std::cerr << msg << ": " << strerror(errno);
  exit(0);
}

inline pid_t fork() {
  pid_t pid;
  if ((pid = sys::fork()) < 0)
    unix_error("fork failed");
  return pid;
}

inline pid_t waitpid(pid_t pid, int *status, int options) {
  pid_t res;
  if ((res = sys::waitpid(pid, status, options)) < 0)
    unix_error("waitpid failed");
  return res;
}

inline pid_t wait(int *status) {
  pid_t pid;
  if ((pid = sys::wait(status)) < 0)
    unix_error("wait failed");
  return pid;
}

inline unsigned int sleep(unsigned int sec) {
  return sys::sleep(sec);
}

inline int pause() {
  int res;
  if ((res = sys::pause()) < 0)
    unix_error("pause failed");
  return res;
}

inline int execve(const char *filename, char *const argv[], char *const envp[]) {
  int res;
  if ((res = sys::execve(filename, argv, envp)) < 0)
    unix_error("execve failed");
  return res;
}

inline int kill(pid_t pid, int sig) {
  int res;
  if ((res = sys::kill(pid, sig)) < 0)
    unix_error("kill error");
  return res;
}

inline unsigned int alarm(unsigned int sec) {
  return sys::alarm(sec);
}

inline sighandler_t signal(int signum, sighandler_t handler) {
  struct sigaction action{}, old_action{};

  action.sa_handler = handler;
  sigemptyset(&action.sa_mask);
  action.sa_flags = SA_RESTART;

  if (sys::sigaction(signum, &action, &old_action) < 0)
    unix_error("Signal error");
  return old_action.sa_handler;
}

inline int chdir(const char *path) {
  int res;
  if ((res = sys::chdir(path)) < 0) {
    std::cout << strerror(errno) << std::endl;
  }
  return res;
}

} // namespace sys_wrapped
} // namespace mgt
#endif //UNIQUE_LAB_SHELL_SYSTEM_CALL_H
