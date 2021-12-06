#!/bin/bash




for k in 10 100 150 200 250 300
do
    file="./data_$k.txt"
    [ -f $file ] && rm $file || touch $file

    # pour lancer 10 fois
    for j in {1..10}
    do
        for i in $( seq 1 $k )
        do
            bash ./basic_client_func.sh >> $file &
        done
        wait
    done
    python parser.py $file
done





