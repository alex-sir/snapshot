/**
 *  Alex Carbajal
 *  CPT_S 360, Spring 2024
 *  snapshot
 */

#include "generate.h"

int create_executable_copy(const char *executable_copy_path)
{
    const int BUFFER_SIZE = 2048;
    char buffer[BUFFER_SIZE];
    char executable_path[PATHNAME_MAX];
    snprintf(executable_path, sizeof(executable_path), "/proc/%d/exe", getpid());

    int executable = open(executable_path, O_RDONLY);
    if (executable == -1) // unable to open file for reading
    {
        return -1;
    }
    int executable_copy = open(executable_copy_path, O_WRONLY | O_TRUNC | O_CREAT, 0777);
    if (executable_copy == -1) // unable to create file
    {
        close(executable);
        return -1;
    }

    int bytes_read = 0, bytes_written = 0;
    // copy all bytes from executable and write them to executable_copy
    do
    {
        bytes_read = read(executable, buffer, BUFFER_SIZE);
        if (bytes_read == -1)
        {
            close(executable);
            close(executable_copy);
            return -1;
        }
        bytes_written = write(executable_copy, buffer, bytes_read);
        if (bytes_written == -1)
        {
            close(executable);
            close(executable_copy);
            return -1;
        }
    } while (bytes_read);

    close(executable);
    close(executable_copy);

    return 0;
}

int remove_temp_dir(const char *dirpath, const char *executable_copy_path)
{
    if (remove(executable_copy_path) == -1 ||
        remove(dirpath) == -1)
    {
        return -1;
    }

    return 0;
}
