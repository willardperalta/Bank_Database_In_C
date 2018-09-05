/*****************************************************************
//
//  NAME:        Willard Peralta
//
//  HOMEWORK:    Project 1
//
//  CLASS:	 ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        February 28, 2018
//
//  FILE:        db.c
//
//  DESCRIPTION: Contains the database functions used in project 1
//
//
****************************************************************/

#include "record.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern int debugmode;

/*****************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:   add a record to the database
//
//  Parameters:    starting (struct record **) : pointer to pointer of
//                 accountNum (int) : account number
//                 name (char[]) : name of user
//                 address (char[]) : address of user
//
//  Return values:  int
//
****************************************************************/

int addRecord(struct record **starting, int accountNum, char name[], char address[])
{
    struct record *temp = NULL;
    struct record *previous = NULL;
    struct record *current = NULL;
 
    temp = malloc(sizeof(struct record));
    current = *starting;

    if(debugmode == 1)
    {
     	printf("\n\n***addrecord() function called***\n\n");
        printf("\nParameters: accountNum: %d name: %s address: %s\n", accountNum, name, address);
    }
    
    temp->accountno = accountNum;
    strcpy(temp->name, name);
    strcpy(temp->address, address);
    temp->next = NULL;

    if(*starting == NULL)
    {
        *starting = temp;
    }

    else if(accountNum < current->accountno)
    {
        *starting = temp;
        temp->next = current;
    }
    
    else
    {
        while(current != NULL && current->accountno < accountNum)
        {
            previous = current;
            current = current->next;
        }

        temp->next = current;

        if(previous != NULL)
        {
            previous->next = temp; 
        }
    }

    return 0;
}

/*****************************************************************
//
//  Function name: printRecord
//
//  DESCRIPTION:   print a record using an account number
//
//  Parameters:    starting (struct record *) : pointer of record start
//                 accountNum (int) : account number
//
//  Return values: 0 : record found and printerd
//                -1 : record not found
//
****************************************************************/

int printRecord(struct record *starting, int accountNum)
{
    int status = -1;
    struct record *current = starting;
    struct record *temp = NULL;

    if(debugmode == 1)
    {
        printf("\n\n***printrecord() function called***\n\n");
        printf("\nParameters: accountNum: %d\n", accountNum);
    }

    if(starting != NULL)
    {
     	if(accountNum == current->accountno)
        {
            printf("\nRecord found: ");
            printf("\nAccountno: %d\n", current->accountno);
            printf("Name: %s\n", current->name);
            printf("Address: %s\n\n", current->address);
            current = NULL;
            status = 0;
        }

	while(current != NULL)
        {
            temp = current->next;

            if(accountNum == current->accountno)
            {
       	        printf("\nRecord found: ");
                printf("\nAccountno: %d\n", current->accountno);
                printf("Name: %s\n", current->name);
                printf("Address: %s\n\n", current->address);
                status = 0;
            }

            current = temp;

        }
    }

    return status;
}

/*****************************************************************
//
//  Function name: printAllRecords
//
//
//  DESCRIPTION:   print all records in database
//
//  Parameters:    starting (struct record *) : pointer of record start
//                 
//  Return values:  void
//
****************************************************************/

int printAllRecords(struct record *starting)
{

    struct record *current = starting;

    if(debugmode == 1)
    {
        printf("\n\n***printAllRecords() function called***\n\n");
    }

    if(current == NULL)
    {
        printf("\nThere are no records to print.\n");
    }

    else
    {
        printf("\nHere are all of the records:\n");

        while(current != NULL)
        {
            printf("\nAccountno: %d\n", current->accountno);
            printf("Name: %s\n", current->name);
            printf("Address: %s\n\n", current->address);
            current = current->next;
        }
     }

    return 0;
}

