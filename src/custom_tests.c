#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "asserts.h"
// Necessary due to static functions in state.c
#include "state.c"

/* Look at asserts.c for some helpful assert functions */

int greater_than_forty_two(int x) { return x > 42; }

bool is_vowel(char c) {
  char *vowels = "aeiouAEIOU";
  for (int i = 0; i < strlen(vowels); i++) {
    if (c == vowels[i]) {
      return true;
    }
  }
  return false;
}

/*
  Example 1: Returns true if all test cases pass. False otherwise.
    The function greater_than_forty_two(int x) will return true if x > 42. False otherwise.
    Note: This test is NOT comprehensive
*/
bool test_greater_than_forty_two() {
  int testcase_1 = 42;
  bool output_1 = greater_than_forty_two(testcase_1);
  if (!assert_false("output_1", output_1)) {
    return false;
  }

  int testcase_2 = -42;
  bool output_2 = greater_than_forty_two(testcase_2);
  if (!assert_false("output_2", output_2)) {
    return false;
  }

  int testcase_3 = 4242;
  bool output_3 = greater_than_forty_two(testcase_3);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  return true;
}

/*
  Example 2: Returns true if all test cases pass. False otherwise.
    The function is_vowel(char c) will return true if c is a vowel (i.e. c is a,e,i,o,u)
    and returns false otherwise
    Note: This test is NOT comprehensive
*/
bool test_is_vowel() {
  char testcase_1 = 'a';
  bool output_1 = is_vowel(testcase_1);
  if (!assert_true("output_1", output_1)) {
    return false;
  }

  char testcase_2 = 'e';
  bool output_2 = is_vowel(testcase_2);
  if (!assert_true("output_2", output_2)) {
    return false;
  }

  char testcase_3 = 'i';
  bool output_3 = is_vowel(testcase_3);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  char testcase_4 = 'o';
  bool output_4 = is_vowel(testcase_4);
  if (!assert_true("output_4", output_4)) {
    return false;
  }

  char testcase_5 = 'u';
  bool output_5 = is_vowel(testcase_5);
  if (!assert_true("output_5", output_5)) {
    return false;
  }

  char testcase_6 = 'k';
  bool output_6 = is_vowel(testcase_6);
  if (!assert_false("output_6", output_6)) {
    return false;
  }

  return true;
}

/* Task 4.1 */

bool test_is_tail() {
  // TODO: Implement this function.
  char testcase_1 = 'w';
  bool output_1 = is_tail(testcase_1);
  if (!assert_true("output_1", output_1)) {
    return false;
  }

  char testcase_2 = 'a';
  bool output_2 = is_tail(testcase_2);
  if (!assert_true("output_2", output_2)) {
    return false;
  }

  char testcase_3 = 's';
  bool output_3 = is_tail(testcase_3);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  char testcase_4 = 'd';
  bool output_4 = is_tail(testcase_4);
  if (!assert_true("output_4", output_4)) {
    return false;
  }

  char testcase_5 = 'l';
  bool output_5 = is_tail(testcase_5);
  if (!assert_false("output_5", output_5)) {
    return false;
  }

  char testcase_6 = '?';
  bool output_6 = is_tail(testcase_6);
  if (!assert_false("output_6", output_6)) {
    return false;
  }

  char testcase_7 = '1';
  bool output_7 = is_tail(testcase_7);
  if (!assert_false("output_7", output_7)) {
    return false;
  }

  printf("test_is_tail all passed\n");

  return true;
}

bool test_is_head() {
  // TODO: Implement this function.
  char testcase_1 = 'W';
  bool output_1 = is_head(testcase_1);
  if (!assert_true("output_1", output_1)) {
    return false;
  }

  char testcase_2 = 'A';
  bool output_2 = is_head(testcase_2);
  if (!assert_true("output_2", output_2)) {
    return false;
  }

  char testcase_3 = 'S';
  bool output_3 = is_head(testcase_3);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  char testcase_4 = 'D';
  bool output_4 = is_head(testcase_4);
  if (!assert_true("output_4", output_4)) {
    return false;
  }

  char testcase_5 = 'l';
  bool output_5 = is_head(testcase_5);
  if (!assert_false("output_5", output_5)) {
    return false;
  }

  char testcase_6 = '?';
  bool output_6 = is_head(testcase_6);
  if (!assert_false("output_6", output_6)) {
    return false;
  }

  char testcase_7 = '1';
  bool output_7 = is_head(testcase_7);
  if (!assert_false("output_7", output_7)) {
    return false;
  }

  printf("test_is_head all passed\n");

  return true;
}

bool test_is_snake() {
  // TODO: Implement this function.
  const char snake_chars[] = "wasd^<v>WASDx";
  for (int i = 0; snake_chars[i] != '\0'; i++) {
    char test_case = snake_chars[i];
    bool output1 = is_snake(test_case);
    if (!assert_true("output1", output1)) {
      return false;
    }
  }

  const char not_snake_chars[] = "123?-=+lkj";
  for (int i = 0; not_snake_chars[i] != '\0'; i++) {
    char test_case_2 = not_snake_chars[i];
    bool output2 = is_snake(test_case_2);
    if (!assert_false("output2", output2)) {
      return false;
    }
  }

  printf("test_is_snake all passed\n");

  return true;
}

