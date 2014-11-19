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


//function declarations
//-----------------------------------------

//Pre-conditions: numAppts contains address of count variable (in other 
//    words is pointer to length of array. 
//Post-conditions: Program adds and appointment at the end of the current 
//  array and increments appointment count by 1. 
void addAppt(struct appt * apptarray, int * numAppts);

//Pre-conditions: none --note month of size 10 because no month names exceed
//  9 characters (1 allowed for null character).
//Post-conditions: Program will convert string containing month name into 
//  appropriate integer. If month name invalid, returns 0.
int monthSort (char month[10]);

//Pre-conditions: count is the length of the array to be printed
//Post-conditions: Program prints the elements in the array
void printAppts(struct appt * apptarray, int count);

//Pre-conditions:
//Post-conditions
void sortByDate(struct appt * apptarray, int length);


//Pre-conditions:
//Post-conditions
void insertionSort(struct appt * apptarray, int length, 
                  int func(struct appt, struct appt));
//Pre-conditions:
//Post-conditions
void sortByText(struct appt * apptarray, int length);

/* returns 1 if the date for appointment app1 comes before the 
   date for app2, and returns 0 otherwise */
int comesFirstByDate (struct appt app1, struct appt app2);

/* returns 1 if the text for appointment app1 comes before the 
   date for app2, and returns 0 otherwise */
int comesFirstByText (struct appt app1, struct appt app2);

void writeToFile(struct appt * apptarray, int numAppts);

void readFromFile(struct appt * apptarray, int * numAppts, int numRead);

//Pre-conditions:
//Post-conditions:
int main()
{
  int i;
  int numAppts=0;
  int maxSize = 100; /* current size of the apptArray */

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

      if (numAppts == maxSize) //if current array is too small
        { 
          printf("uh oh!\n");
          //a new and larger array will be allocated
          maxSize = maxSize * 2; 
          struct appt * tempArray = malloc (maxSize * sizeof (struct appt));
         //the appointments in the old array would be copied into the new array 
          for(i=0; i<=numAppts; i++)
            {
              tempArray[i] = apptArray[i];
            }
          //the old array would be deallocated
          free(apptArray); //****
          //the apptArray would point to the new array 
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
          printf("\nold number appts: %d\n", numAppts);
          addAppt(apptArray, &numAppts);
          printf("\nnew number appts: %d\n", numAppts);
          break;
        case 'd':
          insertionSort(apptArray, numAppts, 
                        comesFirstByDate);
          break;
        case 'a':
          insertionSort(apptArray, numAppts, 
                        comesFirstByText);
          break;
        case 'p':
          printAppts(apptArray, numAppts);
          break;
        case 'r':
          readFromFile(apptArray, &numAppts, 4);
          break;
        case 'w': 
          writeToFile(apptArray, numAppts);
          break;
        default: //if unrecognized option is entered
          printf("Unknown command, try again...\n");
          break;
        case 'q':
          printf("Terminating program . . .\n");
          exit(0);
        }
          
    }

  return 0;
}

