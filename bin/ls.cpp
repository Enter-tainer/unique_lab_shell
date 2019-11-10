//
// Created by mgt on 11/6/19.
//

#include <dirent.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

namespace mgt::bin {

std::string get_file_type(mode_t mode) {
  if (S_ISREG(mode))
    return "-";
  else if (S_ISDIR(mode))
    return "d";
  else if (S_ISCHR(mode))
    return "c";
  else if (S_ISBLK(mode))
    return "b";
  else if (S_ISFIFO(mode))
    return "p";
  else if (S_ISLNK(mode))
    return "l";
  else if (S_ISSOCK(mode))
    return "s";
}

std::string get_user_name(int uid) {
  struct passwd *res;
  if (!(res = getpwuid(uid)))
    return "***";
  else
    return res->pw_name;
}

std::string get_group_name(int gid) {
  struct group *res;
  if (!(res = getgrgid(gid)))
    return "***";
  else
    return res->gr_name;
}

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
      if (std::string(file->d_name) != "." && std::string(file->d_name) != "..")
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

void ll_file(const std::string &path, const std::string &filename) {
  struct stat res{};
  stat(path.c_str(), &res);
  std::string pem[] = {"---", "--x", "-w-", "-wx", "r--", "r-x", "rw-", "rwx"};
  std::string file_type = get_file_type(res.st_mode);
  unsigned int mask = 07;
  std::string file_pem[] = {pem[mask & res.st_mode],
                            pem[mask & (res.st_mode >> 3u)],
                            pem[mask & (res.st_mode >> 6u)]};
  std::string time_str = ::ctime(&res.st_ctim.tv_sec);
  time_str.pop_back();
  std::cout << file_type << file_pem[2] << file_pem[1] << file_pem[0] << ' '
            << std::setw(4) << res.st_nlink << ' ' << get_user_name(res.st_uid) << ' ' << get_group_name(res.st_gid)
            << ' '
            << std::setw(8) << res.st_size << ' '
            << time_str << ' ' << filename << std::endl;
}

void ll(const std::string &path) {
  DIR *dir = opendir(path.c_str());
  std::vector<std::string> res;
  if (dir == nullptr) {
    std::cout << path << std::endl;
  } else {
    dirent *file;
    while ((file = readdir(dir)) != nullptr) {
      if (std::string(file->d_name) != "." && std::string(file->d_name) != "..")
        ll_file(path + "/" + file->d_name, file->d_name);
    }
  }
  closedir(dir);
}

} // namespace mgt::bin

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
        std::cout << std::endl;
      }
    } else { // ls dir1, dir2 ...
      for (int i = 1; i < argc; ++i) {
        mgt::bin::ls(std::string(argv[i]));
        std::cout << std::endl;
      }
    }
  }
}