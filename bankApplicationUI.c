#include<stdio.h>
#include<stdlib.h>
#include"database.h"
#include<strings.h>
#include<string.h>
void getAddress (char [], int);

int debugMode;
/*****************************************************************
        Function name: main
//  //
//  //  DESCRIPTION:   This function prompts the user to make a choice
//  //  and then calls another function to execute the task. Once the
//  //  task is completed it continues to ask the user for to make a
//  //  selection until the user quits.
//  //
//  //  Parameters:    argc (int) : The number of elements in argv
//  //                 argv (char*[]) : An array of arguments passed
//  //                                  to the program.
//  //
//  //  Return values: 0 Code ran succesful and the user quit
//  //                 1 Invalid Usage
//  //
****************************************************************/

int main(int argc, char* argv[])
{
    struct record * start = NULL;
    int userEngages = 0;
    int accountno;
    char input[100];
    char name[100];
    char address[100];
    int addResult;
    int deleteResult;
    int findResult;
    int readResult;

    if (argc == 1)
    {
        debugMode = 0;
        printf("\n");
    }
    else if(argc > 1 && strcmp(argv[1], "debug") == 0)
    {
        debugMode = 1;
    }
     else
    {
        printf("Invalid Usage\n");
        return 1;
    }
    readResult = readfile(&start, "database.txt");
    if(readResult == -1)
    {
        printf("Error: Coud not load records\n");
    }

    printf("Welcome to ICS212 Bank, please be prepared to input your name, address and/or account number\n\n");
    while(userEngages == 0)
    {
        printf("\nPlease select one of the following options:\n");
        printf("add (a): Add a file to the database\n");
 printf("delete (d): Delete a file from the database using your account number\n");
        printf("find (f): Find a file using your account# \n");
        printf("printall (p): Print all the files in the database\n");
        printf("quit (q): Quit the program when you are finish\n");
        printf("Enter your choice: ");

        fgets(input, sizeof(input), stdin);
        input[strcspn(input,"\n")] = 0;

        if(strncasecmp(input, "add", strlen(input)) == 0)
        {
            printf("Enter account number: ");
            while(scanf("%d", &accountno) != 1 || accountno <= 0)
            {
                printf(" Please enter a valid account number\n");
                while (getchar() != '\n');
            }

            printf("Enter name: ");
            while (getchar() != '\n');
            fgets(name, sizeof(name), stdin);
            name[strcspn(name,"\n")] = 0;


            getAddress(address, sizeof(address));
            addResult = addRecord(&start, accountno, name, address);

            if(addResult == 0)
            {
                printf("The record has been succesfully added\n");
            }
            else if(addResult == -1)
            {
            printf("Error: Record already exists\n");
            fflush(stdout);
            }

        }

        else if(strncasecmp(input, "delete", strlen(input)) == 0)
        {
            printf("Enter the account #: ");
            while(scanf("%d", &accountno) != 1 || accountno <= 0)
            {
                printf("Please enter a valid account number\n");
                while (getchar() != '\n');
            }
            while (getchar() != '\n');
            deleteResult =  deleteRecord(&start, accountno);
            if(deleteResult == 0)
            {
                printf("The record was deleted\n");
            }
            else
            {
                printf("Error: Record not found.\n");
                fflush(stdout);
            }
        }
        else if(strncasecmp(input, "find", strlen(input))==0)
        {
            printf("Enter the account #: ");
            while(scanf("%d", &accountno) != 1 || accountno <= 0)
            {
                printf("Please enter a valid account number\n");
                while (getchar() != '\n');
            }
            while (getchar() != '\n');

            findResult =  findRecord(start, accountno);
            if(findResult == -1)
            {
                printf("Record could not be found \n");
            }
        }

        else if(strncasecmp(input, "printall", strlen(input))==0)
        {
            printf("Printing all records...\n");
            printAllRecords(start);
            fflush(stdout);
        }

        else if(strncasecmp(input, "quit", strlen(input))==0)
        {
            printf("Quitting the program\nHave a good day\n\n");
            fflush(stdout);
            if(writefile(start, "database.txt")==-1)
            {
                printf("**Warning no records saved OR no recordw could be recovered**\n\n");
                fflush(stdout);
            }
            userEngages = 1;
        }

        else
        {
            printf("Invalid Input //  (Quick commands:(a)(d)(f)(p))\n");
            fflush(stdout);
        }

    }
    return 0;
}
/*****************************************************************
//
////  Function name: getAddress
////
////  DESCRIPTION:   A function that collects the address from
////                 from the user as well as the size and returns
////                 it to the main function. Uses a fgets call
////                 and collects input until a % sign is reached. n
////
////
////  Parameters:
////  char address[] - character array for storring the provided address
////  int size - size of the address
////
////  Return values:
////
////
****************************************************************/


void getAddress (char address[], int size)
{

    char addy[100]; /* temp buffer */
    int currentLength = 0;
    int completed = 0;

    address[0] = '\0';
    printf("Enter Address(please press enter on a empty line when you have finished)\n");

    while(completed == 0 && currentLength < size-1)
    {
        fgets(addy, sizeof(addy), stdin);

        if(strcmp(addy, "\n") == 0)
        {
            completed = 1;
        }
        else
        {
            strncat(address, addy, size - currentLength - 1);
            currentLength = strlen(address);
            if(currentLength < size - 2)
            {
                strcat(address, " ");
                currentLength++;
            }
        }
        if (currentLength >= size - 1)
        {
            printf("Address is too long\n");
            completed = 1;
        }
    }
}
                                                                                                                                                                                                    241,1         Bot
