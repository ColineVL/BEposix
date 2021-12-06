#!/bin/bash

file="./data.txt"

[ -f $file ] && rm $file || touch $file

for i in {1..200}
do
    echo "$i $(bash ./basic_client_func.sh)" >> $file &
done

sleep 5

python parser.py



