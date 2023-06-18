#!/bin/sh
# Solution for assignment 1
# Author: Karan Kishore

FILESDIR=$1
SEARCHSTR=$2

if [ -z "$1" ] || [ -z "$2" ]; then
    echo "One or more arguments are missing."
    exit 1
elif ! [ -d "$FILESDIR" ]; then
    echo "FILESDIR does not represent a directory on the filesystem"
    exit 1
else
    count=$(find "$FILESDIR" -type f | wc -l)
    match=$(grep -r "$SEARCHSTR" "$FILESDIR" | wc -l)
    echo "The number of files are $count and the number of matching lines are $match"
fi

