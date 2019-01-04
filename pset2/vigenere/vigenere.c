// A program that encrypts messages using Vigenere's cipher.
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[]) {
    // Should only have two arguments.
    if (argc != 2) {
        printf("Invalid number of arguments.\n Usage: ./vigenere k\n");
        return 1;
    } else {
        // Check that the second argument is valid.
        for (int i = 0, len = strlen(argv[1]); i < len; i++) {
            if (!isalpha(argv[1][i])) {
                printf("Invalid input argument. Argument must be composed of only alphabetical characters.\nUsage: ./vigenere k\n");
                return 1;
            } else {
                // If second argument is valid, convert all letters to lowercase.
                argv[1][i] = tolower(argv[1][i]);
            }
        }
    }

    // Save argument into variable to make it easier to read.
    const string key = argv[1];

    // Prompt user for phrase to be encoded.
    const string plaintext = get_string("Plaintext: ");

    // Save length of plaintext string and key.
    const int plain_len = strlen(plaintext);
    const int key_len = strlen(key);

    // Initialize ciphertext.
    char ciphertext[plain_len+1]; // Add one for null character.
    ciphertext[plain_len] = '\0'; // Indicate end of string with null character.

    // Initialize key iterator.
    int key_itr = 0;

    // Implement cipher:
    // c_i = (p_i + k_j) mod 26;
    for (int i = 0; i < plain_len; i++) {
        // Only encode alphabetical characters.
        if (isalpha(plaintext[i])) {
            // Reset key iterator if it has reached the end of the key.
            if (key_itr == key_len) {
               key_itr = 0;
            }
            const int key_offset = key[key_itr] - 'a';
            if (isupper(plaintext[i])) {
                const int plain_offset = plaintext[i] - 'A';
                const char cipher_char = ((plain_offset + key_offset) % 26) + 'A';
                ciphertext[i] = cipher_char;
            } else if (islower(plaintext[i])) {
                const int plain_offset = plaintext[i] - 'a';
                const char cipher_char = ((plain_offset + key_offset) % 26) + 'a';
                ciphertext[i] = cipher_char;
            }
            key_itr++;
        } else {
                ciphertext[i] = plaintext[i];
        }
    }

    // Output ciphertext.
    printf("ciphertext: %s\n", ciphertext);



}