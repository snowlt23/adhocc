#include "string.c"
#include <assert.h>

int main() {
  string* s = empty_string();
  string_push(s, "Hello ");
  string_push(s, "Yukari ");
  string_push(s, "and ");
  string_push(s, "Maki!");
  assert(strcmp("Hello Yukari and Maki!", string_cstr(s)) == 0);

  string* s2 = new_string("AKARI");
  assert(strcmp("AKARI", string_cstr(s2)) == 0);

  string* s3 = empty_string();
  string_pushc(s3, '1');
  string_pushc(s3, '2');
  string_pushc(s3, '3');
  assert(strcmp("123", string_cstr(s3)) == 0);
}
