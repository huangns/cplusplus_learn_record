#!/bin/bash
i=1
sum=100000
while((i<sum))
do
    date +%s%N
    ((i++))
done
echo "copy impl over."
