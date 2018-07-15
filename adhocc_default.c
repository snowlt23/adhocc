void* hooknames[1024] = {};
int hooknamepos = 0;

ADHOCC_DEF(trans_hook, {
  skip_spaces();
  string* hookname = parse_ident();
  hooknames[hooknamepos] = hookname;
  hooknamepos++;

  skip_spaces();
  string* body = parse_block();
  printf("void adhocc_hook_%s() {adhocc_prologue(); %s; adhocc_epilogue();}", cstr(hookname), cstr(body));
});

void post_hook() {
  printf("ADHOCC_BEGIN\n");
  for (int i=0; i<hooknamepos; i++) {
    char* hookname = cstr((string*)hooknames[i]);
    printf("ADHOCC_HOOK(\"%s\", adhocc_hook_%s)\n", hookname, hookname);
  }
  printf("ADHOCC_END\n");
  printf("ADHOCC_POST_BEGIN\n");
  printf("ADHOCC_POST_END\n");
}

ADHOCC_DEF(trans_deadcode, printf("0xDEADC0DE"));

ADHOCC_BEGIN
ADHOCC_HOOK("hook", trans_hook)
ADHOCC_HOOK("deadcode", trans_deadcode)
ADHOCC_END

ADHOCC_POST_BEGIN
ADHOCC_POST(post_hook)
ADHOCC_POST_END
