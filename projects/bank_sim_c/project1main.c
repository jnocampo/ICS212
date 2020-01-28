/*****************************************************************
//
// NAME: Jessica Ocampo
//
// HOMEWORK: Project 1
//
// CLASS: ICS 212
//
//
// FILE: project1main.c
//
// DESCRIPTION: Project 1 driver code, containing the main function and collects user data
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
// Function name: main
//
// DESCRIPTION: Collects user input and supplies them to database functions
//
// Parameters: arc (int) : number of arguments supplied
//			   argv (* char) : what arguments were suplplied
//
// Return values: 1 : success
//
*****************************************************************/ 

int main (int argc, char *argv[]) {
	char userInput[25], compareString[25], accountNum[25], name[50], findName[50], address[100];
	int accountNumber, wrongArgs = 0;
	
	struct record *start = NULL;

	if (argc > 2)
    {
		printf("Too many arguments provided.\n");
		printf("Try ./project1 or ./project1 debug\n");
		printf("Exiting...\n");
		wrongArgs = 1;
	}

    if (argc > 1)
    {
        if (strcmp(argv[argc - 1], "debug") == 0)
	    {
            debug = 1;
		    printf("----- Debug mode on -----\n");
        }
        else
        {
            printf("Unknown argument supplied\n");
		    printf("Try ./project1 debug instead\n");
		    printf("Exting...\n");
		    wrongArgs = 1;
        }
    }

    if (wrongArgs == 0)
    {
        if (readfile(&start, "output.txt") == 1)
        {
            printf("Reading in records out text file.\n");
        }
        else
        {
            printf("No records read in from file.\n");
        }

        printf("Add a new record, type : add\n");
        printf("Print a record, type : print\n");
        printf("Print all records, type : all\n");
        printf("Find a record, type : find\n");
        printf("Delete records, type : delete\n");
        printf("To quit, type : quit\n");

	    printf("Enter a command\n");
	    printf("---------------\n");
    
	
	    while(fgets(userInput, 25, stdin))
	    {
		    sscanf(userInput, "%s", compareString);
		
		    if(strncmp(compareString, "add", 3) == 0)
		    {
			    if (debug == 1)
			    {
				    printf("----- starting addRecord ----- \n");
			    }

			    printf("Adding a record : \n");
			    printf("Enter account number :  \n");
                printf("Please enter a valid integer or the system will default the account number to 0 :\n");

			    fgets(accountNum, 24, stdin);
			    accountNumber = atoi(accountNum);
			    /* look for end of stream	*/
			    fseek(stdin, 0, SEEK_END);
			
			    printf("Enter name of account owner :  \n");

			    fgets(name, 49, stdin);	
			    fseek(stdin, 0, SEEK_END);
			
			    getaddress(address, 100);

			    if (addRecord(&start, accountNumber, name, address) == 1)
                {
                    printf("New record successfully added!\n");
                }
                else
                {
                    printf("Duplicate entry, record not added to the database.\n");
                }

			    /* resets address array	*/
			    strcpy(address, "");		
		    }
		    else if (strncmp(compareString, "print", 5) == 0)
		    {
			    if (debug == 1)
			    {
				    printf("----- starting printRecord ----- \n");
			    }

			    printf("Enter the account number to print information :\n");

			    fgets(accountNum, 24, stdin);
			    accountNumber = atoi(accountNum);
			
			    if (printRecord(start, accountNumber) != 1)
                {
                    printf("Record not found.\n");
                };			
		    }
		    else if (strncmp(compareString, "all", 3) == 0)
		    {
			    if (debug == 1)
			    {
				    printf("----- starting printAllRecords ----- \n");
			    }

			    printAllRecords(start);
		    }
		    else if (strncmp(compareString, "find", 4) == 0)
		    {
			    if (debug == 1)
			    {
				    printf("----- starting findRecords ----- \n");
			    }

			    printf("Enter name to find records :\n");

			    fgets(findName, 49, stdin);
			
			    if (findRecords(start, findName) != 1)
                {
                    printf("No records found starting with : %s \n", name);
                };					
		    }
		    else if (strncmp(compareString, "delete", 5) == 0)
		    {
			    if (debug == 1)
			    {
				    printf("----- starting deleteRecords ----- \n");
			    }

			    printf("Enter the account number to delete records :\n");			
			    fgets(accountNum, 24, stdin);
			    accountNumber = atoi(accountNum);

			    if (deleteRecord(&start, accountNumber) == 1)
                {
                    printf("Sucessfully deleted record!\n");
                }
                else
                {
                    printf("No record found with account number : %d\n", accountNumber);
                }
		    }
		    else if (strncmp(compareString, "quit", 4) == 0)
		    {
			    break;
		    }
		    else
		    {
		    printf("Invalid menu item, please try again.\n");
		    }
		    printf("Enter a command\n");
		    printf("---------------\n");
	    }
        printf("Writing out database to output.txt\n");
        if (writefile(start, "output.txt") == 1)
        {
            printf("Sucessfully wrote records to text file...\n");
        }
        else
        {
            printf("No records wrote out to text file.\n");
        }
        cleanup(start);
	    printf("Qutting program..\n");
    }
	return 1;
}