/*****************************************************************
//
// NAME: Jessica Ocampo
//
// HOMEWORK: Project1
//
// CLASS: ICS 212
//
// FILE: project1functions.c
//
// DESCRIPTION: This file contains the functions for project1
//
*****************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "record.h"

int addRecord (struct record **, int, char [ ],char [ ]);
int printRecord (struct record *, int);
void printAllRecords(struct record *);
int findRecords (struct record *, char [ ]);
int deleteRecord(struct record **, int);
int readfile(struct record **, char []);
int writefile(struct record *, char []);
void cleanup(struct record *);
void getaddress (char [ ], int);
 
int debug;
 
/*****************************************************************
//
// Function name: addRecord
//
// DESCRIPTION: Adds a record to the database
//
// Parameters: start (record **) : Pointer to start point of records
//              accountno (int) : account number of the record
//              name[] (char) : name of record
//              address[] (char) : address of record
//
// Return values: 1 : success
//                0 : record was not added
//
*****************************************************************/
 
int addRecord (struct record **start, int accountno, char name[], char address[])
{
    struct record *newRecord = malloc(sizeof(struct record));
    struct record *currentRecord = *start;
    int returnVal = 0;

    if (debug == 1)
	{
		printf("----- addRecord DEBUG ----- \n");
		printf("----- accountno : %d \n", accountno);
		printf("----- name : %s", name);
        printf("----- address : %s \n", address);
	}

    newRecord->accountno = accountno;
    strcpy(newRecord->name, name);
    strcpy(newRecord->address, address);
    newRecord->next = NULL;

    if (currentRecord == NULL)
    {
        *start = newRecord;
        returnVal = 1;
    }
    else
    {    
        while (currentRecord != NULL)
        {
            if (currentRecord->accountno == accountno)
            {
                break;
            }
            
            if (currentRecord->next == NULL)
            {
                currentRecord->next = newRecord;
                returnVal = 1;
                break;
            }

            currentRecord = currentRecord->next;
        }
    }
 
    return returnVal;
}
 
/*****************************************************************
//
// Function name: printRecord
//
// DESCRIPTION: Uses an account number to print out a record
//
// Parameters: start (record *) : Pointer to the first record in the database
//              accountno (int) : account number to search for
//
// Return values: 1 : successully found the record
//                0 : record not found
//
*****************************************************************/
 
int printRecord (struct record *start, int accountno)
{
    struct record *currentRecord = start;
    int returnVal = 0;

    if (debug == 1)
	{
		printf("----- printRecord DEBUG ----- \n");
		printf("----- accountno : %d \n", accountno);
	}

    if (currentRecord == NULL)
    {
        returnVal = 0;
    }
    else
    {
        while (currentRecord != NULL)
        {
            if(currentRecord->accountno == accountno)
            {
                printf("-------------\n");
                printf("Account No : %d\n", currentRecord->accountno);
                printf("Name : %s", currentRecord->name);
                printf("Address : %s", currentRecord->address);
                printf("-------------\n");
                returnVal = 1;
                break;
            }
        currentRecord = currentRecord->next;
        }
    }

    return returnVal;
}
  
/*****************************************************************
//
// Function name: printAllRecords
//
// DESCRIPTION: prints all records in the database
//
// Parameters: start (record *) : Pointer to the first record in the database
//
// Return values: void
//
*****************************************************************/
 
void printAllRecords(struct record *start)
{
    struct record *currentRecord = start;

    if (debug == 1)
	{
		printf("----- printAllRecords DEBUG -----\n");
	}

    printf("Printing all records...\n");
     
    if (currentRecord == NULL)
    {
        printf("No records available.\n");
    }
    else
    {
        while (currentRecord != NULL)
        {
            printf("-------------\n");
            printf("Account No : %d\n", currentRecord->accountno);
            printf("Name : %s", currentRecord->name);
            printf("Address : %s", currentRecord->address);
            printf("-------------\n");
            currentRecord = currentRecord->next;
        }
    }
}

/*****************************************************************
//
// Function name: findReocrds
//
// DESCRIPTION: Finds all records in the database starting with a given string
//
// Parameters: start (record *) : Pointer ot the first record in the database
//             name[] (char) : substring to check for
//
// Return values: 1 : records were found starting with the string
//                0 : no records found
//
*****************************************************************/
 
int findRecords(struct record *start, char name[])
{
    struct record *currentRecord = start;
    int returnVal = 0;

    if (debug == 1)
	{
		printf("----- findRecords DEBUG ----- \n");
		printf("----- name : %s \n", name);
	}

    while (currentRecord != NULL)
    {
        if (strncmp(name, currentRecord->name, strlen(name) - 1) == 0)
        {
            printf("-------------\n");
            printf("Account No : %d\n", currentRecord->accountno);
            printf("Name : %s", currentRecord->name);
            printf("Address : %s", currentRecord->address);
            printf("-------------\n");
            returnVal = 1;
        }
        currentRecord = currentRecord->next;
    }

    return returnVal;
}
 
