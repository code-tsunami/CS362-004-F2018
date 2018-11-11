/*
 * Sonam Kindy
 * CS362
 * Colors to be used for passed/failed output of unit tests to more easily read results
 * as well as macros to pass to a custom assert func that takes as one of the params the
 * type of comparison to make (i.e. >= or <=).
 * Created: 10/25/18
 * Ref: https://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c
*/

#ifndef UNITTESTS_H

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define LESS_THAN_OR_EQUAL       0
#define GREATER_THAN_OR_EQUAL    1

#endif