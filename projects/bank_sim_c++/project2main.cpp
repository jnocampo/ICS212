/*****************************************************************
//
// NAME: Jessica Ocampi
//
// HOMEWORK: Project 2
//
// CLASS: ICS 212
//
//
// FILE: project2main.cpp
//
// DESCRIPTION: Driver code for Project 2
//
****************************************************************/
 
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <sstream>
#include <cstdio>
#include "record.h"
#include "llist.h"
 
#ifndef DEBUG 
#define DEBUG 0
#endif
 
using namespace std;

int addRecord (int, char [ ],char [ ]);
int printRecord (int);
int findRecords (char [ ]);
int deleteRecord(int);
int readfile();
int writefile();
void reverse();
void getaddress (char [ ]);

/*****************************************************************
//
// Function name: main
//
// DESCRIPTION: Collects user input in a loop and allows the user
//              to access all the database commands
//
// Parameters: arc (int) :
//             argv (* char) : 
//
// Return values: 1 : success
//
 *****************************************************************/
 
int main (int argc, char *argv[])
{
    llist *start = new llist("output.txt");
    char userInput[25], stringCompare[25], name[50], findName[50], address[100];
    int accountno;

    
    #if DEBUG == 1
        cout << "------------- Debug Mode On ------------- " << endl;
    #endif
    
     
    cout << "Add a new record, type : add" << endl;
    cout << "Print a record, type : print" << endl;
    cout << "Print all records, type : all" << endl;
    cout << "Find a record, type : find" << endl;
    cout << "Delete records, type : delete" << endl;
    cout << "Reverse records, type : reverse" << endl;
    cout << "To quit, type : quit" << endl;

	cout << "Enter a command" << endl;
	cout << "---------------" << endl;
 
    while(cin >> userInput)
    {
        strcpy(stringCompare, userInput);
         
        if (strncmp(stringCompare, "add", 3) == 0) 
        {
            #if DEBUG == 1
                cout << "----- Starting addRecord -----" << endl;
            #endif

            cout << "Adding a record..." << endl;
            cout << "Enter account number : ";
            cin >> accountno;
            cout << endl;
            fseek(stdin, 0, SEEK_END);
                        
            /* flush newline char out */
            getchar();
             
            cout << "Enter name of account owner :  ";
            cin.getline(name, sizeof(name));
            cout << endl;
            fseek(stdin, 0, SEEK_END);

            getaddress(address);
                         
            if (start->addRecord(accountno, name, address) != 1)
            {
                cout << "Duplicate entry, not adding to the database." << endl;
            }
             
            strcpy(address, "");           
        }
        else if (strncmp(stringCompare, "print", 5) == 0)
        {
            #if DEBUG == 1
                cout << "----- Starting printRecord -----" << endl;
            #endif

            cout << "Enter the account number to print information :";
            cin >> accountno;
            cout << endl;
            fseek(stdin, 0, SEEK_END);

            /* flush newline char out */
            getchar();
             
            if (start->printRecord(accountno) != 1)
            {
                cout << "Record not found." << endl; 
            }
        }
        else if (strncmp(stringCompare, "all", 3) == 0)
        {
            #if DEBUG == 1
                cout << "----- Starting printAll -----" << endl;
            #endif

            cout << *start << endl;
        }
        else if (strncmp(stringCompare, "find", 4) == 0)
        {
            #if DEBUG == 1
                cout << "----- Starting findRecord -----" << endl;
            #endif

            /* flush newline char out */
            getchar();

            cout << "Enter name to find records : ";
            cin.getline(findName, 49);
            cout << endl;
             
            fseek(stdin, 0, SEEK_END);
             
            if (start->findRecords(findName) != 1)
            {
                cout << "No reocrds with name : " << findName << endl;
            }
        }
        else if (strncmp(stringCompare, "delete", 6) == 0)
        {
            #if DEBUG == 1
                cout << "----- Starting deleteRecord -----" << endl;
            #endif

            cout << "Enter the account number to delete records :";
            cin >> accountno;
            cout << endl;
             
            fseek(stdin, 0, SEEK_END);
             
            if (start->deleteRecord(accountno) == 1)
            {
                cout << "Successfully delete record!" << endl;
            }
            else
            {
                cout << "No record found with account number : " << accountno << endl;
            }
        }
        else if (strncmp(stringCompare, "reverse", 7) == 0)
        {
            #if DEBUG == 1
                cout << "----- Starting reverseRecord -----" << endl;
            #endif

            cout << "Reversing records..." << endl;
            start->reverse();
        }
        else if (strncmp(stringCompare, "quit", 4) == 0) 
        {
            cout << "Program is now exiting." << endl;
            break;
        }
        else
        {
            cout << "Invalid menu item, please try again." << endl;
        }
        cout << "Enter a command" << endl;
	    cout << "---------------" << endl;
    }
    cout << "Qutting program and cleaning up records..." << endl;
    start->~llist();
    return 1;
}