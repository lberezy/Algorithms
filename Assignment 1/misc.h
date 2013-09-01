/*
Miscellaneous functions common to both part 1 and 2 of the assignment.
*/

#ifndef MISC_H
#define MISC_H

void* safe_malloc(size_t size);
FILE* safe_fopen(const char *fp, const char *mode);

#endif
