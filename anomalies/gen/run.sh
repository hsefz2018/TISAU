#!/bin/sh

g++ -o std ../std/anomalies.cpp

for i in {1..9}
do
    echo "Case #$i"
    time ./std < t/0$i.in > t/0$i.ans
done

for i in {10..20}
do
    echo "Case #$i"
    time ./std < t/$i.in > t/$i.ans
done

rm std

