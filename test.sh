
unittest() {
  gcc -otest.out $1
  ./test.out
  RETCODE=$?
  if [ $RETCODE = 0 ] ; then
    echo "[OK] $1"
  else
    echo "[ERROR] $1"
  fi
}

unittest "string_test.c"
