/**
 *  Alex Carbajal
 *  CPT_S 360, Spring 2024
 *  snapshot
 */

#include "generate.h"
#include "helpers.h"

#include <sys/stat.h> // for mkdir()

int snapshot(char *fn, char *progpath, char *readme)
{
    if (mkdir(fn, 0775) == -1) // create temp directory
    {
        print_err();
        return -1; // failed to create temp directory
    }

    return 0;
}
