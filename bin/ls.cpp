//
// Created by mgt on 11/6/19.
//

#include <dirent.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

namespace mgt::bin {

std::pair<int, int> get_term_size() { // <row, col>
  winsize w{};
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  return {w.ws_row, 80};
}

void ls(const std::string &path) {
  DIR *dir = opendir(path.c_str());
  std::vector<std::string> res;
  if (dir == nullptr) {
    std::cout << path << std::endl;
  } else {
    dirent *file;
    while ((file = readdir(dir)) != nullptr) {
      res.emplace_back(file->d_name);
    }
  }
  closedir(dir);
  std::sort(res.begin(), res.end());
  int max_width = std::max_element(res.begin(), res.end(),
                                   [](const auto &a, const auto &b) { return a.length() < b.length(); })
      ->length();
  int col = get_term_size().second;
  int max_col_count = col / (max_width + 2);
  int width_of_each_col = max_width + 2;
  for (auto &i : res) {
    i += std::string(width_of_each_col - i.length(), ' ');
  }
  for (size_t i = 0; i < res.size(); ++i) {
    if ((i + 1) % max_col_count == 0)
      std::cout << std::endl;
    std::cout << res[i];
  }
}

void ll(const std::string &path) {

}
}

int main(int argc, char **argv) {
  if (argc == 1) { // ls .
    mgt::bin::ls(".");
  } else if (argc == 2) {
    if (!std::strcmp(argv[1], "-l")) { // ls -l .
      mgt::bin::ll(".");
    } else {
      std::string dir_name(argv[1]); // ls dirname
      mgt::bin::ls(std::string(dir_name));
    }
  } else { // argc > 2
    if (!std::strcmp(argv[1], "-l")) { // ls -l dir1 dir2 ...
      for (int i = 2; i < argc; ++i) {
        mgt::bin::ll(std::string(argv[i]));
      }
    } else { // ls dir1, dir2 ...
      for (int i = 1; i < argc; ++i) {
        mgt::bin::ls(std::string(argv[i]));
      }
    }
  }
}