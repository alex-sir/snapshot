/**
 *  Alex Carbajal
 *  CPT_S 360, Spring 2024
 *  snapshot
 */

#include "generate.h"

int create_executable_copy(const char *progname, const char *dirname)
{
    int bufferSize = 2048, bytesRead = 0;
    char *buffer = (char *)malloc(bufferSize * sizeof(char));
    if (buffer == NULL) // unable to allocate memory
    {
        print_err();
        return -1;
    }

    char executable_path[PATHNAME_MAX];
    snprintf(executable_path, sizeof(executable_path), "/proc/%d/exe", getpid());
    char executable_copy_path[PATHNAME_MAX];
    snprintf(executable_copy_path, sizeof(executable_copy_path), "%s/%s", dirname, progname);

    int executable = open(executable_path, O_RDONLY);
    if (executable == -1) // unable to open file for reading
    {
        print_err();
        return -1;
    }
    int executable_copy = open(executable_copy_path, O_WRONLY | O_TRUNC | O_CREAT, 0777);
    if (executable_copy == -1) // unable to create file
    {
        print_err();
        return -1;
    }

    // copy all bytes from executable and write them to executable_copy
    do
    {
        bytesRead = read(executable, buffer, bufferSize);
        write(executable_copy, buffer, bytesRead);
    } while (bytesRead);

    free(buffer);
    close(executable);
    close(executable_copy);

    return 0;
}

int remove_files(const char *progname, const char *dirname)
{
    return 0;
}
