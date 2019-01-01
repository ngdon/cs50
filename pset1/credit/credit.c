// Program that determines whether a provided credit card number is valid according to Luhn's algoritm.
#include <stdio.h>
#include <cs50.h>

// Takes a credit card number and returns true if the number passes Luhn's algorithm.
bool VerifyCreditNumber(long long credit_card_num);

// Takes a credit card number and returns the type of card it is as a string.
string GetCreditType(long long credit_card_num);

int main(void) {
    // First, get user's credit card number.
    // Using long long which is 64 bits long to have enough room to store up to 18 digits.
    long long credit_card_num = get_long_long("Credit card number: ");

    // Check if credit card number is valid and print the card type if the number is valid.
    if (VerifyCreditNumber(credit_card_num)) {
        printf("%s\n", GetCreditType(credit_card_num));
    } else {
        printf("Invalid credit card number.\n");
    }
}

bool VerifyCreditNumber(long long credit_card_num) {
    // CheckSum algorithm:
    // 1. Multiply every other digit by 2, starting with the number's second-to-last digit, then add those products' !!digits!!
    // together.
    // 2. Add the sum to the sum of the digits that weren't multiplied by 2.
    // 3. If the total's last digit is 0 (modulo 10 is 0) the number is valid.

    int not_doubled_sum = 0;
    int doubled_sum = 0;
    for (int i = 0; credit_card_num > 0; i++) {
        // If the digit is the 1st, 3rd, 5th...
        if (i%2 == 0) {
            // Add the digit to the sum of digits not doubled.
            not_doubled_sum+=credit_card_num%10;
            // Remove the digit that was just added.
            credit_card_num/=10;
        }
        // If the digit is the 2nd, 4th, 6th..
        if (i%2 == 1) {
            // Double the digit.
            int digit = (credit_card_num%10 * 2);
            // Add the digits of the doubled digit above together.
            while (digit > 0) {
                doubled_sum+=digit%10;
                digit/=10;
            }
            // Remove the digit that was just added.
            credit_card_num/=10;
        }
    }
    if ((not_doubled_sum + doubled_sum)%10 == 0) {
        // Credit card number is valid if last number is a 0.
        return true;
    } else {
        return false;
    }
}

string GetCreditType(long long credit_card_num) {
    // American Express numbers all start with 34 or 37.
    // MasterCard numbers start with 51, 52, 53, 54, or 55.
    // Visa numbers start with 4.

    // Strip all the digits except for the first two.
    do {
        credit_card_num/=10;
    } while (credit_card_num > 100);

    switch (credit_card_num) {
        case 34 :
        case 37 :
            return "American Express";
            break;
        case 51 :
        case 52 :
        case 53 :
        case 54 :
        case 55 :
            return "MasterCard";
            break;
        default :
            // Check if the first digit is a 4.
            if (credit_card_num/10 == 4) {
                return "Visa";
            } else {
                return "Invaid credit card number.";
            }
    }
}