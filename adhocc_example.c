%%hook enum {
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

    string* s = empty_string();
    format(s, "%s, ", cstr(kind));
    pushs(enumsrc, cstr(s));
    format(s, "if (kind == %s) return \"%s\";", cstr(kind), cstr(kind));
    pushs(tostrsrc, cstr(s));

    skip_spaces();
    c = getc(stdin);
    if (c == ',') continue;
    ungetc(c, stdin);
  }
  if (getc(stdin) != ';') error("expected ; token in %%%%enum");

  printf("typedef enum { %s } %s;\n", string_cstr(enumsrc), string_cstr(enumname));
  printf("char* %s_tostring(%s kind) { %s }\n", string_cstr(enumname), string_cstr(enumname), string_cstr(tostrsrc));
}

%%hook deadcode {
  printf("0xDEADC0DE");
}

typedef struct {
  string* name;
  string* body;
} Template;

Template tnames[1024] = {};
int tnamepos = 0;

%%hook template {
  skip_spaces();
  string* name = parse_ident();
  skip_spaces();
  string* body = parse_block();
  tnames[tnamepos] = (Template){name, body};
  tnamepos++;
}

%%hook expand {
  skip_spaces();
  string* name = parse_ident();
  vector* args = parse_arguments();
  string* tmpl = NULL;
  for (int i=0; i<tnamepos; i++) {
    if (strcmp(tnames[i].name->data, name->data) == 0) {
      tmpl = tnames[i].body;
      break;
    }
  }
  if (tmpl == NULL) error("undefined %s template.", name->data);

  for (int i=1; i<tmpl->len-1; i++) {
    char c = tmpl->data[i];
    if (c == '%') {
      if (i+2 < tmpl->len && tmpl->data[i+1] == '%') {
        int n = tmpl->data[i+2] - '1';
        if (args->len <= n) error("%s expand hasn't %d argument.", name->data, n);
        printf("%s", ((string*)vector_get(args, n))->data);
        i+=2;
        continue;
      }
    }
    printf("%c", c);
  }
}
