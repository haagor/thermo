#! /bin/bash

ITER=1

echo "---- e , s , t ,  i , user|cpu - kilobytes ----" >> ./res/res.txt

make && ./bin/main -s 5 -m -M -i $ITER -t 0 -e 0
make && ./bin/main -s 5 -m -M -i $ITER -t 0 -e 1
echo "------------------" >> ./res/res.txt
make && ./bin/main -s 5 -m -M -i $ITER -t 1 -e 1
echo "------------------" >> ./res/res.txt
make && ./bin/main -s 5 -m -M -i $ITER -t 2 -e 1
echo "------------------" >> ./res/res.txt
make && ./bin/main -s 5 -m -M -i $ITER -t 3 -e 1
echo "------------------" >> ./res/res.txt
make && ./bin/main -s 5 -m -M -i $ITER -t 4 -e 1
echo "------------------" >> ./res/res.txt
make && ./bin/main -s 5 -m -M -i $ITER -t 5 -e 1
echo "---------^memoire^---------" >> ./res/res.txt

ITER=500

make && ./bin/main -s 024568 -m -M -i $ITER -t 0 -e 0
echo "------------------" >> ./res/res.txt
make && ./bin/main -s 0245 -m -M -i $ITER -t 15 -e 1
make && ./bin/main -s 68 -m -M -i $ITER -t 15 -e 1
echo "------------------" >> ./res/res.txt