/*****************************************************************
//
// Function name: deleteRecord
//
// DESCRIPTION: Deletes a record in the database with the provided account number
//
// Parameters: start (record **) : Pointer to the pointer of the first record in the database
//              accountno (int) : which account to be deleted
//
// Return values: 1 : record was deleted
//                0 : no record was deleted
//
*****************************************************************/
 
int deleteRecord(struct record **start, int accountno)
{
    struct record *temp = *start, *prev;
    int returnVal = 0;

    if (debug == 1)
	{
		printf("----- deleteRecord DEBUG -----  \n");
		printf("----- accountno : %d ----- \n", accountno);
	}
    
    while (temp != NULL && temp->accountno == accountno)
    {
        *start = temp->next;  
        free(temp);               
        temp = *start;  
        returnVal = 1;       
    }
    while (temp != NULL)
    {
        while (temp != NULL && temp->accountno != accountno)
        {
            prev = temp;
            temp = temp->next;
        }
        if (temp == NULL)
        {
             returnVal = 0;
             break;
        }
        prev->next = temp->next; 
        free(temp); 
        temp = prev->next;
        returnVal = 1;
    } 
    return returnVal;   
 }

 /*****************************************************************
//
// Function name: readfile
//
// DESCRIPTION: Reads records from a text file
//
// Parameters: start (record **) : Pointer to the pointer of the first record in the database
//              filename[] (char) : file to be read from
//
// Return values: 1 : records were read in
//                0 : no records were read in
//
*****************************************************************/

int readfile(struct record **start, char filename[])
{
    FILE *readFileIn;
    char name[25], address[100], buffer[400];
    int accountno;
    int getAddress = 0;
    int returnVal = 0;
     
    if (debug == 1)
	{
		printf("----- readfile DEBUG ----- \n");
		printf("----- filename : %s \n", filename);
	} 
     
    readFileIn = fopen(filename, "r");
     
    if (readFileIn == NULL)
    {
        returnVal = 0;
    }
    else
    {
        while (fgets(buffer, 400, readFileIn) != NULL)
        {
            if (getAddress == 0)
            {
                accountno = atoi(buffer);
                fgets(buffer, 400, readFileIn);
                strcpy(name, buffer);
                fgets(buffer, 400, readFileIn);
                fseek(stdin, 0, SEEK_END);
                getAddress = 1;
            }

            if (getAddress == 1)
            {
                if (buffer[strlen(buffer) - 2] == '^')
                {
                    strcat(address, buffer);
                    getAddress = 0;
                    addRecord(start, accountno, name, address);
                    strcpy(address, "");
                    returnVal = 1;
                    continue;
                }
                else
                {
                    strcat(address, buffer);
                    fseek(stdin, 0, SEEK_END);
                }
            }
        }
        fclose(readFileIn);
    }
     
    return returnVal;
}

/*****************************************************************
//
// Function name: writefile
//
// DESCRIPTION: Writes records out to a text file
//
// Parameters: start (record **) : Pointer to the pointer of the first record in the database
//              filename[] (char) : file to be written to
//
// Return values: 1 : records were written
//                0 : no records were written
//
*****************************************************************/

int writefile(struct record *start, char filename[])
{
    struct record *currentRecord = start;
    int returnVal = 0;
    FILE *writeFileOut;
    writeFileOut = fopen(filename, "w");

    if (debug == 1)
	{
		printf("----- writefile DEBUG ----- \n");
		printf("----- filename : %s \n", filename);
	}   

    while (currentRecord != NULL)
    {
        fprintf(writeFileOut, "%d\n", currentRecord->accountno);
        fprintf(writeFileOut, "%s", currentRecord->name);
        fprintf(writeFileOut, "%s", currentRecord->address);
        currentRecord = currentRecord->next;
        returnVal = 1;
    }
 
    fclose(writeFileOut);

    return returnVal;
}

/*****************************************************************
//
// Function name: cleanup
//
// DESCRIPTION: deletes all records and allocates space on the heap
//
// Parameters: start (record *) : Pointer to the record in the database
//
// Return values: void
//
*****************************************************************/

void cleanup(struct record *start)
{
    struct record *temp = NULL;

    if (debug == 1)
	{
		printf("----- cleanup DEBUG ----- \n");
	}   

    while (start != NULL)
    {
        temp = start;
        start = start->next;
        free(temp);
    }
}
 
/*****************************************************************
//
// Function name: getAddress
//
// DESCRIPTION: Gathers user input for the address
//
// Parameters: array (char *) : Points to the address array
//             lineChars (int) : how large the array is
//
// Return values: void
//
*****************************************************************/
 
void getaddress (char *address, int lineChars)
{
    char str[100];

    if (debug == 1)
    {
        printf("----- getAddress DEBUG ----- \n");
        printf("----- lineChars : %d\n", lineChars);
    }   
     
    printf("Enter the address of the account : \n");
    printf("Include '^' at the end to indicate the end of the address : \n ");

    strcpy(address, "");
    while (fgets(str, 99, stdin))
    {
        fseek(stdin, 0, SEEK_END);
        if (str[strlen(str) - 2] == '^') {
            strcat(address, str);
            fseek(stdin, 0, SEEK_END);
            break;
        }
        else
        {
            strcat(address, str);
        }
    }
    strcpy(str, "");
}