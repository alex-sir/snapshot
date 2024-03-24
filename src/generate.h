/**
 *  Alex Carbajal
 *  CPT_S 360, Spring 2024
 *  snapshot
 */

#ifndef GENERATE
#define GENERATE

#include <stdio.h>  // for snprintf(), remove()
#include <stdlib.h> // for malloc()
#include <string.h> // for strlen(), strcmp()
#include <unistd.h> // for pathconf(), getpid(), read(), write(), close()
#include <fcntl.h>  // for open()
#include <dirent.h> // for opendir(), closedir(), readdir()

#include "helpers.h"

#define PATHNAME_MAX pathconf(".", _PC_PATH_MAX) + 1 // max size of a file pathname

/**
 * @brief create an executable file copy of the current running program's executable file
 *
 * @param executable_copy_path path to the executable file copy
 * @return int 0 = successful copy | -1 = error occurred
 */
extern int create_executable_copy(const char *executable_copy_path);
/**
 * @brief create a README.txt file containing the contents of readme
 *
 * @param readme_path path to the README.txt file
 * @param readme content copied into README.txt
 * @return int 0 = successful creation | -1 = error occurred
 */
extern int create_readme(const char *readme_path, const char *readme);
/**
 * @brief remove a temporary directory
 *
 * @param dirpath path to the temporary directory
 * @return int 0 = successful removal | -1 = error occurred
 */
extern int remove_temp_dir(const char *dirpath);

#endif
