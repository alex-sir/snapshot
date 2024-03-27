/**
 *  Alex Carbajal
 *  CPT_S 360, Spring 2024
 *  snapshot
 */

#include <libgen.h>       // for basename()
#include <sys/stat.h>     // for mkdir()
#include <sys/resource.h> // for setrlimit()

#include "snapshot.h"
#include "generate.h"
#include "helpers.h"

int snapshot(char *ssname, char *progpath, char *readme)
{
    const struct rlimit core_limit = {RLIM_INFINITY, RLIM_INFINITY};
    if (setrlimit(RLIMIT_CORE, &core_limit) == -1) // set unlimited core dump size
    {
        print_err();
        return -1;
    }

    if (mkdir(ssname, 0775) == -1) // create temp directory
    {
        print_err();
        return -1;
    }

    const char *progname = basename(progpath);
    // create all the files for the temp directory
    if (create_executable_copy(ssname, progname) == -1 ||
        create_core(ssname) == -1 ||
        create_readme(ssname, readme) == -1)
    {
        print_err();
        return -1;
    }

    if (create_tarball(ssname) == -1)
    {
        print_err();
        return -1;
    }

    if (remove_temp_dir(ssname) == -1)
    {
        print_err();
        return -1;
    }

    return 0;
}
