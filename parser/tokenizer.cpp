//
// Created by mgt on 11/7/19.
//

#include "tokenizer.h"

std::shared_ptr<mgt::token::Token> mgt::token::to_token(const std::string &str) {
  if (str == "|") {
    Pipe s;
    return std::static_pointer_cast<Token>(std::make_shared<Pipe>(s));
  } else if (str == ">") {
    RedirectR s;
    return std::static_pointer_cast<Token>(std::make_shared<RedirectR>(s));
  } else if (str == "<") {
    RedirectL s;
    return std::static_pointer_cast<Token>(std::make_shared<RedirectL>(s));
  } else if (str == "&") {
    Background s;
    return std::static_pointer_cast<Token>(std::make_shared<Background>(s));
  } else {
    Lit s(str);
    return std::static_pointer_cast<Token>(std::make_shared<Lit>(s));
  }
}

std::vector<std::shared_ptr<mgt::token::Token>> mgt::token::tokenize(const std::string &str) {
  auto v = mgt::str::split(str);
  std::vector<std::shared_ptr<Token>> res;
  for (auto &i : v) {
    res.emplace_back(to_token(i));
  }
  return res;
}
