/*
Miscellaneous functions common to both part 1 and 2 of the assignment.
*/

#ifndef MISC_H
#define MISC_H

FILE* safe_fopen(const char *fp, const char *mode);
void* safe_malloc(size_t size);

#endif
