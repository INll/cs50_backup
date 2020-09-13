// Implements Luhn’s Algorithm to verify potential credit card numbers of either
// Amex, Visa or Mastercard origin. Able to identify invalid numbers.

#include <cs50.h>
#include <stdio.h>
#include <math.h>

long get_crednum(void);

int main(void)
{
    long num = get_crednum();
    long ph3 = num;
    long ph4 = num;
    int length = 1;

    while (ph3 /= 10)
    {
        length++;
//        printf("Length: %i\n", length);
    }
    // Numbers of neither of the following lengths will be rejected.
    if (length != 13 && length != 15 && length != 16 && length != 19)
    {
        printf("INVALID\n");
    }
    else
    {
        int ph1;
        int ph2;
        int total;
        int sum1 = 0;
        int sum2 = 0;

        // Extracts the every last-digit number, from right to left.
        for (int i = 0; i < length; i++)
        {
            // If odd, execute. Else, add to sum2.
            if (i % 2 != 0)
            {
                ph1 = 0;
                ph2 = 0;
                // Checks if the digit's >=5 as only they yield 2-digit products.
                if (num % 10 >= 5)
                {
                    ph1 = num % 10;
                    ph1 *= 2;
                    // Extracts the two digits, then add to sum1.
                    for (int j = 0; j < 2; j++)
                    {
                        ph2 += ph1 % 10;
                        ph1 /= 10;
                    }
                    sum1 += ph2;
                }
                // Extracts <5 numbers, multiply by 2 then add to sum1.
                else
                {
                    ph1 = num % 10;
                    ph1 *= 2;
                    sum1 += ph1;
                }
            }
            else
            {
                ph2 = num % 10;
                sum2 += ph2;
            }
            // Truncate the number string by one digit.
            num /= 10;
        }
        // A number is valid if the last digit of 'total' is 0.
        total = sum1 + sum2;
//        printf("%i\n", total);
        if (total % 10 != 0)
        {
            printf("INVALID\n");
        }
        else
        {
            long ph5;

            // Extarcts the first or first two digits for identifying brands.
            for (int k = 2; k < length; k++)
            {
                // ph4 stores the first two digits of a card number.
                ph4 /= 10;
            }
            ph5 = ph4;
            // ph5 stores the first digit of a card number.
            ph5 /= 10;
//            printf("%li\n", ph4);
            if ((ph4 == 37 || ph4 == 34) && (length == 15))
            {
                printf("AMEX\n");
            }
            else if ((ph5 == 4) && (length == 13 || length == 16 || length == 19))
            {
                printf("VISA\n");
            }
            // The following new line is made for aesthetic reasons. Unfortunately
            // Style50 doesn't accept this and will -0.01 point for this. To get
            // 1.00 undo the new line.
            else if ((ph4 == 51 || ph4 == 52 || ph4 == 53 || ph4 == 54 ||
            ph4 == 55) && (length == 16))
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
    }
}

// Prompts user for input. Ensures input is a positive integer.
long get_crednum(void)
{
    long input;
    long chked_num;
    int length = 1;

    do
    {
        length = 1;
        input = get_long("Number: ");
        chked_num = input;
    }
    while (input <= 0);

    return chked_num;
}