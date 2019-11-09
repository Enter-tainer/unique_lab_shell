//
// Created by mgt on 11/7/19.
//

#ifndef UNIQUE_LAB_SHELL_TOKEN_H
#define UNIQUE_LAB_SHELL_TOKEN_H

#include <string>

namespace mgt::token {
class Token {
 public:
  std::string str;

  virtual ~Token() = default;
};

// data Token = Lit String | RedirectL | RedirectR | Pipe
class Lit : public Token {
 public:
  explicit Lit(const std::string &cmd) { str = cmd; };

  ~Lit() override = default;
};

class RedirectL : public Token {
 public:
  RedirectL() { str = "<"; }

  ~RedirectL() override = default;
};

class RedirectR : public Token {
 public:
  RedirectR() { str = ">"; }

  ~RedirectR() override = default;
};

class Pipe : public Token {
 public:
  Pipe() { str = "|"; }

  ~Pipe() override = default;
};
} // namespace mgt::token
#endif //UNIQUE_LAB_SHELL_TOKEN_H
