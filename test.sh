#! /bin/bash

function single_core() {
    step=$1
    file=$1.txt
    errorfile=$1.e.txt
    date 1>>$file 2>>$errorfile
    start=$(date +%s)
    for ((i=1*$step;i<=10000000*$step;i+=10))
    do
       # echo $i 1>>$file 2>>$errorfile
       xchain-cli wasm invoke --fee 1000 mytable --method add -a '{"id": "'$i'", "name":"myname"}' 1>>$file 2>>$errorfile
    done
    end=$(date +%s)
    date 1>>$file 2>>$errorfile
    time=$(( $end - $start ))
    echo $time 1>>$file 2>>$errorfile
}

single_core 1 &
single_core 2 &
single_core 3 &
single_core 4 &
single_core 5 &
single_core 6 &
single_core 7 &
single_core 8 &
single_core 9 & 
single_core 10 &
