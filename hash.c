/*
Compile:
for main {
    gcc -o hash hash.c -lcrypto
}
else {
    gcc -c hash.c -o hash.o
}
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h> // for EVP hash_with_evp function


// Function to generate the hash of a password using SHA256 algorithm
// Returns a dynamically allocated string containing the hash
char* hash(const char* password) {

    // Set up the SHA256 context and initialize it
    EVP_MD_CTX* mdctx = EVP_MD_CTX_new(); // Create new EVP_MD_CTX structure
    if (mdctx == NULL) {
        return NULL; // Error handling: return NULL if memory allocation fails
    };
    const EVP_MD* md = EVP_sha256(); // Get the SHA256 digest method object
    EVP_MD_CTX_init(mdctx); // Initialize the context
    EVP_DigestInit_ex(mdctx, md, NULL); // Initialize the digest operation

    // Update the context with the password string
    EVP_DigestUpdate(mdctx, password, strlen(password));

    // Generate the hash and store it in a buffer
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;
    EVP_DigestFinal_ex(mdctx, hash, &hash_len);

    // Convert the binary hash to a hex string
    char* output = (char*)malloc(hash_len * 2 + 1); // + 1 for the null-terminator
    // char* output = new char[hash_len * 2 + 1]; // no new expression in c have to use malloc
    if (output == NULL) {
        EVP_MD_CTX_free(mdctx); // Free the context before returning NULL
        return NULL; // Error handling: return NULL if memory allocation fails
    };
    for (int i = 0; i < hash_len; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]); // %02x means print the hexadecimal number with 2 digits, if the number is less than 2 digits, then print 0 before the number and x parameter means print the hexadecimal number in lowercase
    };
    output[hash_len * 2] = '\0'; // Null-terminate the string

    // Clean up and return the hash
    EVP_MD_CTX_free(mdctx); // Free the context
    return output;
};

int main() {
    char* a = hash("hello");
    printf("%s", a);

    return 0;
}