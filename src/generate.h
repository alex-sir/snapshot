/**
 *  Alex Carbajal
 *  CPT_S 360, Spring 2024
 *  snapshot
 */

#ifndef GENERATE
#define GENERATE

#include <stdio.h>    // for snprintf(), remove(), rename()
#include <stdlib.h>   // for malloc(), abort(), system()
#include <string.h>   // for strlen(), strcmp(), strncpy(), strstr()
#include <unistd.h>   // for pathconf(), getpid(), read(), write(), close(), fork(), access()
#include <fcntl.h>    // for open()
#include <dirent.h>   // for opendir(), closedir(), readdir()
#include <sys/wait.h> // for wait()

#include "helpers.h"

#define PATHNAME_MAX pathconf(".", _PC_PATH_MAX) + 1 // max size of a file pathname

/**
 * @brief create an executable file copy of the current running program's executable file
 *
 * @param ssname path to the directory where the executable file copy is stored
 * @param progname name of the current running program's executable file
 * @return int 0 = successful copy | -1 = error occurred
 */
extern int create_executable_copy(const char *ssname, const char *progname);
/**
 * @brief create a README.txt file containing the contents of readme
 *
 * @param ssname path to the directory where README.txt is stored
 * @param readme content copied into README.txt
 * @return int 0 = successful creation | -1 = error occurred
 */
extern int create_readme(const char *ssname, const char *readme);
/**
 * @brief create a core dump file of the current program
 *
 * @param ssname path to the directory where the core dump file is stored
 * @return int 0 = successful creation | -1 = error occurred
 */
extern int create_core(const char *ssname);
/**
 * @brief set the name of the core dump file
 *
 * @param core_name string containing the name of the core dump file
 * @param core_name_size size of the string core_name
 * @return int 0 = successfully set name | -1 = error occurred
 */
extern int set_core_name(char *core_name, const int core_name_size);
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
 * @param ssname path to the temporary directory
 * @return int 0 = successful removal | -1 = error occurred
 */
extern int remove_temp_dir(const char *ssname);

#endif
