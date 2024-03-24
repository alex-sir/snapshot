/**
 *  Alex Carbajal
 *  CPT_S 360, Spring 2024
 *  snapshot
 */

#include "generate.h"
#include "helpers.h"

#include <stdio.h>        // for remove()
#include <libgen.h>       // for basename()
#include <sys/stat.h>     // for mkdir()
#include <sys/resource.h> // for setrlimit()

/* TODO
 * - create a core dump of the current program
 * - create a tarball containing the executable, core dump, and README.txt
 */

int snapshot(char *fn, char *progpath, char *readme)
{
    struct rlimit core_limit = {RLIM_INFINITY, RLIM_INFINITY};
    if (setrlimit(RLIMIT_CORE, &core_limit) == -1) // set unlimited core dump size
    {
        print_err();
        return -1;
    }

    if (mkdir(fn, 0775) == -1) // create temp directory
    {
        print_err();
        return -1;
    }

    const char *progname = basename(progpath);
    char executable_copy_path[PATHNAME_MAX];
    char readme_path[PATHNAME_MAX];
    snprintf(executable_copy_path, sizeof(executable_copy_path), "%s/%s", fn, progname);
    snprintf(readme_path, sizeof(readme_path), "%s/README.txt", fn);

    // create all the files for the temp directory
    if (create_executable_copy(executable_copy_path) == -1 ||
        create_readme(readme_path, readme) == -1)
    {
        print_err();
        return -1;
    }
    /* TODO: create the core dump file
     * - fork(2) the current process to create a child process
     * - within the child process, raise(3) the SIGABRT signal
     */

    if (remove_temp_dir(fn) == -1) // remove temp directory
    {
        print_err();
        return -1;
    }

    return 0;
}
