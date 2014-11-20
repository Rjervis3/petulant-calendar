/* Implementation of the functions for managing appointments */

#include "appt-func.h"  //include header file with declarations
#include <stdio.h>
#include <stdlib.h>      
#include <string.h>

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

  //appointment notes read with getchar to allow for spaces
  while ((text[i] = getchar()) != '\n')
    {
      i++;
    }
  text[i]='\0'; //set last char to null for correct printing

  monthInt=monthSort(month);
  /*    executes and returns to menu if invalid month given   */
  if( monthInt == 0 ) 
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
      while(getchar() != '\n');    /*   clears input for reading    */

      if(option2 == 'c')
        { 
          strcpy(apptarray[*numAppts].text, text);
          /*  strcpy for text, other assignments below  */
	  apptarray[*numAppts].month = monthInt;
	  apptarray[*numAppts].day=day;
	  apptarray[*numAppts].year=year;
          *numAppts = *numAppts + 1; //increment numAppts in main
        }
      else if(option2 =='d')
        addAppt(apptarray, numAppts); //numAppts here already a pointer
    }
}
 
void insertionSort(struct appt * apptarray, int length, 
                  int comesFirst(struct appt, struct appt))
{
  int k;
  for ( k = 1; k < length; k++) {
    struct appt item = apptarray[k];
    int i = k-1;
    while ((i >= 0) && (comesFirst(item, apptarray[i]))){
      apptarray[i+1] = apptarray[i];
      i--;
    }
    apptarray[i+1] = item;  
  }
  printf("Elements of calendar are now sorted. Print with 'p' option\n");
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

/*     returns 1 if the date for app1 comes before the date for app2, 
                      and returns 0 otherwise.                        
 */
int comesFirstByDate(struct appt app1, struct appt app2)
{
  if(app1.year < app2.year)  return 1;
  else if (app1.year == app2.year)
    {
      if (app1.month < app2.month )  return 1;
      else if (app1.month == app2.month && app1.day < app2.day) return 1;
      else return 0;
    }
  else return 0;   //if app2.year > app1.year, app 1 is not first
}

/* returns 1 if the text for app1 comes before the 
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
                                 "November",
                                 "December" };

  for (i=0; i<numAppts; i++)
    { 
      fprintf(file, "%s ", monthNames[apptarray[i].month]);
      fprintf(file, "%d, %d:", apptarray[i].day, apptarray[i].year);
      fprintf(file, "%s \n", apptarray[i].text);
    }
 fclose(file);
}

void readFromFile(struct appt * apptarray, int * numAppts, int numRead)
{
  const char * mode  = "r"; //for read mode
  FILE * file =  fopen("./Appointment_input.txt", mode);
  char line[maxLen];
  char month[10];

  int i, j, k;
  int day;
  int year;

  printf("Will read %d appointments from file:\n", numRead);
  for(j=0; j<numRead; j++)
    {
      i=0; //reset on each loop

      //read name of month
      while ((month[i] = fgetc(file)) != ' ')
        {
          i++;
        }
      month[i]='\0';

      apptarray[*numAppts].month = monthSort(month);
     
      fscanf(file, "%d,", &day);    //read day from file
      apptarray[*numAppts].day =day;

      fscanf(file, "%d:", &year); //read year from file
      apptarray[*numAppts].year =year;

      fgets(line, maxLen, file); //reads until end of line or \n, store in line

      for(k=0; k<maxLen; k++) //clears newline stored above by fgets
        { if (line[k] != 0)
            {
              if(line[k]=='\n') line[k]='\0';
            }
        }

      strcpy(apptarray[*numAppts].text, line); 
    
      printf("\tAppointment %d stored as:", j+1);
      
      printf(" %d %d, %d: %s\n", apptarray[*numAppts].month,
	     apptarray[*numAppts].day, apptarray[*numAppts].year, 
             apptarray[*numAppts].text);
   
      *numAppts = *numAppts + 1;
    }
  fclose(file); 
}
