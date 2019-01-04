#define _XOPEN_SOURCE
#include <cs50.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

// Tested on
/*
1        || 50Xu9TV42tQOg || 0.002s      || 3,420 possible passwords
al       || 507IH4BV0kgzc || 0.789s      || 324,900 possible passwords
RoR      || 50b5ILzBEDplw || 45.780s     || 30,865,500 possible passwords
Ruby     || 50VfakyL0ptK. || 4170.874s   || 2,932,222,500 possible passwords
Linux    || 50u8HReKZleek || 355826.965s || 278,561,137,500 possible passwords
*/



int main(int argc, string argv[]) {
    // Check for correct number of arguments.
    if (argc != 2) {
        printf("Invalid number of arguments.\n");
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
            // Check if password is found.
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
            // Increment next letter.
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