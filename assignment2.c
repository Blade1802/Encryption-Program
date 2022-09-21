/*
    Program Description : Program to verify a security code. This program accepts a code entered by the user and encrypts and verifies it with a set code.
                          It asks user to choose an option from the given menu. It executes that option.
                          Each option is made in a seperate function where parameters are only passed by reference.
                          After executing the option, it brings you back to the menu and asks for your choice again.
                          It continues this until the user selects Option '5' (Exit Program) which asks for user's confirmation to exit and then terminates the program.
                          This program is made for a college assignment.
    Author              : Aayush Gaur
    Student Number      : C20396243 
    Date                : 20-02-2021
*/

#include <stdio.h>

#define SIZE 4          // Number of digits in the Code
#define NONE 0          // State of the Code: If nothing has been entered in the code yet
#define NEWCODE 1       // State of the Code: If the code has just been entered and no Encryption has been done yet
#define DECRYPTED 2     // State of the Code: If the code is in its Decrypted form
#define ENCRYPTED 3     // State of the Code: If the code is in its Encrypted form
#define CORRECT 0       // If the code entered match the Access Code
#define INCORRECT 1     // If the code entered does not match the Access Code

// Function signatures
void enter_code(int *);
void encrypt_verify(int *, int *, int *);
void decrypt(int *);
void display_count(int *, int *);
int exit_program(void);

int main(void)
{

    // Declaring variables
    char temp;                               // Temporary variable to flush out the extra characters in the input
    char option = '0';                       // Option chosen by the user from the menu

    int code[SIZE + 1] = {0, 0, 0, 0, NONE}; // Code entered by the user, last memory stores the current state of the code (None or Encrypted or Decrypted)
    int correctCount = 0;                    // To count the number of times the Code was entered correctly
    int incorrectCount = 0;                  // To count the number of times the Code was entered incorrectly
    int extra = 0;                           // To check if there are extra characters entered

    printf("\n\n");

    while (1)
    {
        printf("1. Enter any code\n");
        printf("2. Encrypt code entered and verify if correct\n");
        printf("3. Decrypt code\n");
        printf("4. Display the number of times the encrypted code entered matches the authorised code (i) Successfully (ii) Incorrectly\n");
        printf("5. Exit Program\n");

        printf("\nPlease enter your choice\n");

        scanf("%c", &option);

        while ((temp = getchar()) != '\n') // Flushes the extra characters after the first character
            extra++;                       // Counts if user enters more than 1 character

        if (extra != 0)
        {
            extra = 0;  // Resetting extra to 0 for the next test
            option = 0; // So that the default case executes
        }

        printf("\n");

        switch (option)
        {
            case '1':
            {
                enter_code(code);
                break;

            } // End of case '1'

            case '2':
            {
                encrypt_verify(code, &correctCount, &incorrectCount );
                break;

            } // End of case '2'

            case '3':
            {
                decrypt(code);   
                break;

            } // End of case '3'

            case '4':
            {
                display_count(&correctCount, &incorrectCount);
                break;

            } // End of case '4'

            case '5':
            {
                if (exit_program())
                {
                    printf("\nExiting Program...\n\n");
                    return 0;
                }
                break;

            } // End of case '5'

            default:
            {
                printf("Invalid Input! Please try again!");
                break;

            } // End of default

        } // End of switch

        printf("\n\n------------------------------------------------------------------------------------------------------------------------\n\n");
        option = 0; // Resetting option to 0 for the next input

    } // End of while

} // End of main



// Function enter_code() will ask and store a 4-digit code entered by the user
void enter_code(int *code)
{
    char temp;      // Temporary variable to flush out the extra characters in the input
    char digit;     // To store each digit of the code for error handling

    int check = 0;  // To check if 4 digits are entered or not
    int extra = 0;  // To check if there are more than 4 characters entered

    int flag = 0;   // Error Handling Variable. It has 3 states:
                    // 0: No error detected (4 digits are entered followed by a newLine)
                    // 1: Exit due to character entered not being a digit
                    // 2: Exit due to newline character entered before entering the 4-digit code

    while (1)
    {
        printf("Please enter a 4-digit code\n");

        // Loop to accept 4-digit code
        for(int i = 0; i < SIZE; i++)
        {
            scanf("%c", &digit);
            
            if (digit == '\n')  // Checks if the user presses enter before entering 4 digits
            {
                flag = 2;   // Exit due to newline character entered before entering the 4-digit code
                break;

            } // End of if

            else if (digit < '0' || digit > '9') // Checks if the digit entered is not number 
            {
                flag = 1;   // Exit due to character entered not being a digit
                break;

            } // End of else if

            else
            {
               *(code + i) = digit - '0'; // Converts the number from character ('0') to integer (0)

            } // End of else

        } // End of for

        // Only executes if the loop has exited due to a newline being entered before entering 4 digits
        if (flag != 2)
        {
            // Loop to count for extra character and also to clean input buffer
            while ((temp = getchar()) != '\n')
                extra++;

        } // End of if

        // Executes if the loop has finished without any errors and exactly 4 digits are entered
        if (flag == 0 && extra == 0)
        {
            printf("\nCode Successfully Entered");
            *(code + 4) = NEWCODE; // Sets State of Code to Decrypted
            break;

        } // End of if

        else
        {
            printf("\nInvalid Input! Please only enter 4 single-digit integers (0-9) in the format (1234)\n");
            printf("Try again!\n\n");
            *(code + 4) = NONE; // Sets State of Code to None
            flag = 0;           // Resetting flag to 0 for the next test
            extra = 0;          // Resetting extra to 0 for the next test

        } // End of else

    } // End of while

} // End of enter_code()