void addAppt(struct appt * apptarray, int * numAppts)
{
  char month[10];
  int year, monthInt, day;
  char text [maxLen];
  int i=0;
  printf("\nPlease enter your appointment information in the format\n");
  printf("Month name date, year : Appointment notes\n");
  
  //read user input
  scanf("%s", &month);
  scanf("%d,", &day);
  scanf("%d:", &year);

  //appointment notes read with getchar to allow spaces
  while ((text[i] = getchar()) != '\n')
    {
      i++;
    }
  text[i]='\0'; //set last char to null for correct printing

  //executes and returns to menu if invalid month given
  //convert month name to int for future sorts in one step
  if((monthInt=monthSort(month)) == 0 ) 
    {
      printf("An invalid month name was entered, returning to menu\n");
    }
  else  //this else executes if month is correct
    {
      printf("The appointment you entered was:");
      printf(" %s %d, %d: %s\n", month, day, year, text);
  
      char option2;
      printf("If this is correct press c to store, or press d to try again\n");
      scanf("%c", &option2);
      while(getchar() != '\n'); //clears input for reading

      if(option2 == 'c')
        { 
          apptarray[*numAppts].year =year;
          apptarray[*numAppts].day =day;
          strcpy(apptarray[*numAppts].text, text);
          apptarray[*numAppts].month=monthInt;
          printf("The appointment stored as:");
          printf(" %d", apptarray[*numAppts].month);
          printf(" %d,", apptarray[*numAppts].day);
          printf(" %d:", apptarray[*numAppts].year);
          printf(" %s\n", apptarray[*numAppts].text);
          *numAppts = *numAppts + 1;
        }
      else if(option2 =='d')
        addAppt(apptarray, numAppts);
    }
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

void insertionSort(struct appt * apptarray, int length, 
                  int func(struct appt, struct appt))
{
  int k;
  for ( k = 1; k < length; k++) {
    struct appt item = apptarray[k];
    int i = k-1;
    while ((i >= 0) && (func(item, apptarray[i]))){
      apptarray[i+1] = apptarray[i];
      i--;
    }
    apptarray[i+1] = item;  
  }
  printf("\nElements of calendar now sorted. Print with 'p' option");
}

void printAppts(struct appt * apptarray, int count)
{
  int i;
  const char * monthNames[13] = {"Zero",        //to make accessing easier
                                 "January",    // ie now monthName[5] = May
                                 "February",
                                 "March",
                                 "April",
                                 "May",
                                 "June",
                                 "July",
                                 "August",
                                 "September",
                                 "October",
                                 "November",
                                 "December" };
  
  if (count != 0)
    {
      printf("Printing appointments:\n");
      for (i=0; i < count; i++)
        {
          printf("Appointment %d: ", i+1);
          printf("%s ", monthNames[apptarray[i].month]);
          printf("%d, %d:", apptarray[i].day, apptarray[i].year);
          printf("%s \n", apptarray[i].text);
        }
    }
  else printf("There are no appointments to print\n");

}


/* returns 1 if the date for appointment app1 comes before the 
   date for app2, and returns 0 otherwise */
int comesFirstByDate(struct appt app1, struct appt app2)
{
  if(app1.year < app2.year)  return 1;
  else if (app1.year == app2.year)
    {
      if (app1.month < app2.month)  return 1;
      else if (app1.day < app2.day) return 1;
    }
  else return 0;   //if app2.year > app1.year, app 1 is not first
}

/* returns 1 if the text for appointment app1 comes before the 
   text for app2, and returns 0 otherwise */
int comesFirstByText (struct appt app1, struct appt app2)
{
  if(strcmp(app1.text, app2.text) < 0)
    return 1;
  else return 0;
}

void writeToFile(struct appt * apptarray, int numAppts)
{
  const char * w  = "w";
  int i;
  FILE * file =  fopen("./Appointments.txt", w);
  
  const char * monthNames[13] = {"Zero", //Zero added to make accessing easier
                                 "January",  // ie now monthName[5] = May
                                 "February",
                                 "March",
                                 "April",
                                 "May",
                                 "June",
                                 "July",
                                 "August",
                                 "September",
                                 "October",
                                 "Novemeber",
                                 "December" };

  for (i=0; i<numAppts; i++)
    { 
      //fprintf(file, "Appointment %d: ", i+1);
      fprintf(file, "%s ", monthNames[apptarray[i].month]);
      fprintf(file, "%d, %d:", apptarray[i].day, apptarray[i].year);
      fprintf(file, "%s \n", apptarray[i].text);
    }
 fclose(file);
}

void readFromFile(struct appt * apptarray, int * numAppts, int numRead)
{
  const char * mode  = "r";
  FILE * file =  fopen("./Appointment_input.txt", mode);
  char line[maxLen];
  char month[10];

  char c;
  int i, j;
  int day;
  int year;

  printf("numRead = %d\n", numRead);
  for(j=0; j<numRead; j++)
    {
      i=0; //reset on ea loop
      printf("loop %d!\n", j);

      //read name of month
      while ((month[i] = fgetc(file)) != ' ')
        {
          i++;
        }
      month[i]='\0';

      printf("month read %s\n", month);
      apptarray[*numAppts].month = monthSort(month);
      // printf("month stored %d\n", apptarray[*numAppts].month);
    
      fscanf(file, "%d,", &day);    //read day from file
      apptarray[*numAppts].day =day;
      // printf("day read %d\n", day);

      fscanf(file, "%d:", &year); //read year from file
      apptarray[*numAppts].year =year;
      // printf("year read %d\n" , year);

      fgets(line, maxLen, file); //reads until end of line, store in line

      strcpy(apptarray[*numAppts].text, line); 
      // printf("Notes stored: %s", line);
    
    
      printf("The appointment %d stored as:", j+1);
      
     
       printf(" %d %d, %d: %s\n", apptarray[*numAppts].month, 
              apptarray[*numAppts].day, apptarray[*numAppts].year, 
              apptarray[*numAppts].text);
   
       *numAppts = *numAppts + 1;
    }
      fclose(file);
      // }

                         
  //}
}
