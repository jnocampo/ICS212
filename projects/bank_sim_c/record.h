/*****************************************************************
*
* NAME: Jessica Ocampo
*
* HOMEWORK: Project 1
*
* CLASS: ICS 212
*
* FILE: record.h
*
* DESCRIPTION: Contains the definition for the record struct
*
*****************************************************************/

#include <stdio.h>
 
struct record
{
    int              accountno;
    char             name[25];
    char             address[80];
    struct record*   next;
};