// Function encrypt_verify() encrypts the code and verify it with the access_code.
// It only encrypts the code only if the code is a new code entered by the user (i.e decrypted).
// It does not allow the user to verify the same code more than once.
void encrypt_verify(int *code, int *correctcount, int *incorrectcount)
{
    const int access_code[SIZE] = {4, 5, 2, 3}; // Access Code
    int temp;                                   // Temporary variable to store the digits of the code
    int i;                                      // For loops
    int flag = CORRECT;                         // To check if the Code Entered matches the Access Code

    if (*(code + 4) == NEWCODE)
    {
        // Swapping 1st and 3rd digits
        temp = *(code + 0);
        *(code + 0) = *(code + 2);
        *(code + 2) = temp;

        // Swapping 2nd and 4th digits
        temp = *(code + 1);
        *(code + 1) = *(code + 3);
        *(code + 3) = temp;

        // For loop to increment each digit by 1 and changes any digit that has a value of 10 to 0 
        for (i = 0; i < SIZE; i++)
        {
            *(code + i) = *(code + i) + 1;

            if (*(code + i) == 10)
            {
                *(code + i) = 0;

            } // End of if

        } // End of for

        printf("Your encrypted code is: ");

        for (i = 0; i < SIZE; i++)
        {
            printf("%d", *(code + i));

        } // End of for

        *(code + 4) = ENCRYPTED;    // Sets State of Code to Encrypted
    

        printf("\n\nVerifying...\n\n");

        // For loop to check if every digit of the Entered Code is the same as the Access Code
        for (i = 0; i < SIZE; i++)
        {
            if (*(code + i) != *(access_code + i))
            {
                flag = INCORRECT;
                break;

            } // End of if

        } // End of for

        if (flag == CORRECT)
        {
            printf("Correct Code Entered");
            *correctcount = *correctcount + 1;

        } // End of if
        else
        {
            printf("Wrong Code Entered");
            *incorrectcount = *incorrectcount + 1;

        } // End of else

    } // End of if

    else if (*(code + 4) == ENCRYPTED)
    {
        printf("The Code is already Encrypted! Returning to the Main Menu...");

    } // End of else if

    else if (*(code + 4) == DECRYPTED)
    {
        printf("You have already verified this code once before! Returning to the Main Menu...");

    } // End of else if

    else
    {
        printf("Please enter a valid code first! Returning to the Main Menu...");

    } // End of else if

} // End of encrypt_verify()



// Function decrypt() decrypts the code. It only decrypts the code only if the code is encrypted.
void decrypt(int *code)
{
    int temp;   // Temporary variable to store the digits of the code
    int i;      // For loops

    if (*(code + 4) == ENCRYPTED)
    {
        // For loop to decrement each digit by 1 and changes any digit that has a value of -1 to 9 
        for (i = 0; i < SIZE; i++)
        {
            *(code + i) = *(code + i) - 1;

            if (*(code + i) == -1)
            {
                *(code + i) = 9;

            } // End of if

        } // End of for

        // Swapping 1st and 3rd digits
        temp = *(code + 0);
        *(code + 0) = *(code + 2);
        *(code + 2) = temp;

        // Swapping 2nd and 4th digits
        temp = *(code + 1);
        *(code + 1) = *(code + 3);
        *(code + 3) = temp;

        printf("Your decrypted code is: ");

        for (i = 0; i < SIZE; i++)
        {
            printf("%d", *(code + i));

        } // End of for

        *(code + 4) = DECRYPTED;    // Sets State of Code to Decrypted

    } // End of if

    else if (*(code + 4) == DECRYPTED || *(code + 4) == NEWCODE )
    {
        printf("The Code is already Decrypted! Returning to the Main Menu...");

    } // End of else if

    else
    {
        printf("Please enter a valid Code first! Returning to the Main Menu...");

    } // End of else

} // End of decrypt()



// Function display_count() is used to display the number of times the code of entered 1) Successfully 2) Incorrectly
void display_count(int *correctcount, int *incorrectcount)
{
    printf("Number of times the Code was entered :\n");
    printf("Successfully = %d\n", *correctcount);
    printf("Incorrectly  = %d", *incorrectcount);
}



// Funtion exit_program() is to ask for confirmation from the user, if he wants to exit or not.
int exit_program(void)
{
    char ans;       // To store user's choice [Y/N]
    char temp;      // Temporary variable to flush out the extra characters in the input
    int extra = 0;  // To check if there are extra characters entered

    while (1)
    {
        printf("Are you sure you want to exit? [Y/N]\n");
        ans = getchar();

        while ((temp = getchar()) != '\n') // Flushes the extra characters after the first character
            extra++;                       // Counts if user enters more than 1 character

        if (extra != 0)
        {
            extra = 0; // Resetting extra to 0 for the next test
            ans = 'a'; // So that the else gets executed if the user enters more than 1 charater instead of just Y/N
        }
        

        if (ans == 'y' || ans == 'Y')
        {
            return 1;

        } // End of if

        else if (ans == 'n' || ans == 'N')
        {
            printf("\nReturning to Main Menu...");
            return 0;

        } // End of else if

        else
        {
            printf("\nInvalid Input! Please only enter:\n");
            printf("\'Y\' for Yes\n");
            printf("\'N\' for No\n\n");

        } // End of else

    } // End of while

} // End of exit_program()