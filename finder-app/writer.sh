#!/bin/sh
# Solution for assignment 1
# Author: Karan Kishore

WRITEFILE=$1
WRITESTR=$2

if [ -z "$1" ] || [ -z "$2" ]; then
    echo "One or more arguments are missing."
    exit 1
fi

mkdir -p "$(dirname "$WRITEFILE")" && echo "$WRITESTR" >> $WRITEFILE
    
if ! [ $? -eq 0 ]; then
    echo "$WRITEFILE could not be created"
    exit 1
fi
