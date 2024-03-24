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
 * - create a temp directory of name fn ($)
 * - create an executable copy of the binary code of the current running executable
 *   - the name of the executable is the basename(3) of progpath
 * - create a core dump of the current program
 * - create a README.txt file containing the contents of the readme string
 *   - if readme doesn't end in '\n', append it to the file
 * - create a tarball containing the executable, core dump, and README.txt
 * - remove the temp directory of name fn
 *   - first, remove all the files within it
 *   - then, remove the directory
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
    snprintf(executable_copy_path, sizeof(executable_copy_path), "%s/%s", fn, progname);
    
    if (create_executable_copy(executable_copy_path) == -1)
    {
        print_err();
        return -1;
    }
    /* TODO: create the core dump file
     * - fork(2) the current process to create a child process
     * - within the child process, raise(3) the SIGABRT signal
     */

    if (remove_temp_dir(fn, executable_copy_path) == -1) // remove temp directory
    {
        print_err();
        return -1;
    }

    return 0;
}
