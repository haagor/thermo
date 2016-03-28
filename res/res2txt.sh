#! /bin/bash

cat $1 | sed -e '
s/---*//g
s/  *//g
1,1 s/^/ /
s/,/	/g
s/|/	/g
s/-/	/g
' | sort | sed -e '
s/ //
s/\./,/g
'
