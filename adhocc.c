#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "adhocc.h"

#define ADHOCC_BEGIN void* adhocc_table[] = {
#define ADHOCC_HOOK(name, p) (void*)name, (void*)p,
#define ADHOCC_END };
#define ADHOCC_DEF(name, body) void name() { adhocc_prologue(); body; adhocc_epilogue(); }

#define ADHOCC_POST_BEGIN void* adhocc_post_table[] = {
#define ADHOCC_POST(p) (void*)p,
#define ADHOCC_POST_END };

#define adprintf(...) {if (adfile == NULL) error("adfile is null."); fprintf(adfile, __VA_ARGS__);}

int gLine = 1;
FILE* adfile = NULL;

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

string* parse_string() {
  char c = getc(stdin);
  if (c != '"') error("expect \" token in parse_string");
  string* s = empty_string();
  for (;;) {
    c = getc(stdin);
    if (c == '"') break;
    pushc(s, c);
  }
  return s;
}
string* parse_block() {
  int blockcount = 0;
  string* blksrc = empty_string();
  for (;;) {
    char c = getc(stdin);
    if (c == EOF) {
      error("unexpected EOF reached");
    } else if (c == '"') {
      ungetc(c, stdin);
      string* s = parse_string();
      pushc(blksrc, '"');
      pushs(blksrc, cstr(s));
      pushc(blksrc, '"');
    } else if (c == '{') {
      pushc(blksrc, c);
      blockcount++;
    } else if (c == '}') {
      pushc(blksrc, c);
      blockcount--;
      if (blockcount == 0) break;
    } else {
      pushc(blksrc, c);
    }
  }
  return blksrc;
}

string* parse_until(char* uc) {
  string* s = empty_string();
  for (;;) {
    char c = getc(stdin);
    if (c == EOF) {
      return s;
    }
    for (int i=0; i<strlen(uc); i++) {
      if (uc[i] == c) {
        ungetc(c, stdin);
        return s;
      }
    }
    pushc(s, c);
  }
  return NULL;
}

vector* parse_arguments() {
  vector* args = new_vector();
  char c;
  c = getc(stdin);
  if (c != '(') return NULL;
  skip_spaces();
  for (;;) {
    string* id = parse_until(",)");
    vector_push(args, id);
    skip_spaces();
    c = getc(stdin);
    skip_spaces();
    if (c == ')') break;
    skip_spaces();
    if (c != ',') ungetc(c, stdin);
  }
  return args;
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

  // post process
  for (int i=0; i<sizeof(adhocc_post_table)/sizeof(void*); i++) {
    ((void (*)())adhocc_post_table[i])();
  }
}

int main(int argc, char** argv) {
  if (argc == 2) {
    adfile = fopen(argv[1], "w");
    if (adfile == NULL) {
      fprintf(stderr, "couldn't open %s file", argv[0]);
      return 1;
    }
  }
  adhocc_trans();
}
