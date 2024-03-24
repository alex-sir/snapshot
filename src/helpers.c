/**
 *  Alex Carbajal
 *  CPT_S 360, Spring 2024
 *  snapshot
 */

#include "helpers.h"

void print_err(void)
{
    fprintf(stderr, "Error: %s\n", strerror(errno));
}
