//
// Created by mgt on 11/10/19.
//

#include <iostream>
#include <cstdio>
#include <string>

#include "../system_call.h"

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cout << "Too few or too many arguments" << std::endl;
  } else {
    std::freopen(argv[1], "r", stdin);
    std::freopen(argv[2], "w", stdout);
    char c;
    while ((c = std::getchar()) != EOF) {
      putchar(c);
    }
  }
}