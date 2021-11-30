#!/bin/bash



for i in {1..36}
do
    #repeat 36 times 20 clients requesting at the same time
    # then wait 300 ms 
    sleep 0.3
    for i in {1..20}
    do
        bash ./basic_client_func.sh &
    done
done
