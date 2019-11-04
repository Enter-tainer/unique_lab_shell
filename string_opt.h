//
// Created by mgt on 11/4/19.
//

#ifndef UNIQUE_LAB_SHELL_STRING_OPT_H
#define UNIQUE_LAB_SHELL_STRING_OPT_H
#include <string>
namespace mgt::str {
std::string trim_init(const std::string &str, char ch) {
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

std::string trim_init(const std::string &str) {
  return trim_init(str, ' ');
}

std::string trim_last(const std::string &str, char ch) {
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

std::string trim_last(const std::string &str) {
  return trim_last(str, ' ');
}

std::string trim(const std::string &str, char ch) {
  return trim_init(trim_last(str, ch), ch);
}

std::string trim(const std::string &str) {
  return trim(str, ' ');
}

}
#endif //UNIQUE_LAB_SHELL_STRING_OPT_H
