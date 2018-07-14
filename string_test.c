#include "string.c"
#include <assert.h>

int main() {
  string* s = empty_string();
  string_pushs(s, "Hello ");
  string_pushs(s, "Yukari ");
  string_pushs(s, "and ");
  string_pushs(s, "Maki!");
  assert(strcmp("Hello Yukari and Maki!", string_cstr(s)) == 0);

  string* s2 = new_string("AKARI");
  assert(strcmp("AKARI", string_cstr(s2)) == 0);

  string* s3 = empty_string();
  string_pushc(s3, '1');
  string_pushc(s3, '2');
  string_pushc(s3, '3');
  assert(strcmp("123", string_cstr(s3)) == 0);
}
