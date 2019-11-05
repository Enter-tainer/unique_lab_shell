#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-narrowing-conversions"
//
// Created by mgt on 11/5/19.
//

#include <cstdio>

int main(int argc, char **argv) {
  for (int i = 1; i < argc; ++i) {
    std::freopen(argv[i], "r", stdin);
    char c;
    while ((c = getchar()) != EOF) {
      putchar(c);
    }
  }
}