/**
 *  Alex Carbajal
 *  CPT_S 360, Spring 2024
 *  snapshot
 */

#include "generate.h"

int create_executable_copy(const char *executable_copy_path)
{
    char executable_path[PATHNAME_MAX];
    snprintf(executable_path, sizeof(executable_path), "/proc/%d/exe", getpid());
    // open the executable and executable copy
    int executable = open(executable_path, O_RDONLY);
    if (executable == -1)
    {
        return -1;
    }
    int executable_copy = open(executable_copy_path, O_WRONLY | O_TRUNC | O_CREAT, 0775);
    if (executable_copy == -1)
    {
        close(executable);
        return -1;
    }

    const int BUFFER_SIZE = 2048;
    char buffer[BUFFER_SIZE];
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

int create_readme(const char *readme_path, const char *readme)
{
    int readme_file = open(readme_path, O_WRONLY | O_TRUNC | O_CREAT, 0600);
    if (readme_file == -1)
    {
        return -1;
    }
    int bytes_written = 0;

    if (readme[strlen(readme) - 1] != '\n') // readme does not end in a newline
    {
        bytes_written = write(readme_file, readme, strlen(readme));
        if (bytes_written == -1)
        {
            close(readme_file);
            return -1;
        }
    }

    close(readme_file);

    return 0;
}

int remove_temp_dir(const char *dirpath)
{
    DIR *dir;
    dir = opendir(dirpath);
    if (dir == NULL)
    {
        return -1;
    }

    char file_path[PATHNAME_MAX];
    struct dirent *entry;
    // remove all the files in the directory
    while ((entry = readdir(dir)))
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }
        snprintf(file_path, sizeof(file_path), "%s/%s", dirpath, entry->d_name);
        remove(file_path);
    }
    closedir(dir);

    if (remove(dirpath) == -1) // remove the directory
    {
        return -1;
    }

    return 0;
}
