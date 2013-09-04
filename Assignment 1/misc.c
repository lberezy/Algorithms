/*
Miscellaneous functions common to both part 1 and 2 of the assignment.
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>

#include "misc.h"
#include "errorcodes.h"
#include "debug.h"

int counter(int code) {
	/*
	Static incrementing counter. Calls to this function will increment the 
	counter by 'code'. Any code < 0 will reset the counter to 0. Use a code
	of 0 to return the current counter value.
	*/
	static int count = 0;
	if (code >= 0) {
		count += code;
	} else { /* reset counter */
		count = 0;
	}
	return count;
}

void* safe_malloc(const size_t size) {
	/* 
	Checks to see if malloc has failed, slightly safer than usual.
	Probably pointless because a seg-fault can at least gives you a core
	dump to look through later on, but this is "good practice".
	*/

	void *tmp = malloc(size);
	assert(size > 0);
	if (!tmp) {
		/* printing is kind of pointless because it invokes malloc() again */
		fprintf(stderr, "(malloc)Memory allocation failed!\n");
		fflush(stderr);
		sleep(1);
		exit(MALLOC_ERROR);
	}

	return tmp;
}


FILE* safe_fopen(const char *fp, const char *mode) {
	/*
	Attempts to return a valid handle to a file.
	*/

	void *tmp = fopen(fp, mode);
	if (!tmp) {
		fprintf(stderr, "Failed to open file!\n");
		fflush(stderr);
		sleep(1);
		exit(FILE_OPEN_ERROR);
	}

	return tmp;
}
