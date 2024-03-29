#ifndef _ADHOCC_H_
#define _ADHOCC_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define error(...) {fprintf(stderr, __VA_ARGS__); exit(0);}
#define string_format(s, ...) snprintf(s->data, s->cap, __VA_ARGS__)

#ifndef NO_ADHOCC_SHORTNAME
  #define cstr(s) string_cstr(s)
  #define format(s, ...) string_format(s, __VA_ARGS__)
  #define pushs(s, p) string_pushs(s, p)
  #define pushc(s, c) string_pushc(s, c)
#endif

typedef struct {
  char* data;
  int len;
  int cap;
} string;

typedef struct {
  void** data;
  int len;
  int cap;
} vector;

// string.c
string* new_string_cap(int cap);
string* empty_string();
void string_extend(string* s, int len);
void string_pushs(string* s, char* p);
void string_pushc(string* s, char c);
string* new_string(char* p);
char* string_cstr(string* s);

// vector.c
vector* new_vector_cap(int cap);
vector* new_vector();
void* vector_get(vector* v, int index);
void vector_set(vector* v, int index, void* elem);
void vector_push(vector* v, void* elem);

void adhocc_trans();

#endif
