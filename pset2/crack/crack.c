/**
 * Program that uses a brute force method to cracks passwords assuming:
 * 1. Password has been hashed using C's DES-based 'crypt' function.
 * 2. Password is no longer than 5 characters.
 * 3. Passwords are composed entirely of alphabetical characters (uppercase and/or lowercase).
 *
 * Results:
 * anushree:50xcIMJ0y.RXo   |   0.191s  | YES
 * brian:50mjprEcqC/ts      |   0.004s  | CA
 * bjbrown:50GApilQSG3E2    |
 * lloyd:50n0AAUD.pL8g      |
 * malan:50CcfIk1QrPr6      |
 * maria:509nVI8B9VfuA      |   0.005s  | TF
 * natmelo:50JIIyhDORqMU    |   16.381s | nope
 * rob:50JGnXUgaafgc        |   6.252s  | ROFL
 * stelios:51u8F0dkeDSbY    |   0.007s  | NO
 * zamyla:50cI2vYkF0YU2     |   0.124s  | LOL
 */

#define _XOPEN_SOURCE
#include <cs50.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>


int main(int argc, string argv[]) {
    // Check for correct number of arguments.
    if (argc != 2) {
        printf("Invalid number of arguments. Usage: ./crack hash\n");
        return 1;
    }

    const string hash_pwd = argv[1];

    // Take the first two characters as the salt.
    char salt[3];
    salt[0] = hash_pwd[0];
    salt[1] = hash_pwd[1];
    salt[2] = '\0';

    // Assume passwords are 5 characters long.
    const int pwd_len = 5;
    char pwd[pwd_len+1]; // +1 to account for null character.
    for (int i = 0; i < pwd_len; i++) {
        // Initialize guess password.
        for (int j = 0; j <= i; j++) {
            pwd[j] = 'A';
        }
        pwd[i+1] = '\0';
        bool end = false;
        do {
            // Increment left most character and check hash.
            for (int guess = 'A'; guess <= 'z';) {
                pwd[0] = guess;
                const string guess_hash = crypt(pwd, salt);
                if (strcmp(guess_hash, hash_pwd) == 0) {
                    printf("%s\n", pwd);
                    return 0;
                }
                if (guess == 'Z') {
                    guess = 'a';
                } else {
                    guess++;
                }
            }
            // Increment characters to the right.
            for (int k = 1; k > 0;) {
                switch(pwd[k]) {
                    // Reached end of lowercase range, go back to uppercase range.
                    case 'z':
                        pwd[k] = 'A';
                        k++;
                        break;
                    // Reached end of uppercase range, go to lowercase range.
                    case 'Z':
                        pwd[k] = 'a';
                        k = -1;
                        break;
                    // Reached end of password. Password must be longer.
                    case '\0':
                        // Exit out of guessing loop and increase password by one character.
                        end = true;
                        k = -1;
                        break;
                    // Have not reached end of password, uppercase, or lowercase range. Increment to next letter.
                    default:
                        pwd[k]++;
                        k = -1;
                }
            }

        } while (!end);
    }

    return 1;
}