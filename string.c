#include <stdlib.h>
#include <string.h>
#include "adhocc.h"

string* new_string_cap(int cap) {
  string* s = malloc(sizeof(string));
  s->data = malloc((cap+1)*sizeof(char));
  memset(s->data, 0, (cap+1)*sizeof(char));
  s->len = 0;
  s->cap = cap;
  return s;
}

string* empty_string() {
  return new_string_cap(256);
}

void string_extend(string* s, int len) {
  if (s->len+len > s->cap) {
    while (s->len+len > s->cap) s->cap *= 2;
    s->data = realloc(s->data, (s->cap+1) * sizeof(char));
  }
}

void string_pushs(string* s, char* p) {
  string_extend(s, strlen(p));
  strcpy(s->data + s->len, p);
  s->len += strlen(p);
}

void string_pushc(string* s, char c) {
  string_extend(s, 1);
  *(s->data + s->len) = c;
  *(s->data + s->len+1) = '\0';
  s->len += 1;
}

string* new_string(char* p) {
  string* s = empty_string();
  string_pushs(s, p);
  return s;
}

char* string_cstr(string* s) {
  return s->data;
}
