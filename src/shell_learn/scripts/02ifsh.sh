#!/bin/bash
#if test
#by hns 20191027
NUM1=100
NUM2=200
if(($NUM1 > $NUM2));then
        echo "$NUM1 is greater than $NUM2"
else
        echo "$NUM1 is less than $NUM2"
fi
