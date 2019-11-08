//
// Created by mgt on 11/7/19.
//

#ifndef UNIQUE_LAB_SHELL_TOKENIZER_H
#define UNIQUE_LAB_SHELL_TOKENIZER_H

#include "token.h"
#include "../string_opt.h"

#include <vector>
#include <string>
#include <memory>

namespace mgt::token {

std::shared_ptr<Token> to_token(const std::string &str);

std::vector<std::shared_ptr<Token>> tokenize(const std::string &str);
}
#endif //UNIQUE_LAB_SHELL_TOKENIZER_H
