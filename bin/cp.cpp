//
// Created by mgt on 11/10/19.
//

#include <iostream>
#include <cstdio>

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cout << "Too few or too many arguments" << std::endl;
  } else {
    FILE* res = std::freopen(argv[1], "r", stdin);
    if (res == nullptr) {
      perror("cannot read");
      exit(1);
    }
    std::string dist = argv[2], from = argv[1];
    if (*from.rbegin() == '/')
      from.pop_back();
    if (*dist.rbegin() == '/')
      dist.pop_back();
    int del_count = 1 + from.find_last_of('/');
    from.erase(0, del_count);
    dist += std::string("/") + from;
    std::cout << dist << std::endl;
    res = std::freopen(dist.c_str(), "w", stdout);
    
    if (res == nullptr) {
      perror(("cannot write" + dist).c_str());
      exit(1);
    }
    char c;
    while ((c = std::getchar()) != EOF) {
      putchar(c);
    }
  }
}