# Find Tabs

## Introduction
Utility program to find and report the location of all tab characters in a
file.

## Example
```
$ ft /usr/include/errno.h
/usr/include/errno.h: 19,3
/usr/include/errno.h: 19,32
/usr/include/errno.h: 22,8
/usr/include/errno.h: 26,8
/usr/include/errno.h: 27,18
/usr/include/errno.h: 36,7
/usr/include/errno.h: 38,7
/usr/include/errno.h: 45,8
/usr/include/errno.h: 69,28
$ echo $?
2
$ ft /etc/passwd
$ echo $?
0
$ ft /doesnotexist
open failed: No such file or directory
$ echo $?
1
```

## Exit code
The process can exit with three different exit codes:
 * `0`: successful execution and no tabs found
 * `1`: unsuccessful execution
 * `2`: successful execution but at least one tab was found

## Resource usage
The program uses a single thread, whilst only opening a single file at a time.
All files are streamed from the disk, maximum 512 bytes at a time. This means
the program introduces no limits to the length or number of the files
processed.

## License
The program is licensed under the terms of the [2-clause BSD license](LICENSE).
In case you require a different license, please contact the author.

## Author
Daniel Lovasko <daniel.lovasko@gmail.com>
