//
// Created by mgt on 11/4/19.
//

#ifndef UNIQUE_LAB_SHELL_STRING_OPT_H
#define UNIQUE_LAB_SHELL_STRING_OPT_H

#include <string>
#include <vector>

namespace mgt::str {
inline std::string trim_init(const std::string &str, char ch) {
  std::string res;
  res.reserve(str.length());
  bool first = true;
  for (auto i : str) {
    if (first && i == ch) {
      continue;
    } else {
      first = false;
      res.push_back(i);
    }
  }
  return res;
}

inline std::string trim_init(const std::string &str) {
  return trim_init(str, ' ');
}

inline std::string trim_last(const std::string &str, char ch) {
  std::string res = str;
  for (int i = static_cast<int>(res.size()) - 1; i >= 0; --i) {
    if (res[i] == ch) {
      res.pop_back();
    } else {
      break;
    }
  }
  return res;
}

inline std::string trim_last(const std::string &str) {
  return trim_last(str, ' ');
}

inline std::string trim(const std::string &str, char ch) {
  return trim_init(trim_last(str, ch), ch);
}

inline std::string trim(const std::string &str) {
  return trim(str, ' ');
}

inline std::string split_and_return_last(const std::string &str, char ch) {
  size_t res = str.find(ch);
  if (res == std::string::npos)
    return "";
  else
    return trim(str.substr(res));
}

inline std::string split_and_return_last(const std::string &str) {
  return split_and_return_last(str, ' ');
}

inline std::vector<std::string> split(const std::string &str, char ch) {
  std::stringstream ss(str);
  std::vector<std::string> elem;
  std::string item;
  while (std::getline(ss, item, ch)) {
    if (item.length() > 0) {
      elem.push_back(item);
    }
  }
  return elem;
}

inline std::vector<std::string> split(const std::string &str) {
  return split(str, ' ');
}

}
#endif //UNIQUE_LAB_SHELL_STRING_OPT_H
