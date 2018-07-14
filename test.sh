
unittest() {
  gcc -otest.out $1
  ./test.out
  RETCODE=$?
  if [ $RETCODE = 0 ] ; then
    echo "[OK] unittest: $1"
  else
    echo "[ERROR] unittest: $1"
  fi
}

adhocctest() {
  OUT=`echo "$1" | ./adhocc.out`
  if [ "$OUT" = "$2" ] ; then
    echo "[OK] adhocc: $1"
  else
    echo "[ERROR] adhocc: $1, expected $2, but got $OUT"
  fi
}

gcc -Wall -oadhocc.out adhocc.c string.c

unittest "string_test.c"

adhocctest "yukari" "yukari"
adhocctest "%%deadcode" "0xDEADC0DE"
