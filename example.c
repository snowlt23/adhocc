#include <stdio.h>

%%enum TokenKind {
  TOKEN_INTLIT,
  TOKEN_STRLIT
};

int main() {
  printf("%s\n", TokenKind_tostring(TOKEN_INTLIT));
}
