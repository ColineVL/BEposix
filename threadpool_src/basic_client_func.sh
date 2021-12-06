#!/bin/bash


start=`date +%s.%N`
./web_client 127.0.0.1 > /dev/null 2>&1 
end=`date +%s.%N`
runtime=$( echo "$end - $start" | bc -l )

echo $runtime
