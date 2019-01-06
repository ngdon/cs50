// Helper functions for music

#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
// Assuming that denominator is always a power of 2, so no check for that.
int duration(string fraction)
{
    int numerator = atoi(strtok(fraction, "/"));
    int denominator = atoi(strtok(NULL, "/"));
    if (denominator == 8) {
        return numerator;
    } else if (denominator > 8) {
        return numerator / (denominator / 8);;
    } else {
        return numerator * (8 / denominator);;
    }

}

int GetNoteSemitone(string note) {
    int semitone;
    switch(note[0]) {
        case 'B':
            semitone = 2;
            break;
        case 'A':
            semitone = 0;
            break;
        case 'G':
            semitone = -2;
            break;
        case 'F':
            semitone = -4;
            break;
        case 'E':
            semitone = -5;
            break;
        case 'D':
            semitone = -7;
            break;
        case 'C':
            semitone = -9;
            break;
    }
    if (strlen(note) == 2) {
        switch(note[1]) {
            case 'b':
                semitone--;
                break;
            case '#':
                semitone++;
                break;
        }
    }
    return semitone;
}

// Calculates frequency (in Hz) of a note
// WARNING: For some reason when using either "octave" or "octave_delim" in strtok, "octave_delim" is lost!!!
int frequency(string note)
{
    // Calculate number of semitones from A4 by:
    // 1) Calculate number of semitones from note to A.
    // 2) Calculate number of octaves away from 4, multiply by 12 to get semitones.
    // Add number of semitones from note to A, and semitones from octave to 4.

    // First split input "note" into the note and octave.
    const string octave_delim = &note[strlen(note)-1]; // Octave will always be the last character in the string.
    char octave[2]; // Bug with strtok where the delimiting byte is lost so we need an extra copy.

    // The length of octave should be 1, (0-8 octaves). If it is bigger then program will overflow.
    if (strlen(octave) > 1) {
        return 1;
    } else {
        strcpy(octave, octave_delim);
    }

    const string raw_note = strtok(note, octave_delim); // Raw note will always be whatever is left of the octave.

    const double octave_semitone = (strtod(octave, NULL) - 4) * 12; // There are 12 semitones between one octave.
    double semitones = GetNoteSemitone(raw_note) + octave_semitone;

    const double frequency = pow(2, (semitones/12)) * 440; // 2^(n/12) * 440;
    return round(frequency);


}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (strcmp(s, "") == 0) return true;
    else return false;
}
