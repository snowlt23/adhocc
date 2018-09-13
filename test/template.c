
%%template TIList {
  typedef struct {
    int index;
  } IList%%1;
}

%%expand TIList(int)

int main() {
  IListint li;
  return 0;
}

