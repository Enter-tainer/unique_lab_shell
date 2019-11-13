//
// Created by mgt on 11/12/19.
//
#include <iostream>
#include <vector>
#include "../system_call.h"
#include "util.h"

const int height = 24 - 1, width = 80;

void set_echo(int fd, bool enable) {
  const unsigned int flags = ECHO | ICANON;
  termios term{};
  mgt::sys_wrapped::tcgetattr(fd, &term);
  if (enable)
    term.c_lflag |= flags;
  else
    term.c_lflag &= ~flags;
  mgt::sys_wrapped::tcsetattr(fd, TCSAFLUSH, &term);
}

void disable_echo(int fd) {
  set_echo(fd, false);
}

void enable_echo(int fd) {
  set_echo(fd, true);
}

void refresh_screen() {
  mgt::sys_wrapped::write(STDOUT_FILENO, "\x1b[2J", 4);
  mgt::sys_wrapped::write(STDOUT_FILENO, "\x1b[H", 3);
}

int print_line(int fd, int pos) {
  // (pos, next'\n']
  ++pos;
  mgt::sys_wrapped::lseek(fd, pos, SEEK_SET);
  char c;
  int cnt;
  for (cnt = 0; (c = mgt::bin::getchar(fd)) != '\n' && c != EOF; ++cnt) {
    mgt::bin::putchar(STDOUT_FILENO, c);
  }
  if (c != EOF) {
    mgt::bin::putchar(STDOUT_FILENO, c);
    ++cnt;
  }
  return cnt;
}

int up_1_page(int fd, int *line_count, const std::vector<int> &newline_pos) {
  refresh_screen();
  if (*line_count < height) {
    int i = 0;
    for (i = 0; i < std::min(height, (int) newline_pos.size()); ++i) {
      print_line(fd, newline_pos[i]);
    }
    *line_count = 0;
    return i - 1;
  } else {
    int i, lc = *line_count;
    for (i = lc - height; i < lc; ++i) {
      print_line(fd, newline_pos[i]);
    }
    return i - 1;
  }
}

int down_1_page(int fd, int *line_count, int *char_count, std::vector<int> *newline_pos) {
  int i = 0;
  if (newline_pos->size() == 1 || *line_count >= newline_pos->size() - 1) {
    for (i = 0; i < height; ++i) {
      int cnt = print_line(fd, *char_count);
      if (cnt == 0)
        break;
      *char_count += cnt;
      newline_pos->push_back(*char_count);
      ++(*line_count);
    }
  } else {
    int lc = *line_count;
    for (i = lc; i < std::min(lc + height, (int) newline_pos->size() - 1); ++i) {
      int cnt = print_line(fd, (*newline_pos)[i]);
      if (cnt == 0)
        break;
      ++(*line_count);
    }
  }
  return i;
}


int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "Fatal error" << std::endl;
    ::exit(0);
  } else {
    int fd = mgt::sys_wrapped::open(argv[1], O_RDONLY);
    std::vector<int> newline_pos{-1}; // records the index of '\n's
    int char_count = -1, line_count = 0;
    down_1_page(fd, &line_count, &char_count, &newline_pos);
    if (newline_pos.size() < height) {
      ::exit(0);
    }
    line_count = height;
    disable_echo(STDIN_FILENO);
    while (true) {
      char c = mgt::bin::getchar(STDIN_FILENO);
      if (c == 'j' || c == '\n') {
        int res = down_1_page(fd, &line_count, &char_count, &newline_pos);
        if (res < height) {
          break;
        }
      } else if (c == 'k' || c == ' ') {
        line_count -= height;
        up_1_page(fd, &line_count, newline_pos);
      } else if (c == 'q') {
        break;
      }
    }
    enable_echo(STDIN_FILENO);
  }
}