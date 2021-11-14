/** @author Nicolas Boeckh */

#ifndef HEADER_ARGS
#define HEADER_ARGS
#define THEORETICAL_MAX_PATH_LENGTH 4096    // Linux max path length. Win is 260

/** Struct representing the arg structure.
* @param size       Contains the amount of words / files in the args.
* @param isFiles    Whether the args are files or just words.
* @param digest     The specified digest  (default SHA1)
* @param words      Container for words / files
*/
typedef struct  {
    int size;
    int isFiles;
    char digest[12];
    char words[][255];
} Args;

/** Gets the arguments container relative to the input
* @param argc   The number of arguments given to the program
* @param argv   The arguments provided
*/
Args * getArgs(int argc, char *argv[]);

#endif