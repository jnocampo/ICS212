/*****************************************************************
*
* NAME: Jessica Ocampo
*
* HOMEWORK: Project 2
*
* CLASS: ICS 212
*
* FILE: llist.cpp
*
* DESCRIPTION: Defines functions for project 2
*
*****************************************************************/
 
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <sstream>
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
void printAll();
void getaddress (char [ ]);
 
/*****************************************************************
//
// Function name: readfile
//
// DESCRIPTION: Reads records from a text file
//
// Parameters: none
//
// Return values: 1 : records were read in
//                0 : no records were read in
//
*****************************************************************/
 
int llist::readfile(void)
{   
    char name[25], address[100], end_address[100];
    int accountno, returnVal;
    int getName = 1;
    int getAccountNo = 1;
    int getAddress = 1;
    ifstream infile;
    string read_in_line;
    
    #if DEBUG == 1
        cout << "----- DEBUG readfile ----- " << endl;
    #endif
    
    infile.open(filename);

    if (!infile.is_open())
    {
        returnVal = 0;
    }
    else
    {
        cout << "Reading in records from output.txt..." << endl;
        while (getline(infile, read_in_line))
        {
            #if DEBUG == 1
                cout << "In getLine : " << read_in_line << endl;
            #endif

            if (getAccountNo == 1)
            {
                accountno = atoi(read_in_line.c_str());
                getAccountNo = 0;
                continue;
            }

            if (getName == 1)
            {
                strcpy(name, read_in_line.c_str());
                getName = 0;
                continue;
            }

            if (getAddress == 1)
            {
                strcpy(end_address, read_in_line.c_str());

                if (end_address[strlen(end_address) - 1] == '^')
                {
                    strcat(address, read_in_line.c_str());
                    addRecord(accountno, name, address);
                    getAccountNo = 1;
                    getName = 1;
                    getAddress = 1;
                    returnVal = 1;
                    strcpy(end_address, "");
                    strcpy(address, "");
                    continue;
                }
                else
                {
                    strcat(address, read_in_line.c_str());
                    strcat(address, "\n");
                    continue;
                }

            }
        }
    }
    
    infile.close();
    return returnVal;
}
 
/*****************************************************************
//
// Function name: writefile
//
// DESCRIPTION: Writes records out to a text file
//
// Parameters: void
//
// Return values: void
//
*****************************************************************/
 
void llist::writefile(void)
{   
    struct record *current_record = start;
    int returnVal = 0;
    ofstream outfile;
    
    #if DEBUG == 1
        cout << "----- DEBUG writefile -----" << endl;
    #endif

    outfile.open("output.txt");
     
    while (current_record != NULL)
    {
        outfile << current_record->accountno << endl;
        outfile << current_record->name << endl;
        outfile << current_record->address << endl;
        current_record = current_record->next;
        returnVal = 1;
    }
     
    outfile.close();
}
 
/*****************************************************************
//
// Function name: reverse
//
// DESCRIPTION: Reverse the link list, first record is in the back and the last
// record is in the front 
//
// Parameters: reocrd (record *) : Pointer to last record passed in
//
// Return values: record : recurses to the next record in the list
//
//****************************************************************/
 
record* llist::reverse(record* record)
{
    #if DEBUG == 1
        cout << "----- DEBUG writefile -----" << endl;
        cout << "record * : " << record << endl;
    #endif
     
    if (record->next != NULL)
    {
        (reverse(record->next))->next = record;
        record->next = NULL;
    }
    else
    {
        start = record;
    }
     
    return record;
}
 
/*****************************************************************
//
// Function name: cleanup
//
// DESCRIPTION: deletes all records and allocates space on the heap
//
// Parameters: void
//
// Return values: void
//
*****************************************************************/
 
void llist::cleanup(void)
{   
    struct record **pointer_start = &start;
    struct record *current_record = *pointer_start;
     
    #if DEBUG == 1
        cout << "----- DEBUG cleanup -----" << endl;
    #endif
     
    while (current_record != NULL)
    {
        *pointer_start = current_record->next;
        delete current_record;
        current_record = *pointer_start;
    }
}
 
