/**
 *  Alex Carbajal
 *  CPT_S 360, Spring 2024
 *  snapshot
 */

#include "helpers.h"

void print_err(void)
{
    fprintf(stderr, "ERROR: %s\n", strerror(errno));
}

int copy_file_data(const int file_from, const int file_to)
{
    const size_t BUFFER_SIZE = 2048;
    char buffer[BUFFER_SIZE];
    int bytes_read = 0, bytes_written = 0;
    // copy all bytes from file_from and write them to file_to
    do
    {
        bytes_read = read(file_from, buffer, BUFFER_SIZE);
        if (bytes_read == -1)
        {
            return -1;
        }
        bytes_written = write(file_to, buffer, bytes_read);
        if (bytes_written == -1)
        {
            return -1;
        }
    } while (bytes_read);

    return 0;
}

int set_core_name(char *core_name, const size_t core_name_size, const pid_t corepid)
{
    snprintf(core_name, core_name_size, "core");

    // determine if the core dump filename is not just "core" and contains a suffix
    DIR *dir;
    dir = opendir(".");
    if (dir == NULL)
    {
        return -1;
    }
    struct dirent *entry;
    char corepid_str[8];
    snprintf(corepid_str, sizeof(corepid_str), "%d", corepid);
    errno = 0;
    while ((entry = readdir(dir)))
    {
        // check if the core dump file exists with a suffix (core.*) containing a PID
        if (strstr(entry->d_name, "core.") != NULL && strstr(entry->d_name, corepid_str) != NULL)
        {
            strncpy(core_name, entry->d_name, core_name_size);
            break;
        }
    }
    closedir(dir);
    if (errno != 0)
    {
        return -1;
    }

    return 0;
}
