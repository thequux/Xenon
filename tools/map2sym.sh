#!/bin/sh
echo 0x0000000 undef >$2
cat $1| sed -nre  's/ {16}(.{18}) {16}/\1 /p' |grep -v = >>$2