/*****************************************************************
//
// Function name: llist
//
// DESCRIPTION: Creates an llist object
//
// Parameters: void
//
// Return values: void
//
*****************************************************************/
 
llist::llist(void) 
{
    #if DEBUG == 1
        cout << "----- DEBUG llist constructor -----" << endl;
        cout << "New llist object made" << endl;
    #endif
}
 
/*****************************************************************
//
// Function name: llist
//
// DESCRIPTION: Creates an llist object
//
// Parameters: filename[] (char) : Reads in file to create llist
//
// Return values: void
//
*****************************************************************/
 
llist::llist(char filename[])
{
    #if DEBUG == 1
        cout << "----- DEBUG llist constructor -----" << endl;
        cout << "New llist object made" << endl;
        cout << "filename : " << filename << endl;
    #endif
 
    start = NULL;
    strcpy(this->filename, filename);
    readfile();
}
 
/*****************************************************************
//
// Function name: ~llist
//
// DESCRIPTION: Destructor function, writes records out and cleans them up
//              from the heap
//
// Parameters: void
//
// Return values: void
//
 *****************************************************************/
 
llist::~llist(void)
{
    #if DEBUG == 1
        cout << "----- DEBUG llist destructor -----" << endl;
        cout << "llist object being destroyed" << endl;
    #endif
     
    writefile();
    cleanup();
}
 
/*****************************************************************
//
// Function name: addRecord
//
// DESCRIPTION: Adds a record to the database
//
// Parameters:  accountno (int) : account number of the record
//              name[] (char) : name of record
//              address[] (char) : address of record
//
// Return values: 1 : success
//                0 : record was not added
//
*****************************************************************/
 
int llist::addRecord (int accountno, char name[], char address[])
{
    struct record **pointer_start = &start;
    struct record *current_record = *pointer_start;
    struct record *new_record = new struct record;
    int returnVal = 0;
    
    #if DEBUG == 1
        cout << "----- DEBUG addRecord -----" << endl;
        cout << "Account Number : " << accountno << endl;
        cout << "Name[] : " << name << endl;
        cout << "Address[] : " << address << endl;
    #endif

    new_record->accountno = accountno;
    strcpy(new_record->name, name);
    strcpy(new_record->address, address);
    new_record->next = NULL;
     
    if (current_record == NULL)
    {
        *pointer_start = new_record;
        returnVal = 1;
    }
    else
    {
        while (current_record != NULL)
        {
            if (current_record->accountno == accountno)
            {
                break;
            }

            if  (current_record->next == NULL)
            {
                current_record->next = new_record;
                returnVal = 1;
                break;
            }

            current_record = current_record->next;
        }
    }
     
    return returnVal;
}
 
/*****************************************************************
//
// Function name: printrecord
//
// DESCRIPTION: Uses an account number to print out a record
//
// Parameters: accountno (int) : account number to search for
//
// Return values: 1 : successully found the record
//                0 : record not found
//
*****************************************************************/
 
int llist::printRecord (int accountno)
{
    struct record *current_record = start;
    int returnVal;
     
    #if DEBUG == 1
        cout << "----- DEBUG printRecord ------" << endl;
        cout << "Account Number : " << accountno << endl;
    #endif
     
    if (current_record == NULL)
    {
        returnVal = 0;
    }
    else
    {
        while (current_record != NULL)
        {
            if (current_record->accountno == accountno)
            {
                cout << "-------------" << endl;
                cout << "Account No : " << current_record->accountno << endl;
                cout << "Name : " << current_record->name << endl;
                cout << "Address : " << current_record->address << endl;
                cout << "-------------" << endl;
                returnVal = 1;
                break;
            }
            current_record = current_record->next;
        }
    }
 
    return returnVal;
}

/*****************************************************************
//
// Function name: findReocrds
//
// DESCRIPTION: Finds all records in the database starting with a given string
//
// Parameters: name[] (char) : substring to check for
//
// Return values: 1 : records were found starting with the string
//                0 : no records found
//
*****************************************************************/
 
