/** @author Nicolas Boeckh */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "argsGetter.h"

/** Gets options specified after -f [multiple] and -t
* @param argc   The number of arguments given to the program
* @param argv   The arguments provided
* @param args   The struct containing the arguments { @see argsGetter.h }
*/
void getParams(int argc, char *argv[], Args *args) {
    char opt;           // Current option
    int counter = 0;    // A counter for the number of words / files 
    int offset = 0;     // An offset value

    // While there are opts in the arguments
    while ((opt = getopt(argc, argv, "f:t:")) != -1) {
        offset = optind - 1;

        switch(opt) {
            case 'f':   // If files are specified
                args->isFiles = 1;
                optind--;
                
                // For all args that aren't another digest
                for( ;optind < argc && *argv[optind] != '-'; optind++){
                    // Add to the next element in the array.
                    strncpy(args->words[optind - offset], argv[optind], THEORETICAL_MAX_PATH_LENGTH);
                    counter++;
                }
                
                args->size = counter; // Define the amount of words / files given.
                break;
            case 't':   // If a digest is specified
                strncpy(args->digest, optarg, 12);
                break;
            default:    // Wrong usage case, exit out.
                fprintf(stderr, "Usage: %s [-f] word1 word2 ... [-t digest]\n", argv[0]);
                exit(EXIT_FAILURE);
                break;
        }
    }

    // Redundancy : If the digest name is not specified, set SHA1.
    if (*args->digest == '\0') {
        strncpy(args->digest, "SHA1", 12);
    }
}

/** Gets arbitrary words if the file options isn't specified
* @param argc   The number of arguments given to the program
* @param argv   The arguments provided
* @param args   The struct containing the arguments { @see argsGetter.h }
*/
void getWords(int argc, char *argv[], Args *args) {
    int index;          // Current iteration index
    int counter = 0;    // A counter for the number of words / files 
    
    for (index = 1; index < argc; index++) {
        if (argv[index][0] != '-') {       // If the argument is not an option.
            strncpy(args->words[counter], argv[index], 255);
            counter++;
        } else
            index += 1;     // Skip -t param
    }
    args->size = counter;  // Define the amount of words / files given.
}

/** Gets the arguments container relative to the input
* @param argc   The number of arguments given to the program
* @param argv   The arguments provided
*/
Args * getArgs(int argc, char *argv[]) {
    Args *args;
    args = malloc(argc * sizeof(char[THEORETICAL_MAX_PATH_LENGTH]) + // Amount of words
                    sizeof(char[12]) +       // Max size of a digest  
                    2 * sizeof(int));        // Both ints in the struct.
    
    // By default, get the parameters.
    getParams(argc, argv, args);
    
    // If it isn't a collection of filenames, the words should be collected in a similar manner.
    if (args->isFiles != 1)
        getWords(argc, argv, args);

    return args;
}

