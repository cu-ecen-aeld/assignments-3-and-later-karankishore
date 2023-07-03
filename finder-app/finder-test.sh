#!/bin/sh
# Tester script for assignment 1 and assignment 2
# Author: Siddhant Jajoo

set -e
set -u

NUMFILES=10
WRITESTR=AELD_IS_FUN
WRITEDIR=/tmp/aeld-data
username=$(cat conf/username.txt)

echo "Removing the old writer utility and compiling as a native application"
#make clean
#make
./writer $WRITEDIR $WRITESTR
