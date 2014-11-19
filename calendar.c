     /***********************************************************************
     * Name: Renn Jerivs                                                   *
     * Box : 3762                                                          *
     * Assignment: Supplemental Problem 4: Daily Calendar                  *
     *                                                                     *
     * Assignment for Friday, November 21st                                *
     ***********************************************************************/

    /* *********************************************************************
     * Academic honesty certification:                                     *
     *   Written/online sources used:                                      *
     *   ->Referenced namelist.c from Lab on Linked Lists for an example   *
     *     of a switch statement that uses characters                      *
     *   ->Referenced project011 for use of exit function                  *
     *   ->Referenced getchar-line-example.c from lab on char by char I/O  *
     *       for use of getchar and a while loop                           *
     *   ->Referenced  http://stackoverflow.com/questions/1088622/         *
     *       how-do-i-create-an-array-of-strings-in-c for help declaring   *
     *       string literals                                               *
     *   ->Referenced lab2-2-1.c from Lab on Functions pt 2 for reminders  *
     *     on accessing pointers                                           *
     *   ->Referenced program func-parm.c from lab on function parameters  *
     *     for help on declaring a function with a function parameter      *
     *   ->Referenced http://www.tutorialspoint.com/cprogramming           *
     *      /c_file_io.htm for how to write and read to a file             *
     *   -> also used man page on feof() and http://stackoverflow.com/     *
     *      questions/13384296/reading-input-file-in-c for help with       *
     *      readFromFile function                                          *
     *                                                                     *
     *   Help obtained:  [none]                                            *
     *                                                                     *
     *   My/our signature(s) below confirms that the above list of sources *
     *   is complete AND that I/we have not talked to anyone else          *
     *   (e.g., CSC 161 students) about the solution to this problem       *
     *                                                                     *
     *   Signature:                                                        *
     ***********************************************************************/

/*     calendar.c
 *
 *  This is a program to maintain a daily calendar via the terminal.
 */


//compile and run with the line gcc -o calendar calendar.c && ./calendar

#include <stdio.h>
#include <stdlib.h>       //for use with exit function
#include <string.h>
#include "appt.h"        //defines appointment struct and maxLen
#include "appt-func.h"    //header for appt functions


/*Pre-conditions: None --note month of size 10 because no month names exceed
                  9 characters (1 allows for null character).
  Post-conditions: Program will convert string containing month name into 
                  appropriate integer. If month name invalid, returns 0.  */
int monthSort (char month[10]);

//Pre-conditions:
//Post-conditions:
int main()
{
  int i;
  int numAppts=0;
  int maxSize = 4; /* current size of the apptArray */
  int numRead = 4;  //number of appts to be read from file Appointment_input.txt
 //declare dynamic array for storing appts
  struct appt * apptArray = malloc (maxSize * sizeof (struct appt));

  //for option entered by user
   char option;

  while(1)  //loop until program is quit
    {
      //print list of menu options
      printf("\nCalendar Program Options:\n");
      printf("\t e:\tEnter a new appontment\n");
      printf("\t d:\tSort appointments by date\n");
      printf("\t a:\tSort appointments alphabetically by text\n");
      printf("\t p:\tPrint curent appointments\n");
      printf("\t r:\tRead appointments from a file\n");
      printf("\t w:\tWrite appointments to a file\n");
      printf("\t q:\tQuit the program\n\n");

      if (numAppts == maxSize) //if array is full
        { 
          printf("Previous appointment book full, more space now allocated\n");
          //a new and larger array will be allocated
          maxSize = maxSize * 2; 
          struct appt * tempArray = malloc (maxSize * sizeof (struct appt));
         //the appointments in the old array copied into the new array 
          for(i=0; i<=numAppts; i++)
            {
              tempArray[i] = apptArray[i];
            }
          //old array deallocated
          free(apptArray);
          //apptArray points to the new array 
          apptArray=tempArray;
        }

      printf("Please enter an option: ");
      scanf("%c", &option);
      while(getchar() != '\n');  //clear input after reading
  
      printf("\n");

      //switch statement to determine action based on user choice
      switch (option)
        {
        case 'e': 
          addAppt(apptArray, &numAppts);
          break;
        case 'd':
          insertionSort(apptArray, numAppts, comesFirstByDate);
          break;
        case 'a':
          insertionSort(apptArray, numAppts, comesFirstByText);
          break;
        case 'p':
          printAppts(apptArray, numAppts);
          break;
        case 'r':
          readFromFile(apptArray, &numAppts, numRead);
          break;
        case 'w': 
          writeToFile(apptArray, numAppts);
          break;
        default:              //if unrecognized option is entered
          printf("Unknown command, try again...\n");
          break;
        case 'q':
          printf("Terminating program . . .\n");
          exit(0);
        }
          
    }

  return 0;
}

int monthSort (char month[10])
{
  int monNum;

  //note that (!strcmp()) will execute if strcmp return 0 (strings are equal)
  if (!strcmp(month, "January")){
    monNum=1;}
  else if (!strcmp(month, "February")){
    monNum=2;}
  else if (!strcmp(month, "March"))
    monNum=3;
  else if (!strcmp(month, "April"))
    monNum=4;
  else if (!strcmp(month, "May"))
    monNum=5;
  else if (!strcmp(month, "June"))
    monNum=6;
  else if (!strcmp(month, "July"))
    monNum=7;
  else if (!strcmp(month, "August"))
    monNum=8;
  else if (!strcmp(month, "September"))
    monNum=9;
  else if (!strcmp(month, "October"))
    monNum=10;
  else if (!strcmp(month, "November"))
    monNum=11;
  else if (!strcmp(month, "December"))
    monNum=12;
  else return 0;  //to indicate month entered incorrectly

  return monNum;
}

