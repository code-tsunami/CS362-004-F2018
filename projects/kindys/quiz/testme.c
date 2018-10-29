/*
 * Sonam Kindy
 * CS362
 * Random Testing Quiz
 * Created: 10/26/18
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define NUM_INPUT_CHARS     13
#define STR_LEN             6   /* room for null terminator */

/* define int array of characters' ASCII values */
int asciiInputPool[NUM_INPUT_CHARS] = {
    '[',
    '(',
    '{',
    ' ',
    'a',
    'x',
    '}',
    ')',
    ']',
    'r',
    'e',
    's',
    't'
};

/* Function: Get random index of asciiInputPool and return char at that index */
char inputChar()
{
    return asciiInputPool[rand() % NUM_INPUT_CHARS];
}

/* Function: Generate random 5-letter string and return it */
char* inputString()
{
    char* str = (char*)malloc(STR_LEN * sizeof(char)); /* dynamically allocate mem  */
    memset(str, '\0', STR_LEN); /* set all characters to null terminator */
    /* for indices 0..4 of char arr (need to leave room for null terminator) */
    for(int i = 0; i < STR_LEN - 1; i++)
        str[i] = inputChar();
    return str;
}

void testme()
{
    int tcCount = 0;
    char* s;
    char sCopy[STR_LEN];
    char c;
    int state = 0;
    while(1) {
        tcCount++;
        c = inputChar();
        s = inputString();
        printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

        if (c == '[' && state == 0) state = 1;
        if (c == '(' && state == 1) state = 2;
        if (c == '{' && state == 2) state = 3;
        if (c == ' '&& state == 3) state = 4;
        if (c == 'a' && state == 4) state = 5;
        if (c == 'x' && state == 5) state = 6;
        if (c == '}' && state == 6) state = 7;
        if (c == ')' && state == 7) state = 8;
        if (c == ']' && state == 8) state = 9;

        /* copy s contents returned from inputString call to sCopy */
        memcpy(sCopy, s, STR_LEN * sizeof(char));
        free(s); // free dynamically alloc memory in inputString
        
        /* if the string generated by inputString == reset and the state == 9 
         * exit with status code 200 */
        if (sCopy[0] == 'r' && sCopy[1] == 'e'
            && sCopy[2] == 's' && sCopy[3] == 'e'
            && sCopy[4] == 't' && sCopy[5] == '\0'
            && state == 9) {
            printf("ERROR; s = %s\n", sCopy);
            exit(200);
        }
    }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
