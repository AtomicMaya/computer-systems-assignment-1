/** @author Nicolas Boeckh */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "argsGetter.h"
#include "digest.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        fprintf(stderr, "Insufficient number of arguments.\nUsage: %s [-f] word1 word2 ... [-t digest]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    Args *args = getArgs(argc, argv);
    int i;
    
    // Assume that a digest doesn't exceed 255 chars.
    char *fDigest = (char*) malloc(sizeof(char[255]));
    // Assume that your sentence isn't composed of more words than were written, and that no words are larger than 255 chars.
    char *sentence = (char*) malloc(args->size * sizeof(char[255]));
    
    if (args->isFiles == 1) {
        for (i = 0; i < args->size; i++) {
            fDigest = digestFile(args->words[i], args->digest);
            printf("%s\t%s\n", fDigest, args->words[i]);
        }
    } else {
        // Since all the words are fragmented, concatenate them into a sentence.
        for (i = 0; i < args->size; i++) {
            strncat(sentence, args->words[i], 255);
            if (i != args->size - 1)
                strncat(sentence, " ", 1);
        }
        printf("\r%s\t%s\n", digestSentence(sentence, args->digest), sentence);
        
    }

    // Deallocate memory.
    free(fDigest);
    free(sentence);
    free(args);
	return 0;
} 