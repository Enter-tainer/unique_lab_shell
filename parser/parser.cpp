//
// Created by mgt on 11/7/19.
//

#include "parser.h"

std::shared_ptr<mgt::parse::ast::Node>
mgt::parse::parse(const std::vector<std::shared_ptr<mgt::token::Token>> &tokens, int l, int r) {
  // [l, r)
  bool has_pipe = tokens.begin() + r != std::find_if(tokens.begin() + l, tokens.begin() + r, [](auto ptr) {
    return std::dynamic_pointer_cast<token::Pipe>(ptr);
  });
  if (has_pipe) {
    for (int i = r - 1; i >= l; --i) {
      if (std::dynamic_pointer_cast<token::Pipe>(tokens[i])) {
        std::shared_ptr<ast::PipeNode> res = std::make_shared<ast::PipeNode>();
        res->lc = parse(tokens, l, i);
        res->rc = parse(tokens, i + 1, r);
        return std::static_pointer_cast<ast::Node>(res);
      }
    }
  } else {
    return std::static_pointer_cast<ast::Node>(parse_command(tokens, l, r));
  }
}

std::shared_ptr<mgt::parse::ast::CommandNode>
mgt::parse::parse_command(const std::vector<std::shared_ptr<mgt::token::Token>> &tokens, int l, int r) {
  bool has_redirectL = tokens.begin() + r != std::find_if(tokens.begin() + l, tokens.begin() + r, [](auto ptr) {
    return std::dynamic_pointer_cast<token::RedirectL>(ptr);
  });
  bool has_redirectR = tokens.begin() + r != std::find_if(tokens.begin() + l, tokens.begin() + r, [](auto ptr) {
    return std::dynamic_pointer_cast<token::RedirectR>(ptr);
  });
  int redirect_num = 0;
  if (has_redirectL)
    redirect_num += 2;
  if (has_redirectR)
    redirect_num += 2;
  std::shared_ptr<ast::CommandNode> res = std::make_shared<ast::CommandNode>();
  res->cmd = tokens[l]->str;
  std::vector<std::string> argv;
  for (int i = l; i < r - redirect_num; ++i) { // assume that <Command> <Args> <Redirect>
    argv.push_back(tokens[i]->str);
  }
  res->argv = argv;
  for (int i = l; i < r; ++i) {
    if (std::dynamic_pointer_cast<token::RedirectL>(tokens[i])) {
      std::shared_ptr<ast::RedirectLNode> redirect = std::make_shared<ast::RedirectLNode>();
      std::static_pointer_cast<ast::RedirectNode>(redirect)->path = tokens[i + 1]->str;
      res->redirectL = std::static_pointer_cast<ast::RedirectLNode>(redirect);
    } else if (std::dynamic_pointer_cast<token::RedirectR>(tokens[i])) {
      std::shared_ptr<ast::RedirectRNode> redirect = std::make_shared<ast::RedirectRNode>();
      std::static_pointer_cast<ast::RedirectNode>(redirect)->path = tokens[i + 1]->str;
      res->redirectR = std::static_pointer_cast<ast::RedirectRNode>(redirect);
    }
  }
  return res;
}

std::shared_ptr<mgt::parse::ast::Node>
mgt::parse::parse(const std::vector<std::shared_ptr<mgt::token::Token>> &tokens) {
  return parse(tokens, 0, tokens.size());
}
