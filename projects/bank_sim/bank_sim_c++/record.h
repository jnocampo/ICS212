/*****************************************************************
*
* NAME: Jessica Ocampo
*
* HOMEWORK: Project 2
*
* CLASS: ICS 212
*
* FILE: record.h
*
* DESCRIPTION: Contains the record definition for Project 2
*
*****************************************************************/
 
#include <iostream>
#include <stdlib.h>
#include <iomanip>
 
using namespace std;
 
struct record
{
    int              accountno;
    char             name[25];
    char             address[80];
    struct record*   next;
};