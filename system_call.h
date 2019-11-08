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
#include <fcntl.h>
#include <sys/stat.h>
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

inline int execvp(const char *file, char *const argv[]) {
  return ::execvp(file, argv);
}

inline int execvpe(const char *file, char *const argv[], char *const envp[]) {
  return ::execvpe(file, argv, envp);
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

inline int dup2(int old_fd, int new_fd) {
  return ::dup2(old_fd, new_fd);
}

inline int open(const char *pathname, int flags, mode_t mode) {
  return ::open(pathname, flags, mode);
}

inline int close(int fd) {
  return ::close(fd);
}

inline int mkdir(const char *path, mode_t mode) {
  return ::mkdir(path, mode);
}

inline ssize_t read(int fd, void *buf, size_t count) {
  return ::read(fd, buf, count);
}

inline ssize_t write(int fd, const void *buf, size_t count) {
  return ::write(fd, buf, count);
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
    unix_error("fork failed: ");
  return pid;
}

inline pid_t waitpid(pid_t pid, int *status, int options) {
  pid_t res;
  if ((res = sys::waitpid(pid, status, options)) < 0)
    unix_error("waitpid failed: ");
  return res;
}

inline pid_t wait(int *status) {
  pid_t pid;
  if ((pid = sys::wait(status)) < 0)
    unix_error("wait failed: ");
  return pid;
}

inline unsigned int sleep(unsigned int sec) {
  return sys::sleep(sec);
}

inline int pause() {
  int res;
  if ((res = sys::pause()) < 0)
    unix_error("pause failed: ");
  return res;
}

inline int execve(const char *filename, char *const argv[], char *const envp[]) {
  int res;
  if ((res = sys::execve(filename, argv, envp)) < 0)
    unix_error("execve failed: ");
  return res;
}

inline int execvp(const char *file, char *const argv[]) {
  int res;
  if ((res = sys::execvp(file, argv) < 0)) {
    unix_error("execvp failed: ");
  }
  return res;
}

inline int execvpe(const char *file, char *const argv[], char *const envp[]) {
  int res;
  if ((res = sys::execvpe(file, argv, envp) < 0)) {
    unix_error("execvpe failed: ");
  }
  return res;
}

inline int kill(pid_t pid, int sig) {
  int res;
  if ((res = sys::kill(pid, sig)) < 0)
    unix_error("kill error: ");
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
    unix_error("Signal error: ");
  return old_action.sa_handler;
}

inline int chdir(const char *path) {
  int res;
  if ((res = sys::chdir(path)) < 0) {
    std::cout << strerror(errno) << std::endl;
  }
  return res;
}

inline int dup2(int old_fd, int new_fd) {
  int res;
  if ((res = sys::dup2(old_fd, new_fd)) < 0)
    unix_error("dup2 failed: ");
  return res;
}

inline int open(const char *pathname, int flags, mode_t mode) {
  int res;
  if ((res = sys::open(pathname, flags, mode) < 0)) {
    unix_error("cannot open: ");
  }
  return res;
}

inline int close(int fd) {
  int res;
  if ((res = sys::close(fd))) {
    unix_error("cannot close: ");
  }
  return res;
}

inline int mkdir(const char *path, mode_t mode) {
  int res;
  if ((res = sys::mkdir(path, mode))) {
    unix_error("cannot mkdir: ");
  }
  return res;
}

inline ssize_t read(int fd, void *buf, size_t count) {
  ssize_t res;
  if ((res = sys::read(fd, buf, count) < 0)) {
    unix_error("cannot read: ");
  }
  return res;
}

inline ssize_t write(int fd, const void *buf, size_t count) {
  ssize_t res;
  if ((res = sys::write(fd, buf, count) < 0)) {
    unix_error("cannot write: ");
  }
  return res;
}

} // namespace sys_wrapped
} // namespace mgt
#endif //UNIQUE_LAB_SHELL_SYSTEM_CALL_H
