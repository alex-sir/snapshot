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

/**
 * @brief create an executable file copy of the current running program's executable file
 *
 * @param progname name of the current running program
 * @param dirname name of the directory where the executable file copy is stored
 * @return int 0 = successful copy | -1 = error occurred
 */
extern int create_executable_copy(const char *executable_copy_path);
extern int remove_temp_dir(const char *dirpath, const char *executable_copy_path);

#endif
