//
// Created by mgt on 11/7/19.
//

#ifndef UNIQUE_LAB_SHELL_PARSER_H
#define UNIQUE_LAB_SHELL_PARSER_H

#include "token.h"
#include "ast.h"
#include <algorithm>

namespace mgt::parse {
std::shared_ptr<ast::Node> parse(const std::vector<std::shared_ptr<mgt::token::Token>> &tokens, int l, int r);

std::shared_ptr<ast::Node> parse(const std::vector<std::shared_ptr<mgt::token::Token>> &tokens);

std::shared_ptr<ast::CommandNode>
parse_command(const std::vector<std::shared_ptr<mgt::token::Token>> &tokens, int l, int r);
}
#endif //UNIQUE_LAB_SHELL_PARSER_H
