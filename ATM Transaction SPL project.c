/*
 Structured Programming Laboratory
 [[[[ Project File ]]]]

 Project name :    C Program to Display the ATM Transaction

 Program    :    BSc in CSE
 Semester   :    2nd
 Section    :    C1
 Session    :    Spring 2022
 Group No.  :    05
 ID's       :    1) 2104010202230 - Anik Barua
                 2) 2104010202242 - Pankaj Rudra
                 3) 2104010202268 - Ram Prashad Das Kanto
                 4) 2104010202269 - Md. Tyeb Hossain

 SUBMITTED TO :
 ==============
 Mohammad Hasan
 (Lecturer, Department of CSE,
 Premier University)

 Submission Date : 26th September, 2022

 [modified after submission]

 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

unsigned long amount = 1000, deposit, withdraw, opening;
int choice, pin, pass_lim = 5, i;
char transaction = 'y';
char ch_in;
char del_history;
FILE *fp1, *fp2, *Log;

// Function to display transaction menu
void displayMenu() {
    printf("\n\t\t\t######### WELCOME to ATM Service #########\n");
    printf("\t\t\t\t1. Check Balance\n");
    printf("\t\t\t\t2. Withdraw Cash\n");
    printf("\t\t\t\t3. Deposit Cash\n");
    printf("\t\t\t\t4. Withdrawal History\n");
    printf("\t\t\t\t5. Deposit History\n");
    printf("\t\t\t\t6. Clear All Transaction\n");
    printf("\t\t\t\t7. Quit\n");
    printf("\t\t\t##########################################\n");
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("\t\t\tDate and time: %02d-%02d-%02d %02d:%02d:%02d\n\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

// Function to validate PIN
int validatePin() {
    int attempts = 0;
    while (pin != 123 && attempts < pass_lim) {
        printf("ENTER YOUR SECRET PIN NUMBER : ");
        scanf("%d", &pin);
        if (pin != 123) {
            attempts++;
            printf(" PLEASE ENTER VALID PASSWORD!\n [] Remaining try : %d\n\n", pass_lim - attempts);
        }
    }
    return (pin == 123);
}

// Function to handle withdrawal transaction
void performWithdrawal() {
    printf("\n ENTER THE AMOUNT TO WITHDRAW: ");
    scanf("%lu", &withdraw);

    while (withdraw % 100 != 0) {
        printf("\n\t\t ! PLEASE ENTER THE AMOUNT IN MULTIPLES OF 100\n");
        printf("\n ENTER THE AMOUNT TO WITHDRAW: ");
        scanf("%lu", &withdraw);
    }

    if (withdraw > (amount - 500)) {
        printf("\n\t\t INSUFFICIENT BALANCE !!!\n [] Your Account Must Contain at least 500 Tk.");
    } else {
        opening = amount;
        amount = amount - withdraw;
        printf("\n\n\t\t CASH OUT SUCCESSFUL. PLEASE COLLECT CASH");
        printf("...");

        // writing transaction history in file
        fp1 = fopen("WithdrawalHistory.txt", "a+");
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        fprintf(fp1, "Date and time => %02d-%02d-%02d %02d:%02d:%02d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
        fprintf(fp1, "Opening : \t%lu BDT\n", opening);
        fprintf(fp1, "Withdrawal : \t%lu BDT\n", withdraw);
        fprintf(fp1, "Closing : \t%lu BDT\n", amount);
        fprintf(fp1, "-----------------------------------------\n");
        fclose(fp1);
        printf("\n\t\t [] YOUR CURRENT BALANCE IS : %lu", amount);
    }
}

// Function to handle deposit transaction
void performDeposit() {
    printf("\n ENTER THE AMOUNT TO DEPOSIT : ");
    scanf("%lu", &deposit);
    opening = amount;
    amount = amount + deposit;
    fp2 = fopen("DepositHistory.txt", "a+");
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    fprintf(fp2, "Date and time => %02d-%02d-%02d %02d:%02d:%02d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
    fprintf(fp2, "Opening : \t%lu BDT\n", opening);
    fprintf(fp2, "Deposit : \t%lu BDT\n", deposit);
    fprintf(fp2, "Closing : \t%lu BDT\n", amount);
    fprintf(fp2, "-----------------------------------------\n");
    fclose(fp2);
    printf("\n\n\t\tDeposit Successful!\n\t\tYOUR BALANCE IS : %lu Tk.", amount);
}

// Function to handle withdrawal history
void displayWithdrawalHistory() {
    fp1 = fopen("WithdrawalHistory.txt", "r");
    printf("\n\n\t\tWithdrawal History : \n\t===================================\n");
    if (fp1 == NULL)
        printf("\t\tNO RECORD FOUND !\n");
    else {
        while (!feof(fp1)) {
            ch_in = fgetc(fp1);
            if ((int)ch_in == 255)
                break;
            printf("%c", ch_in);
        }
        fclose(fp1);
    }
}

// Function to handle deposit history
void displayDepositHistory() {
    fp2 = fopen("DepositHistory.txt", "r");
    printf("\n\n\t\tDeposit History : \n\t================================\n");
    if (fp2 == NULL)
        printf("\tNO RECORD FOUND !\n");
    else {
        while (!feof(fp2)) {
            ch_in = fgetc(fp2);
            if ((int)ch_in == 255)
                break;
            printf("%c", ch_in);
        }
        fclose(fp2);
    }
}

int main() {
    // PIN input section (Validation)
    if (validatePin()) {
        int continueTransaction = 1;
        do {
            system("cls");
            displayMenu();

            // User choice section
            printf("Enter your choice: ");
            scanf("%d", &choice);

            // User choice result section
            switch (choice) {
                case 1:
                    printf("\n\t\t YOUR CURRENT BALANCE IS : %lu BDT", amount);
                    break;
                case 2:
                    performWithdrawal();
                    break;
                case 3:
                    performDeposit();
                    break;
                case 4:
                    displayWithdrawalHistory();
                    break;
                case 5:
                    displayDepositHistory();
                    break;
                case 6:
                    printf("\nARE YOU SURE DELETE ALL HISTORY? (y/n) : ");
                    scanf(" %c", &del_history);
                    if (del_history == 'y' || del_history == 'Y') {
                        fp1 = fopen("WithdrawalHistory.txt", "w");
                        fclose(fp1);
                        fp2 = fopen("DepositHistory.txt", "w");
                        fclose(fp2);
                        printf("\n\t\t\t[] History Deletion Successful !");
                    }
                    break;
                case 7:
                    printf("\n\t\t EXITING FROM ATM...");
                    continueTransaction = 0;
                    break;
                default:
                    printf("\n\t\t ! INVALID CHOICE");
            }

            // Asking user to choose another transaction
            if (continueTransaction) {
                printf("\n\n\nDO YOU WISH TO HAVE ANOTHER TRANSACTION?(y/n) : ");
                scanf(" %c", &transaction);
                continueTransaction = (transaction == 'y' || transaction == 'Y' || transaction == 49);
            }
        } while (continueTransaction);

        printf("\n\n\t\t--------------------------------");
        printf("\n\t\t# THANKS FOR USING OUR SERVICE #");
        printf("\n\t\t--------------------------------");
    } else {
        printf("\n\t\t YOU HAVE EXCEEDED PASSWORD LIMIT!\n");
    }

    return 0;
}
