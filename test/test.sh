#!/bin/sh
set -xe

# Compile the program.
rm -f ft
cc -Wall -Werror -std=c99 -O0 -o ft ../ft.c

# Run the program on the file with no tabs.
./ft notab.txt
test "$?" = "0"

# Run the program on the file with a single tab.
./ft tab.txt
test "$?" = "1"
