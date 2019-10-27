#!/bin/bash
#logical operator 
#by hns 20191027
DIR=/home/h/sh_learn/1027/1/2
if [ -d $DIR ]; then
    echo "$DIR exist."
else
    mkdir -p $DIR
fi
