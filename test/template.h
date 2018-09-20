
#include <stdio.h>
%%adinclude "out.c"

%%template TIList {
  typedef struct {
    int index;
  } IList%%1;
} {
  void %%1_print_index(IList%%1 il) {
    printf("%d\n", il.index);
  }
}

%%expand TIList(int)

