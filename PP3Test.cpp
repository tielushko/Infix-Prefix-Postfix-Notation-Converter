/**************************************************************************************************/
// Test File for PP3
// Requires the Catch2 header file
// How to compile: g++ -std=c++17 -Wall -I$(CATCH_SINGLE_INCLUDE) (All cpp files)
// Example if Catch2 and source files are in this directory and at directory level: 
//    Example: g++ -std=c++17 -Wall *.cpp
// To see what tests were successful and failed, run your executable with the -s flag
//    Example: a.out -s
// A successful test should output: All tests passed (24 assertions in 1 test case)
/**************************************************************************************************/

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <string>

#include "NotationConverter.hpp"

TEST_CASE("Project 2 Test Cases for NotationConverter") {
  const std::string infix1 = "(A + B)";
  const std::string infix2 = "((X + B) * (Y - D))";
  const std::string infix3 = "(((A + B) / (X + Y)) - R)";

  const std::string prefix1 = "+ / * x y g h";
  const std::string prefix2 = "-    /  x  y  g"; // Multiple Spaces Between Letters and Operators
  const std::string prefix3 = "- / x y * a b";

  const std::string postfix1 = "X Y + A B + *";
  const std::string postfix2 = "V C +"; 
  const std::string postfix3 = "H W * R Q - /";

  NotationConverter nc;

  SECTION("Infix notation should convert to prefix notation") {
    REQUIRE_THAT(nc.infixToPrefix(infix1), Catch::Contains("+ A B"));// works and matches 100%
    REQUIRE_THAT(nc.infixToPrefix(infix2), Catch::Contains("* + X B - Y D")); //works and matches 100%
    REQUIRE_THAT(nc.infixToPrefix(infix3), Catch::Contains("- / + A B + X Y R")); //works and matches 100%
  }

  SECTION("Infix notation should convert to postfix notation") {
    REQUIRE_THAT(nc.infixToPostfix(infix1), Catch::Contains("A B +")); //tested and works - deleted last space
    REQUIRE_THAT(nc.infixToPostfix(infix2), Catch::Contains("X B + Y D - *")); // tested and works - deleted last space
    REQUIRE_THAT(nc.infixToPostfix(infix3), Catch::Contains("A B + X Y + / R -")); //tested and works - deleted last space
  }

  SECTION("Prefix notation should convert to postfix notation") {
    REQUIRE_THAT(nc.prefixToPostfix(prefix1), Catch::Contains("x y * g / h +")); //tested and works - deleted last space
    REQUIRE_THAT(nc.prefixToPostfix(prefix2), Catch::Contains("x y / g -")); // tested and works need to delete last space
    REQUIRE_THAT(nc.prefixToPostfix(prefix3), Catch::Contains("x y / a b * -")); // tested and works need to delete last space
  }

  SECTION("Prefix notation should convert to infix notation") {
    REQUIRE_THAT(nc.prefixToInfix(prefix1), Catch::Contains("(((x * y) / g) + h)")); //tested and works - no spaces left 
    REQUIRE_THAT(nc.prefixToInfix(prefix2), Catch::Contains("((x / y) - g)")); // tested and works - no spaces left 
    REQUIRE_THAT(nc.prefixToInfix(prefix3), Catch::Contains("((x / y) - (a * b))")); // tested and works - no spaces left
  }

  SECTION("Postfix notation should convert to infix notation") {
    REQUIRE_THAT(nc.postfixToInfix(postfix1), Catch::Contains("((X + Y) * (A + B))")); // tested and works - matches output 100%
    REQUIRE_THAT(nc.postfixToInfix(postfix2), Catch::Contains("(V + C)")); // tested and works - matches output 100%
    REQUIRE_THAT(nc.postfixToInfix(postfix3), Catch::Contains("((H * W) / (R - Q))")); // works! - matches output 100%
  }

  SECTION("Postfix notation should convert to prefix notation") {
    REQUIRE_THAT(nc.postfixToPrefix(postfix1), Catch::Contains("* + X Y + A B")); //tested works, need to modify beginning space - done. modified space
    REQUIRE_THAT(nc.postfixToPrefix(postfix2), Catch::Contains("+ V C")); // tested works. correct modified space!
    REQUIRE_THAT(nc.postfixToPrefix(postfix3), Catch::Contains("/ * H W - R Q")); // tested works. correct modified space
  }

  const std::string bad1 = "[A + B]";
  const std::string bad2 = "^ / x y * a b";
  const std::string bad3 = "H W \\ R Q - /";

  SECTION("Check for invalid characters") {
    REQUIRE_THROWS(nc.infixToPrefix(bad1));
    REQUIRE_THROWS(nc.infixToPostfix(bad2));
    REQUIRE_THROWS(nc.prefixToPostfix(bad3));
    REQUIRE_THROWS(nc.prefixToInfix(bad1)); // tested works
    REQUIRE_THROWS(nc.postfixToInfix(bad2));
    REQUIRE_THROWS(nc.postfixToPrefix(bad3));
  }
}