#include <osbind.h>
#include <stdio.h>
#include "input.h"

/* ----- Function: has_input -----

Purpose:
Checks if a key is waiting in the keyboard buffer.

Input:
None

Output:
true  → key available
false → no key
*/

bool has_input(void) {
    return (Cconis() != 0);
}


/* ----- Function: get_input -----

Purpose:
Gets the next key from the keyboard buffer.

Input:
None

Output:
ASCII character of key pressed
*/

char get_input(void) {
    return (char)Cnecin();
}
