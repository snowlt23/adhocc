#include <assert.h>
#include <string.h>

%%enum TokenKind {
  TOKEN_INTLIT,
  TOKEN_STRLIT,
  TOKEN_IDENT,
};

int main() {
  assert(strcmp(TokenKind_tostring(TOKEN_STRLIT), "TOKEN_STRLIT") == 0);
}
