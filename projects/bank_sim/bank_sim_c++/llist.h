/*****************************************************************
*
* NAME: Jessica Ocampo
*
* HOMEWORK: Project 2
*
* CLASS: ICS 212
*
* INSTRUCTOR: Ravi Narayan
*
* DATE: May 1 2019
*
* FILE: llist.h
*
* DESCRIPTION: Linked list class definition for project 2
*
*****************************************************************/

#include <iostream>
#include <stdlib.h>
 
using namespace std;

class llist
{
private:
    record *    start;
    char        filename[16];
    int         readfile();
    void        writefile();
    record *    reverse(record * );
    void        cleanup();

public:
    llist();
    llist(char[]);
    ~llist();
    int addRecord (int, char [ ],char [ ]);
    int printRecord (int);
    // replace printAllRecords() with the << operator
    friend std::ostream& operator<< (std::ostream &, llist &);
    int findRecords (char [ ]);
    int deleteRecord(int);
    void reverse();
};