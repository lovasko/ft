// Copyright (c) 2018 Daniel Lovasko.
// All Rights Reserved
//
// Distributed under the terms of the 2-clause BSD License. The full
// license is in the file LICENSE, distributed as part of this software.

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>


// Custom exit codes.
#define FT_SUCCESS 0 ///< Successful execution without any tabs found.
#define FT_FAILURE 1 ///< Technical failure during the execution.
#define FT_HASTABS 2 ///< Successful execution with tabs found.

/// Report the tab character to the standard output stream. The report includes
/// the file path, line number, and character position.
///
/// @param[in] row  line number
/// @param[in] col  character position
/// @param[in] path file path
static void
report_tab(const uint64_t row, const uint64_t col, const char* path)
{
	printf("%s: %" PRIu64 ",%" PRIu64 "\n", path, row, col);
}

/// Traverse bytes of a file and find all tab characters.
/// @return success/failure indication
///
/// @param[out] ntab number of tabs
/// @param[in]  fd   open file descriptor
/// @param[in]  path file path
static bool
scan_file(uint64_t* ntab, int fd, const char* path)
{
	uint64_t col;
	uint64_t row;
	ssize_t retss;
	ssize_t i;
	char buf[512];

	col = 1;
	row = 1;
	*ntab = 0;

	// Traverse all bytes of the file.
	while (true) {
		retss = read(fd, buf, sizeof(buf));

		// Check for errors.
		if (retss == -1) {
		  perror("read failed");
			return false;
		}

		// Check for end of file.
		if (retss == 0)
			return true;

		for (i = 0; i < retss; i++) {
			// In case the new-line indicator is found, move to another line and
			// reset the character counter.
			if (buf[i] == '\n') {
				row++;
				col = 1;
				continue;
			}

			// In case a tab character was found, increase the overall number of
			// tabs found. Moreover, report the finding along with the relevant
			// details.
			if (buf[i] == '\t') {
				(*ntab)++;
				report_tab(row, col, path);
			}

			// Move to the next character position.
			col++;
		}
	}

	return true;
}

/// Utility to find tabs.
/// @return process exit code
///
/// @param[in] argc argument count
/// @param[in] argv argument vector
int
main(int argc, char* argv[])
{
  uint64_t ntab;
	int fd;
	int i;
	int reti;
	bool retb;

	// Reset the overall counter of tabs. The utility counts the overall number
	// of tabs in all the input files provided. Once at least one tab is found,
	// the tool reports its findings and changes its exit code.
	ntab = 0;

	// In case no arguments are provided, inspect the standard input stream.
	if (argc == 1) {
		retb = scan_file(&ntab, STDIN_FILENO, "stdin");
		if (retb == false)
			return FT_FAILURE;
	}

	// Traverse all files provided as arguments.
	for (i = 1; i < argc; i++) {
		// Open the file.
		fd = open(argv[i], O_RDONLY);
		if (fd == -1) {
		  perror("open failed");
			return FT_FAILURE;
		}

		// Scan the file and report any tab characters found. The report also
		// includes the file name, line number, and the character number.
		retb = scan_file(&ntab, fd, argv[i]);
		if (retb == false)
			return FT_FAILURE;

		// Close the file.
		reti = close(fd);
		if (reti == -1) {
		  perror("close failed");
			return FT_FAILURE;
		}
	}

	return ntab > 0 ? FT_HASTABS : FT_SUCCESS;
}
