#!/bin/bash

file="./test_data_log.txt"
[ -f $file ] && rm $file
touch $file

echo "waiting please..."

for k in 50 100 150 200 250 300 # number of clients
do

    echo "n_clients - $k" >> $file
    for j in {1..2} # launch 2 times to compute a mean
    do
        time_start=$(date +%s.%N)
        for i in $( seq 1 $k ) # launch k clients (almost) simultaneously
        do
            echo "$i - $(bash ./basic_client_func.sh)" >> $file &
        done
        time_end=$(date +%s.%N)
        delta=$(echo "$time_end - $time_start" | bc)
        echo "launch_time - $delta" >> $file
        sleep 10
        pkill -P $$
    done
    # python parser.py $file
done

echo "finished"




