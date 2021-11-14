/** @author Nicolas Boeckh */

#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>

#include "digest.h"

/** Pipes the digested string to the output.
* @param str		The string to be digested
* @param digest		The digest name
* @param output		The pointer to the output array.
* @param strLen 	The length of the incoming string, useful because determining the length of { @param str } is less feasible from here.
*/
void digestThis(char str[], char digest[], char output[], long int strLen) {
	/** @see { man EVP_DigestInit } for most of this. */
	EVP_MD_CTX *md_ctx;
	const EVP_MD *md;
	unsigned char md_value[EVP_MAX_MD_SIZE];
	unsigned int md_len;

	md = EVP_get_digestbyname(digest);

	// If the digest is not correct, instead of erroring out, set a default digest (SHA1)
	if (md == NULL) {
		printf("%s\n", "Unknown digest, defaulting to SHA1");
		md = EVP_get_digestbyname("SHA1");
	}
	
	// Digest the message
	md_ctx = EVP_MD_CTX_new();
	EVP_DigestInit_ex(md_ctx, md, NULL);
	EVP_DigestUpdate(md_ctx, str, strLen);
	EVP_DigestFinal_ex(md_ctx, md_value, &md_len);
	EVP_MD_CTX_free(md_ctx);


	int i;
	output[0] = '\0';		// Default start to avoid weird chars (don't ask...)
	for (i = 0; i < md_len; i++) {
		char *value = (char*) malloc(2 * sizeof(char));
		sprintf(value, "%02x", md_value[i]);
		strncat(output, value, 2);
		free(value);
	}
	strncat(output, "\0", 1);

}


/** Gets the digest of the given sentence
* @param sentence   The sentence comprised of the given words
* @param digest     The name of the digest
*/
char * digestSentence(char sentence[], char digest[]) {
	char * output = malloc(MAX_DIGEST_SIZE * sizeof(char));
	digestThis(sentence, digest, output, strlen(sentence));
	return output;
}

/** Gets the digest of a given file at a given path
* @param file       The path of the file
* @param digest     The name of the digest
*/
char * digestFile(char file[], char digest[]) {
	char * buffer = 0;
	char * output = malloc(MAX_DIGEST_SIZE * sizeof(char));
	long length;
	FILE *f = fopen(file, "rb");

	// Read the binary content of the file.
	if (f) {
		fseek(f, 0, SEEK_END);
		length = ftell(f);
		fseek(f, 0, SEEK_SET);
		buffer = malloc(length + 1);
		
		// If the file exists
		if (buffer)
			fread (buffer, 1, length, f);
		buffer += '\0';
		fclose (f);
	}

	if (buffer)
		digestThis(buffer, digest, output, length);
	else
		output = "#facepalm... This isn't a file...";	// Else pipe a fun little message

	free(buffer);
	return output;
}
