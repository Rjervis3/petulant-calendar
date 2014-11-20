/*
 *
 *
 * appt.h   - contains definition of appointment stuct as well as max
 *            text lenth var */


/* utilize an ifndef/define mechanism, so nodes will be defined exactly once */
#ifndef _APPT_H
#define _APPT_H

#define maxLen 80

  struct appt {
      int year;
      int month; /* 1=January, 2=February, ..., 12=December */
      int day;
      char text [maxLen];
   };

#endif
