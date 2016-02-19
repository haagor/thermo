#! /bin/bash

echo "---- s , i , user|cpu - kilobytes , memo/cell , cell ----" >> ../res.txt

make && ./main -s 0123456789 -m -M -i 1
echo "------------------" >> ../res.txt
make && ./main -s 0123456789 -m -M -i 10
echo "------------------" >> ../res.txt
make && ./main -s 0123456789 -m -M -i 100
echo "------------------" >> ../res.txt
make && ./main -s 01234567 -m -M -i 1000
echo "------------------" >> ../res.txt
make && ./main -s 012345 -m -M -i 10000