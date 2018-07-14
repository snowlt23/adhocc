#ifndef _ADHOCC_H_
#define _ADHOCC_H_

#include <stdbool.h>

typedef struct {
  char* data;
  int len;
  int cap;
} string;

string* new_string_cap(int cap);
string* empty_string();
void string_extend(string* s, int len);
void string_push(string* s, char* p);
void string_pushc(string* s, char c);
string* new_string(char* p);
char* string_cstr(string* s);

void adhocc_trans();

#endif