//
// Created by mgt on 11/4/19.
//
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <string>

#include "../string_opt.h"

TEST_CASE("trim init") {
  SECTION("normal") {
    REQUIRE(std::string("123") == mgt::str::trim_init("  123"));
    REQUIRE(std::string("123") == mgt::str::trim_init(" 123"));
    REQUIRE(std::string("addr123") == mgt::str::trim_init("daddr123", 'd'));
  }
  SECTION("corner cases") {
    REQUIRE(std::string("") == mgt::str::trim_init(""));
    REQUIRE(std::string("") == mgt::str::trim_init(" "));
    REQUIRE(std::string("") == mgt::str::trim_init("   "));
  }
}

TEST_CASE("trim last") {
  SECTION("normal") {
    REQUIRE(std::string("123") == mgt::str::trim_last("123  "));
    REQUIRE(std::string("123") == mgt::str::trim_last("123   "));
    REQUIRE(std::string("addr12") == mgt::str::trim_last("addr1233333", '3'));
  }
  SECTION("corner cases") {
    REQUIRE(std::string("") == mgt::str::trim_last(""));
    REQUIRE(std::string("") == mgt::str::trim_last(" "));
    REQUIRE(std::string("") == mgt::str::trim_last("   "));
  }
}

TEST_CASE("trim") {
  REQUIRE(std::string("") == mgt::str::trim("  "));
  REQUIRE(std::string("221") == mgt::str::trim("  221 "));
}

TEST_CASE("split") {
  REQUIRE(std::string("qwq qwq") == mgt::str::split_and_return_last("echo qwq qwq "));
  REQUIRE(std::string("") == mgt::str::split_and_return_last("cd"));
  REQUIRE(std::vector<std::string>{"ls", "-l", "qwq", "eoe"} == mgt::str::split("ls -l qwq eoe"));
  REQUIRE(std::vector<std::string>{"", "f", "fg", "h", "g"} == mgt::str::split(" f fg h g "));
  REQUIRE(std::vector<std::string>{"ls"} == mgt::str::split("ls"));
}