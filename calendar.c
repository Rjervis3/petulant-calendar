     /***********************************************************************
     * Name: Renn Jerivs                                                   *
     * Box   : 3762                                                        *
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

#define maxLen 80

//definition of appointment structure
  struct appt {
      int year;
      int month; /* 1=January, 2=February, ..., 12=December */
      int day;
      char text [maxLen];
   };


//function declarations
//-----------------------------------------

//Pre-conditions: Count is number of elements in array 
//Post-conditions: Program adds and appointment at the end of the current 
//  array. 
void addAppt(struct appt * apptarray, int count);


//Pre-conditions: none --note month of size 10 because no month names exceed
//  9 characters (1 allowed for null character).
//Post-conditions: Program will convert string containing month name into 
//  appropriate integer. If month name invalid, returns 0.
int monthSort (char month[10]);

//Pre-conditions:
//Post-conditions:
int main()
{

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

      //declare dynamic array for storing appts
      int maxSize = 100; /* current size of the apptArray */
      struct appt * apptArray = malloc (maxSize * sizeof (struct appt));
      int numAppts = 0;


        //read option 
      char option;
      printf("Please enter an option: ");
      scanf("%c", &option);
      while(getchar() != '\n');
  
      printf("\n");
      //switch statement to determine action based on user choice
      switch (option)
        {
        case 'e': 
          addAppt(apptArray, numAppts); 
          break;
        case 'd':
          printf("option d\n");
          break;
        case 'a':
          printf("option a\n");
          break;
        case 'p':
          printf("print option\n");
          break;
        case 'r':
          printf("READ OPTION\n");
          break;
        case 'w': 
          printf("write option\n");
          break;
        default:
          printf("Unknown command, try again...\n");
          break;
        case 'q':
          exit(0);
        }
          
    }

  return 0;
}

void addAppt(struct appt * apptarray, int count)
{
  char month[10];
  int year, monthInt, day;
  char text [maxLen];
  printf("\nPlease enter your appointment information in the format\n");
  printf("Month name date, year : Appointment notes\n");
  int i=0;
  scanf("%s", &month);
  scanf("%d,", &day);
  scanf("%d:", &year);

  //appointment notes read with getchar to allow spaces
   while ((text[i] = getchar()) != '\n')
    {
      i++;
    }
   text[i]='\0'; //set last char to null for correct printing

 monthInt=monthSort(month);
  
  if(monthInt==0) //prints and returns to menu if invalid month given
    {
      printf("An invalid month name was entered, returning to menu\n");
    }
  else  //this else exectutes if month is correct
    {
      printf("The appointment you entered was:");
      printf(" %s %d, %d: %s\n", month, day, year, text);
  
      char option2;
      printf("If this is correct press c to store, or press d to try again\n");

      scanf("%c", &option2);
      while(getchar() != '\n'); //clears input for reading
 
      if(option2 == 'c')
        {
          apptarray[count].year =year;
          apptarray[count].day =day;
          //apptarray[count].text="text";
          apptarray[count].month=monthSort(month);
        }
      else if(option2 =='d')
        addAppt(apptarray, count);
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