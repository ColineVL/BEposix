#!/bin/bash

start=1
nb_clients=1000

for i in {1..1000}
do
    bash ./basic_client_func.sh &
done
wait