bool test_body_to_tail() {
  // TODO: Implement this function.
  const char body[] = "^<v>";
  const char tail[] = "wasd";
  for (int i = 0; body[i] != '\0'; i++) {
    char test_case = body[i];
    char output = body_to_tail(test_case);
    if (!assert_equals_char("output", tail[i], output)) {
      return false;
    }
  }

  const char not_body[] = "123wasdWASD-=;";
  const char not_tail = '?';
  for (int i = 0; not_body[i] != '\0'; i++) {
    char test_case_2 = not_body[i];
    char output2 = body_to_tail(test_case_2);
    if (!assert_equals_char("output2", not_tail, output2)) {
      return false;
    }
  }

  printf("test_body_to_tail all passed\n");

  return true;
}

bool test_head_to_body() {
  // TODO: Implement this function.
  const char body[] = "^<v>";
  const char head[] = "WASD";
  for (int i = 0; body[i] != '\0'; i++) {
    char test_case = head[i];
    char output = head_to_body(test_case);
    if (!assert_equals_char("output", body[i], output)) {
      return false;
    }
  }

  // Test cases for invalid inputs
  const char not_head[] = "123wasd-=;";
  const char not_body = '?';
  for (int i = 0; not_head[i] != '\0'; i++) {
    char test_case_2 = not_head[i];
    char output2 = head_to_body(test_case_2);
    if (!assert_equals_char("output2", not_body, output2)) {
      return false;
    }
  }

  printf("test_head_to_body all passed\n");

  return true;
}

bool test_get_next_row() {
  // TODO: Implement this function.
  unsigned int current_row = 10;

  // 测试 'v', 's', 'S'
  if (!assert_equals_unsigned_int("get_next_row('v')", current_row + 1, get_next_row(current_row, 'v'))) {
    return false;
  }
  if (!assert_equals_unsigned_int("get_next_row('s')", current_row + 1, get_next_row(current_row, 's'))) {
    return false;
  }
  if (!assert_equals_unsigned_int("get_next_row('S')", current_row + 1, get_next_row(current_row, 'S'))) {
    return false;
  }

  // 测试 '^', 'w', 'W'
  if (!assert_equals_unsigned_int("get_next_row('^')", current_row - 1, get_next_row(current_row, '^'))) {
    return false;
  }
  if (!assert_equals_unsigned_int("get_next_row('w')", current_row - 1, get_next_row(current_row, 'w'))) {
    return false;
  }
  if (!assert_equals_unsigned_int("get_next_row('W')", current_row - 1, get_next_row(current_row, 'W'))) {
    return false;
  }

  // 测试其他字符
  if (!assert_equals_unsigned_int("get_next_row('x')", current_row, get_next_row(current_row, 'x'))) {
    return false;
  }

  printf("test_get_next_row all passed\n");

  return true;
}

bool test_get_next_col() {
  // TODO: Implement this function.
   unsigned int current_column = 20;

  // 测试 '>', 'd', 'D'
  if (!assert_equals_unsigned_int("get_next_col('>')", current_column + 1, get_next_col(current_column, '>'))) {
    return false;
  }
  if (!assert_equals_unsigned_int("get_next_col('d')", current_column + 1, get_next_col(current_column, 'd'))) {
    return false;
  }
  if (!assert_equals_unsigned_int("get_next_col('D')", current_column + 1, get_next_col(current_column, 'D'))) {
    return false;
  }

  // 测试 '<', 'a', 'A'
  if (!assert_equals_unsigned_int("get_next_col('<')", current_column - 1, get_next_col(current_column, '<'))) {
    return false;
  }
  if (!assert_equals_unsigned_int("get_next_col('a')", current_column - 1, get_next_col(current_column, 'a'))) {
    return false;
  }
  if (!assert_equals_unsigned_int("get_next_col('A')", current_column - 1, get_next_col(current_column, 'A'))) {
    return false;
  }

  // 测试其他字符
  if (!assert_equals_unsigned_int("get_next_col('z')", current_column, get_next_col(current_column, 'z'))) {
    return false;
  }

printf("test_get_next_col all passed\n");

  return true;
}

bool test_customs() {
  if (!test_greater_than_forty_two()) {
    printf("%s\n", "test_greater_than_forty_two failed.");
    return false;
  }
  if (!test_is_vowel()) {
    printf("%s\n", "test_is_vowel failed.");
    return false;
  }
  if (!test_is_tail()) {
    printf("%s\n", "test_is_tail failed");
    return false;
  }
  if (!test_is_head()) {
    printf("%s\n", "test_is_head failed");
    return false;
  }
  if (!test_is_snake()) {
    printf("%s\n", "test_is_snake failed");
    return false;
  }
  if (!test_body_to_tail()) {
    printf("%s\n", "test_body_to_tail failed");
    return false;
  }
  if (!test_head_to_body()) {
    printf("%s\n", "test_head_to_body failed");
    return false;
  }
  if (!test_get_next_row()) {
    printf("%s\n", "test_get_next_row failed");
    return false;
  }
  if (!test_get_next_col()) {
    printf("%s\n", "test_get_next_col failed");
    return false;
  }
  return true;
}

int main(int argc, char *argv[]) {
  init_colors();

  if (!test_and_print("custom", test_customs)) {
    return 0;
  }

  return 0;
}
