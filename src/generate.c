/**
 *  Alex Carbajal
 *  CPT_S 360, Spring 2024
 *  snapshot
 */

#include "generate.h"

int create_executable_copy(const char *ssname, const char *progname)
{
    char executable_path[PATHNAME_MAX];
    char executable_copy_path[PATHNAME_MAX];
    snprintf(executable_path, sizeof(executable_path), "/proc/%d/exe", getpid());
    snprintf(executable_copy_path, sizeof(executable_copy_path), "%s/%s", ssname, progname);
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

int create_readme(const char *ssname, const char *readme)
{
    char readme_path[PATHNAME_MAX];
    snprintf(readme_path, sizeof(readme_path), "%s/README.txt", ssname);
    int readme_file = open(readme_path, O_WRONLY | O_TRUNC | O_CREAT, 0600);
    if (readme_file == -1)
    {
        return -1;
    }
    int bytes_written = 0;

    bytes_written = write(readme_file, readme, strlen(readme));
    if (bytes_written == -1)
    {
        close(readme_file);
        return -1;
    }
    if (readme[strlen(readme) - 1] != '\n') // readme does not end in a newline
    {
        bytes_written = write(readme_file, "\n", 1); // add the newline
        if (bytes_written == -1)
        {
            close(readme_file);
            return -1;
        }
    }

    close(readme_file);

    return 0;
}

int create_core(const char *ssname)
{
    pid_t childpid = fork();
    if (childpid == -1) // error forking child
    {
        return -1;
    }
    else if (childpid == 0) // in child
    {
        abort(); // create the core dump file
    }
    else // child forked successfully
    {
        childpid = wait(NULL);
    }

    const int core_name_size = FILENAME_MAX;
    char core_name[core_name_size];
    char core_path[PATHNAME_MAX];
    if (set_core_name(core_name, core_name_size) == -1)
    {
        return -1;
    }
    snprintf(core_path, sizeof(core_path), "%s/core", ssname);

    if (rename(core_name, core_path) == -1) // move the core file to the temp directory
    {
        return -1;
    }

    return 0;
}

int set_core_name(char *core_name, const int core_name_size)
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
    while ((entry = readdir(dir)))
    {
        // check if the core dump file exists with a suffix (core.*)
        if (strstr(entry->d_name, "core.") != NULL)
        {
            strncpy(core_name, entry->d_name, core_name_size);
            break;
        }
    }
    closedir(dir);

    return 0;
}

int create_tarball(const char *ssname)
{
    char tarball_name[FILENAME_MAX];
    const int tarball_command_size = FILENAME_MAX + PATHNAME_MAX + 12;
    char tarball_command[tarball_command_size];
    snprintf(tarball_name, sizeof(tarball_name), "%s.tgz", ssname);
    snprintf(tarball_command, sizeof(tarball_command), "tar -czvf %s %s", tarball_name, ssname);
    if (system(tarball_command) == -1)
    {
        return -1;
    }

    return 0;
}

int remove_temp_dir(const char *ssname)
{
    DIR *dir;
    dir = opendir(ssname);
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
        snprintf(file_path, sizeof(file_path), "%s/%s", ssname, entry->d_name);
        remove(file_path);
    }
    closedir(dir);

    if (remove(ssname) == -1) // remove the directory
    {
        return -1;
    }

    return 0;
}
