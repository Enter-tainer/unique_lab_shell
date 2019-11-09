//
// Created by mgt on 11/6/19.
//

#include "../system_call.h"

#include <unistd.h>
#include <fcntl.h>
#include <string>

namespace mgt::bin {
void touch(const char *path) {
  int fd = sys_wrapped::open(path, O_RDWR | O_CREAT, 0644); // NOLINT(hicpp-signed-bitwise)
  sys_wrapped::close(fd);
}
} // namespace mgt::bin

int main(int argc, char **argv) {
  if (argc == 1) {
    std::cout << "Missing operands" << std::endl;
    return 1;
  }
  for (int i = 1; i < argc; ++i) {
    mgt::bin::touch(argv[i]);
  }
}