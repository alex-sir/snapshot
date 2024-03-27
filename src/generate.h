/**
 *  Alex Carbajal
 *  CPT_S 360, Spring 2024
 *  snapshot
 */

#ifndef GENERATE
#define GENERATE

#include <stdio.h>     // for snprintf(), remove(), rename()
#include <stdlib.h>    // for abort(), system()
#include <string.h>    // for strlen(), strcmp(), strncpy()
#include <errno.h>     // for errno
#include <unistd.h>    // for getpid(), fork(), access()
#include <fcntl.h>     // for open()
#include <dirent.h>    // for opendir(), closedir(), readdir()
#include <sys/types.h> // for pid_t
#include <sys/wait.h>  // for wait()

#include "helpers.h"

#define PATHNAME_MAX pathconf(".", _PC_PATH_MAX) + 1 // max size of a file pathname

/**
 * @brief create an executable file copy of the current running program's executable file
 *
 * @param ssname name of the directory where the executable file copy is stored
 * @param progname name of the current running program's executable file
 * @return int 0 = successful copy | -1 = error occurred
 */
extern int create_executable_copy(const char *ssname, const char *progname);
/**
 * @brief create a README.txt file containing the contents of readme
 *
 * @param ssname name of the directory where README.txt is stored
 * @param readme content copied into README.txt
 * @return int 0 = successful creation | -1 = error occurred
 */
extern int create_readme(const char *ssname, const char *readme);
/**
 * @brief create a core dump file of the current program
 *
 * @param ssname name of the directory where the core dump file is stored
 * @return int 0 = successful creation | -1 = error occurred
 */
extern int create_core(const char *ssname);
/**
 * @brief create a tarball of a directory
 *
 * @param ssname name of the directory to create a tarball of
 * @return int 0 = successful creation | -1 = error occurred
 */
extern int create_tarball(const char *ssname);
/**
 * @brief remove a temporary directory
 *
 * @param ssname name of the temporary directory
 * @return int 0 = successful removal | -1 = error occurred
 */
extern int remove_temp_dir(const char *ssname);

#endif
