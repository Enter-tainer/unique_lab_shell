//
// Created by mgt on 11/7/19.
//

#ifndef UNIQUE_LAB_SHELL_AST_NODE_H
#define UNIQUE_LAB_SHELL_AST_NODE_H

#include <string>
#include <memory>
#include <utility>
#include <vector>
#include "token.h"

namespace mgt::parse::ast {
class Node {
 public:
  virtual ~Node() = default;
};

class RedirectNode : public Node {
 public:
  ~RedirectNode() override = default;

  std::string path;
};

class RedirectRNode : public RedirectNode {
 public:
  ~RedirectRNode() override = default;
};

class RedirectLNode : public RedirectNode {
 public:
  ~RedirectLNode() override = default;
};

class CommandNode : public Node {
 public:
  ~CommandNode() override = default;

  std::string cmd;
  std::vector<std::string> argv;
  std::shared_ptr<RedirectLNode> redirectL;
  std::shared_ptr<RedirectRNode> redirectR;
};

class PipeNode : public Node {
 public:
  ~PipeNode() override = default;

  std::shared_ptr<Node> lc, rc;
};

} // namespace mgt::parse::ast


#endif //UNIQUE_LAB_SHELL_AST_NODE_H
