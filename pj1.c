pico /*****************************************************************
//
//  NAME:        Willard Peralta
//
//  HOMEWORK:    Project 1
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        February 28, 2018
//
//  FILE:        project1main.c
//
//  DESCRIPTION: Contains the user interface
//
//
****************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "record.h"
#include "db.h"

void displaymenu();
void chooseadd(struct record **);
void chooseprint(struct record *);
void choosedelete(struct record **);

int debugmode = 0;

/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   Main function, user interface
//
//  Parameters:    argc (int) : contains the number of arguments
//                 *argv char[] : argument vector
//
//  Return values:  0 : success
//
****************************************************************/

int main(int argc, char *argv[])
{
    char string1[8] = "debug";
    char* string2;
    int comparison;
    char input = NULL;
    int userchoice = 0;
    int done = 0;
    int readStatus = -1;
    char filename[] = "pj1.txt";
    struct record *start = NULL;

    if(argc > 2)
    {
     	string2 = argv[1];
        comparison = strcmp(string1, string2);
    }

    if(argc == 2 && comparison == 0)
    {
     	printf("\n***Program is running in debug mode.***\n");
        debugmode = 1;
    }
    else if(argc == 1)
    {
     	printf("\n");
    }
    else
    {
     	printf("\nOne argument expected\n");
    }

    readStatus = readfile(&start, filename);

    if(readStatus == 0)
    {
        printf("***File successfully read from %s***\n", filename);
    }
    else
    {
        printf("Error reading file named %s", filename);
    }

    do
    {
     	displaymenu();
        scanf("%s", &input);
        userchoice = atoi(&input);

        switch(userchoice)
        {
            case 1:
                chooseadd(&start);
                break;
            case 2:
                chooseprint(start);
                break;
            case 3:
                printAllRecords(start);
                break;
            case 4:
                choosedelete(&start);
                break;
            case 5:
                printf("\nExited program.\n");
                done = 1;
                break;
            default:
                printf("\nInvalid Input. Please enter a number between 1 and 5\n");
                break;
        }
    }while(done == 0);

    writefile(start, filename);
    printf("\n***Data saved to %s***\n", filename);

    return 0;
}

/*****************************************************************
//
//  Function name: displaymenu
//
//  DESCRIPTION:   Displays the menu options 1-5 and asks user to
//                 enter a number 1-5
//
//  Parameters:    none
//
//  Return values:  void
//
****************************************************************/

void displaymenu()
{

    if(debugmode == 1)
    {
     	printf("\n\n***displaymenu() function called***\n\n");
    }

    printf("\n****Bank Database Application****");
    printf("\n1. Add a new record");
    printf("\n2. Print a single record");
    printf("\n3. Print all records");
    printf("\n4. Delete a record");
    printf("\n5. Exit");
    printf("\nPlease enter a number between 1 and 5: ");
}

/*****************************************************************
//
//  Function name: chooseadd
//
//  DESCRIPTION:   asks user for account number, name and address
//                 and then passes them to  addRecord()
//
//  Parameters:    startingpoint (struct record *) : start of database
//
//  Return values:  void
//
****************************************************************/

void chooseadd(struct record **startingpoint)
{
    int accountNumber;
    char name[25];
    char address[80];

    if(debugmode == 1)
    {
     	printf("\n\n***chooseadd() function called***\n\n");
    }

    printf("\nEnter account number: ");
    scanf("%d", &accountNumber);
    getchar();

    printf("\nEnter Name: ");
    scanf("%[^\n]s", name);
    getchar();

    printf("\nEnter Address: ");
    getaddress(address, 80);

    addRecord(startingpoint, accountNumber, name, address);
    getchar();
    printf("\nThe record was added.\n");
}

/*****************************************************************
//
//  Function name: chooseprint
//
//  DESCRIPTION:   ask user for account number, then print out
//                 that record
//
//  Parameters:    startingpoint (struct record *) : start of database
//
//  Return values:  void
//
****************************************************************/

void chooseprint(struct record *startingpoint)
{
    int accountNumber;
    int status = -1;

    if(debugmode == 1)
    {
     	printf("\n\n***chooseprint() function called***\n\n");
    }

    printf("\nEnter account number: ");
    scanf("%d", &accountNumber);

    status = printRecord(startingpoint, accountNumber);

    if(status == -1)
    {
        printf("\nError, no such record.\n");
    }
}

/*****************************************************************
//
//  Function name: choosedelete
//
//  DESCRIPTION:   ask user for account number, then deletes that
//                 record
//
//  Parameters:    startingpoint (struct record *) : start of database
//
//  Return values:  void
//
****************************************************************/

void choosedelete(struct record **startingpoint)
{
    int accountNumber;
    int status = -1;

    if(debugmode == 1)
    {
        printf("\n\n***choosedelete() function called***\n\n");
    }

    printf("\nEnter account number: ");
    scanf("%d", &accountNumber);

    status = deleteRecord(startingpoint, accountNumber);
    
    if(status == 0)
    {
        printf("\nRecord deleted.\n");
    }
    else if(status == -1)
    {
        printf("\nRecord not found.\n");
    }
}

