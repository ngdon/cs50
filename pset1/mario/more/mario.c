// A program that prints out a double half-pyramid of a specified height.

#include <stdio.h>
#include <cs50.h>

int main(void) {
    // Get pyramid height from user. Limit pyramid height to 23 units.
    int height;
    do {
        height = get_int("Pyramid height (max 23): ");
    } while (height > 23 || height < 0);

    // Print pyramid from top to bottom.
    // Small bug where when current_row = height, it will print an empty line. Subtract 1 from height to fix.
    for (int current_row = height - 1; current_row >= 0; current_row--) {

        // Print left half of pyramid.
        // Print spaces.
        for (int spaces = current_row; spaces > 0; spaces--) {
            printf(" ");
        }

        // Print blocks
        for (int blocks = height - current_row; blocks > 0; blocks--) {
            printf("#");
        }

        // Print space between the two halfs.
        printf("  ");

        // Print right half of pyramid.
        for (int right = 0; right < height - current_row; right++) {
            printf("#");
        }

        // Move to next line.
        printf("\n");
    }
}