#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "adhocc.h"

#define ADHOCC_BEGIN void* adhocc_table[] = {
#define ADHOCC_HOOK(name, p) (void*)name, (void*)p,
#define ADHOCC_END };
#define ADHOCC_DEF(name, body) void name() { adhocc_prologue(); body; adhocc_epilogue(); }

int gLine = 1;

void skip_spaces() {
  for (;;) {
    char c = getc(stdin);
    if (c == '\n') {
      gLine++;
      continue;
    }
    if (c == '\r' || c == '\n' || c == ' ' || c == '\t') continue;
    ungetc(c, stdin);
    break;
  }
}

string* parse_ident() {
  string* s = empty_string();
  for (;;) {
    char c = getc(stdin);
    if (!isalpha(c) && c != '_') {
      ungetc(c, stdin);
      break;
    }
    string_pushc(s, c);
  }
  return s;
}

void adhocc_prologue() {}
void adhocc_epilogue() {
  printf("\n#line %d\n", gLine-1);
}

#include "adhocc_default.c"

void* search_table(char* key) {
  for (int i=0; i<sizeof(adhocc_table)/sizeof(void*); i+=2) {
    char* name = adhocc_table[i];
    void* funcp = adhocc_table[i+1];
    if (strcmp(name, key) == 0) {
      return funcp;
    }
  }
  return NULL;
}

void adhocc_trans() {
  for (;;) {
    char c = getc(stdin);
    if (c == EOF) break;
    if (c == '%') {
      c = getc(stdin);
      if (c == EOF) break;
      if (c == '%') { // goto adhocc
        char strbuf[256] = {};
        for (int i=0; ; i++) {
          c = getc(stdin);
          if (c == EOF || c == ' ' || c == '\n') {
            ungetc(c, stdin);
            break;
          }
          strbuf[i] = c;
        }
        void* funcp = search_table(strbuf);
        if (funcp != NULL) {
          ((void (*)())funcp)(); // execute hook function.
        }
      } else {
        printf("%%");
        ungetc(c, stdin);
      }
    } else {
      if (c == '\n') gLine++;
      printf("%c", c);
    }
  }
}

int main() {
  adhocc_trans();
}
