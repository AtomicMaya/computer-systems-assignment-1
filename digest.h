/** @author Nicolas Boeckh */

#ifndef HEADER_DIGEST
#define HEADER_DIGEST
#define MAX_DIGEST_SIZE 129

/** Gets the digest of a given file at a given path
* @param file       The path of the file
* @param digest     The name of the digest
*/
char * digestFile(char file[], char digest[]);

/** Gets the digest of the given sentence
* @param sentence   The sentence comprised of the given words
* @param digest     The name of the digest
*/
char * digestSentence(char sentence[], char digest[]);

#endif