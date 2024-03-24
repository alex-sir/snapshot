/**
 *  Alex Carbajal
 *  CPT_S 360, Spring 2024
 *  snapshot
 */

#ifndef GENERATE
#define GENERATE

#include <stdio.h>  // for snprintf(), remove()
#include <stdlib.h> // for malloc()
#include <unistd.h> // for pathconf(), getpid(), read(), write(), close()
#include <fcntl.h>  // for open()

#include "helpers.h"

#define PATHNAME_MAX pathconf(".", _PC_PATH_MAX) + 1 // max size of a file pathname

extern int create_executable_copy(const char *progname, const char *dirname);
extern int remove_files(const char *progname, const char *dirname);

#endif
