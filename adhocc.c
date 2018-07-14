#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "adhocc.h"

#define ADHOCC_BEGIN void* adhocc_table[] = {
#define ADHOCC_HOOK(name, p) (void*)name, (void*)p,
#define ADHOCC_END };

void skip_spaces() {
  for (;;) {
    char c = getc(stdin);
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

void trans_enum() {
  skip_spaces();
  string* enumname = parse_ident();
  skip_spaces();
  if (getc(stdin) != '{') error("expected { token in %%%%enum");
  skip_spaces();

  string* enumsrc = empty_string();
  string* tostrsrc = empty_string();

  for (;;) {
    skip_spaces();
    char c = getc(stdin);
    if (c == '}') break;
    ungetc(c, stdin);

    string* kind = parse_ident();

    string_push(enumsrc, string_cstr(kind));
    string_push(enumsrc, ", ");

    string_push(tostrsrc, "if (kind == ");
    string_push(tostrsrc, string_cstr(kind));
    string_push(tostrsrc, ") return \"");
    string_push(tostrsrc, string_cstr(kind));
    string_push(tostrsrc, "\"; ");

    skip_spaces();
    c = getc(stdin);
    if (c == ',') continue;
    ungetc(c, stdin);
  }

  printf("typedef enum { %s } %s;\n", string_cstr(enumsrc), string_cstr(enumname));
  printf("char* %s_tostring(%s kind) { %s }\n", string_cstr(enumname), string_cstr(enumname), string_cstr(tostrsrc));
}

void trans_deadcode() {
  printf("0xDEADC0DE");
}

ADHOCC_BEGIN
ADHOCC_HOOK("enum", trans_enum)
ADHOCC_HOOK("deadcode", trans_deadcode)
ADHOCC_END

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
      printf("%c", c);
    }
  }
}

int main() {
  adhocc_trans();
}