/*****************************************************************
//
//  Function name: deleteRecord
//
//  DESCRIPTION:   print a record using an account number
//
//  Parameters:    starting (struct record **) : pointer of pointer of record start
//                 accountNum (int) : account number
//
//  Return values:  0 : record found and deleted
//                 -1 : record does not exist and nothing deleted
//
****************************************************************/

int deleteRecord(struct record **starting, int accountNum)
{
    int status = -1;
    struct record *previous = NULL;
    struct record *current = *starting;
    struct record *temp = NULL;

    if(debugmode == 1)
    {
        printf("\n\n***deleterecord() function called***\n\n");
        printf("\nParameters: accountNum: %d\n", accountNum);
    }

    if(*starting != NULL)
    {

        if(accountNum == current->accountno)
        {    
            *starting = current->next;
            free(current);
            current = NULL;
            status = 0;
        }
    
        while(current != NULL)
        {
            temp = current->next;
        
            if(accountNum == current->accountno)
            {
                previous->next = temp;
                free(current);
                status = 0;
            }
        
            previous = current;
            current = temp;

        }
    }

    return status;
}

/*****************************************************************
//
//  Function name: getaddress
//
//
//  DESCRIPTION:   ask user for address with multiple lines
//
//  Parameters:    address (char[]) : array of address
//                 size (int) : size of address array
//
//  Return values:  void
//
****************************************************************/

void getaddress(char address[], int size)
{
    if(debugmode == 1)
    {
        printf("\n\n***getaddress() function called***\n\n");
        printf("\nParameters: address: %s size: %d\n", address, size);
    }


    printf("\nEnter the address no bigger than %d chars then press semicolon when done: ", size);
    scanf("%[^;]s", address);
}

/*****************************************************************
//
//  Function name: readfile
//
//
//  DESCRIPTION:   called at start of main to read database
//
//  Parameters:    starting (struct record**) : double pointer to start of databse
//                 filename (char[]) : array to store data read from file
//
//  Return values: int
//
****************************************************************/

int readfile(struct record **starting, char filename[])
{
    int status = -1;
    FILE *outfile = fopen(filename, "r");
    int accountNum = 0;
    char name[25];
    char address[80];
    char buffer[100];
    long size;

    if(debugmode == 1)
    {
        printf("\n\n***readfile() function called***\n\n");
        printf("\nParameters: filename: %s\n", filename);
    }

    if(outfile != NULL)
    {

        fseek(outfile, 0, SEEK_END);
        size = ftell(outfile);

        if(size == 0)
        {
            status = 0;
        }

        else
        {
            
            fseek(outfile, 0, SEEK_SET);

            while(fscanf(outfile, "%d", &accountNum) == 1)
            {
                fgets(buffer, 100, outfile);
                fscanf(outfile, "%[^\n]s", name);
                fgets(buffer, 100, outfile);
                fscanf(outfile, "%[^;]s", address);
                fgets(buffer, 100, outfile);
                addRecord(starting, accountNum, name, address);
            }
            status = 0;
         }
    }

    fclose(outfile);
    return status;
}

/*****************************************************************
//
//  Function name: writefile
//
//
//  DESCRIPTION:   call at end of main to store database into a file
//
//  Parameters:    starting (struct record*) : pointer to start of database  
//                 filename (char[]) : filename
//
//  Return values:  void
//
****************************************************************/

void writefile(struct record *starting, char filename[])
{
    struct record *current = starting;
    FILE *infile = fopen(filename, "w");

    if(debugmode == 1)
    {
        printf("\n\n***writefile() function called***\n\n");
        printf("\nParameters: filename: %s\n", filename);
    }

    if(current != NULL)
    {   
        if(infile != NULL)
        {
            while(current != NULL)
            {
                fprintf(infile, "%d\n", current->accountno);
                fprintf(infile, "%s\n", current->name);
                fprintf(infile, "%s;\n\n", current->address);
                current = current->next;
            }
         }    
     }

    fclose(infile);

}
