/**
 *  Alex Carbajal
 *  CPT_S 360, Spring 2024
 *  snapshot
 */

#ifndef HELPERS
#define HELPERS

#include <stdio.h>     // for fprintf(), snprintf()
#include <string.h>    // for strerror(), strncpy(), strstr()
#include <errno.h>     // for errno
#include <unistd.h>    // for read(), write(), close()
#include <dirent.h>    // for opendir(), closedir(), readdir()
#include <sys/types.h> // for pid_t

/**
 * @brief print an error message
 */
extern void print_err(void);
/**
 * @brief copy all data from the file file_from to the file file_to
 *
 * @param file_from file to copy all data from
 * @param file_to file to copy all data to
 * @return int 0 = successful copy | -1 = error occurred
 */
extern int copy_file_data(const int executable, const int executable_copy);
/**
 * @brief set the name of the core dump file
 *
 * @param core_name string containing the name of the core dump file
 * @param core_name_size size of the string core_name
 * @param corepid PID of the core dump file
 * @return int 0 = successfully set name | -1 = error occurred
 */
extern int set_core_name(char *core_name, const size_t core_name_size, const pid_t corepid);

#endif
