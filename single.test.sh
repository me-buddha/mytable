#! /bin/bash

function single_core() {
    date
    start=$(date +%s)
    for ((i=1;i<=10000000;i+=1))
    do
       xchain-cli wasm invoke --fee 1000 mytable --method add -a '{"id": "'$i'", "name":"myname"}'
    done
    end=$(date +%s)
    date
    time=$(( $end - $start ))
    echo $time
}

single_core $1