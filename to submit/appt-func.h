/* interface for working with appointments */

#include "appt.h" //includes def of appt stuct

/* Pre-conditions: @param numAppts contains a pointer to the length of 
                  the array. 
Post-conditions: Program adds and appointment at the end of the current 
                 array and increments appointment count by 1.
 */
void addAppt(struct appt * apptarray, int * numAppts);

/* Pre-conditions: count is the length of the array to be printed
   Post-conditions: Program prints the elements in the array */
void printAppts(struct appt * apptarray, int count);

/* Pre-conditions: @param length is the length of the array to be printed
                   @param funct indicates how elements are to be compared,
                   function should return 1 if first appt if before second
   Post-conditions: Program sorts appointments by date earliest to latest */
void insertionSort(struct appt * apptarray, int length, 
                  int comesFirst(struct appt, struct appt));

/* Pre-conditions: None
   Post-conditions: Program returns 1 if the date for app1 comes before 
                    the date for app2, else returns 0 */
int comesFirstByDate (struct appt app1, struct appt app2);

/* Pre-conditions: None
   Post-conditions: Program returns 1 if the text for app1 comes before 
                    the date for app2, else returns 0
note: program does not take into account capital letters (all capitals
will be sorted before lowercase) */
int comesFirstByText (struct appt app1, struct appt app2);

/* Pre-conditions: None
   Post-conditions: Program writes current collection of appointments
                    to the specified file, 1 appointment per line*/
void writeToFile(struct appt * apptarray, int numAppts);


/* Pre-conditions: File containing appointments is in current directory
                   with the title Appointment_input.txt and text is in
                   correct format (Monthname date, year: Notes")
   Post-conditions: Program reads specified number of appointments
   from the specified file. */
void readFromFile(struct appt * apptarray, int * numAppts, int numRead);
