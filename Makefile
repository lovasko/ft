#  Copyright (c) 2018 Daniel Lovasko.
#  All Rights Reserved
#
#  Distributed under the terms of the 2-clause BSD License. The full
#  license is in the file LICENSE, distributed as part of this software.

CC = cc
FTM = -D_BSD_SOURCE -D_XOPEN_SOURCE -D_POSIX_C_SOURCE=200809L -D_DEFAULT_SOURCE
CHECKS = -Wall -Wextra -fstrict-aliasing
CFLAGS = -fno-builtin -std=c99 -Werror $(CHECKS) $(FTM) -Isrc/ -O3

ft: ft.c
	$(CC) $(CFLAGS) -o ft ft.c

clean:
	rm -f ft
	rm -f ft.o
