unittest() {
  gcc -otest.out $1
  ./test.out
  RETCODE=$?
  if [ $RETCODE = 0 ] ; then
    echo "[OK] unittest: $1"
  else
    echo "[ERROR] unittest: $1"
    exit 1
  fi
}

adhocctest() {
  cat $1 | ./adhocc adout.c > out.c
  gcc -o test.out out.c adout.c
  ./test.out
  RETCODE=$?
  if [ $RETCODE = 0 ] ; then
    echo "[OK] adhocc: $1"
  else
    echo "[ERROR] adhocc: $1"
    exit 1
  fi
}

unittest "string_test.c"

./adhocc build adhocc_example.c

adhocctest "test/blank.c"
adhocctest "test/deadcode.c"
adhocctest "test/enum_stringer.c"
adhocctest "test/template.c"