int llist::findRecords(char name[])
{
    struct record *current_record = start;
    int returnVal = 0;

    #if DEBUG == 1
        cout << "----- DEBUG findRecord ------" << endl;
        cout << "Name : " << name << endl;
    #endif

    while (current_record != NULL)
    {
        if (strncmp(name, current_record->name, strlen(name) - 1) == 0)
        {
            cout << "-------------" << endl;
            cout << "Account No : " << current_record->accountno << endl;
            cout << "Name : " << current_record->name << endl;
            cout << "Address : " << current_record->address << endl;
            cout << "-------------" << endl;
            returnVal = 1;
        }
        current_record = current_record->next;
    }

    return returnVal;
}

/*****************************************************************
//
// Function name: deleteRecord
//
// DESCRIPTION: Deletes a record in the database with the provided account number
//
// Parameters: accountno (int) : which account to be deleted
//
// Return values: 1 : record was deleted
//                0 : no record was deleted
//
*****************************************************************/
 
int llist::deleteRecord(int accountno)
{
    struct record *current_record = start;
    struct record *previous = NULL;
    int returnVal = 0;
     
    #if DEBUG == 1
        cout << "----- DEBUG deleteRecord ------" << endl;
        cout << "Accountno : " << accountno << endl;
    #endif
     
    while (current_record != NULL)
    {
        if (current_record->accountno == accountno)
        {
            if (previous == NULL)
            {
                start = current_record->next;
                previous = start;
                delete current_record;
                returnVal = 1;
                current_record = previous;               
            } 
            else if (previous->accountno == accountno)
            {
                start = current_record->next;
                previous = start;
                delete current_record;
                returnVal = 1;
                current_record = previous;
            }
            else
            {
                previous->next = current_record->next;
                delete current_record;
                returnVal = 1;
                current_record = previous;
            }
        }
        else
        {
            previous = current_record;
            current_record = current_record->next;
        }
    }
     
    return returnVal;
}
 
/*****************************************************************
//
// Function name: reverse
//
// DESCRIPTION: Recursive helper method to reverse the linked list
//
// Parameters: void
//
// Return values: void
//
*****************************************************************/
 
void llist::reverse(void)
{
    struct record *current_record = start;
    
    #if DEBUG == 1
        cout << "----- DEBUG reverse ------" << endl;
    #endif
     
    if (current_record == NULL)
    {
        cout << "No records, not reversing database." << endl;
    } else
    {
        reverse(start);
    }   
}
 
/*****************************************************************
 *
 * Function name: ostream
 *
 * DESCRIPTION: Overloads the operator <<
 *
 * Parameters: &os (ostream)
 *             &start (llist)
 *
 * Return values: os : Records being outputted
 *
 *****************************************************************/
 
std::ostream& operator<< (std::ostream &os, llist &start)
{
    struct record *current_record = start.start;
     
    #if DEBUG == 1
        cout << "----- DEBUG ostream overload -----" << endl;
        cout << "os : " << os << endl;
        cout << "start : " << start << endl;
    #endif
    
  
    if (current_record == NULL)
    {
        cout << "No records in database." << endl;
    }
    else
    {
        while (current_record != NULL)
        {
            cout << "-------------" << endl;
            cout << "Account No : " << current_record->accountno << endl;
            cout << "Name : " << current_record->name << endl;
            cout << "Address : " << current_record->address << endl;
            cout << "-------------" << endl;
            current_record = current_record->next;
        }
    }
     
    return os;
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
 
void getaddress(char address[])
{
    char user_input[100];
    
    #if DEBUG == 1
        cout << "----- DEBUG getAddress -----" << endl;
        cout << "Address : " << address << endl;
    #endif
 
    cout << "Enter the address of the account : " << endl;
    cout << "Include '^' at the end to indicate the end of the address : " << endl;

    cin.ignore();

    while(cin.getline(user_input, 99))
    {
        if(user_input[strlen(user_input) - 1] == '^') {
            strcat(address, user_input);
            fseek(stdin, 0, SEEK_END);
            break;
        }
        else
        {
            strcat(address, user_input);
            strcat(address, "\n");
        }
    }
    strcpy(user_input, "");
}