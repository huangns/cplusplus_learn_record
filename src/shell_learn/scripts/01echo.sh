#!/bin/bash
#by author: hns
# time: 2019.10.27
#$0 script name, $1 the 1st param, $2 the 2nd param, $? show whether last command is correct
echo "shell echo learn"
echo "The \$0 value: $0"
echo "The \$1 value: $1"
echo "The \$2 value: $2"
echo "The \$? value: $?"
A=123 #no space between A and =, also between = and value
echo "The \$? value: $?"
echo "The A value: $A"
echo $A
