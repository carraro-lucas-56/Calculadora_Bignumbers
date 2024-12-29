#!/bin/bash

in=$(ls instances | grep -F .in | cut -f1 --delimiter='.')

for i in $in
do
    ./main < instances/$i.in > output.txt 
    out=$(diff instances/$i.out output.txt)
    if [ "$out" != "" ]
    then
        echo "instância $i com problemas"
    else
        echo "instância $i OK"
    fi 
done