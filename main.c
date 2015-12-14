#include<stdio.h>
#include<math.h>
#include"recur.c"
#include <gsl/gsl_integration.h>
#include"gsl_integration.c"
#include"timer.h"
#include"timer.c"
#include"adjust.c"
#define NMAX 100

/* Integral is evaluated for n=0 to n=100 using the derived recursion formula and the GSL general integrator then the results are displayed showing speed of calculation in terms of a ratio by dividng them by each other. The integral is evaluated for n=0 to n=100 using both a derived recursion formula*/

int main (void)
{
    double vals1[NMAX + 1], vals2[NMAX + 1], time1a, time1b, time2a, time2b, tmin = 	1., tmax = 2.;      // Establishes all double values that are to be used//
    
	int nmin = 0, nmax = NMAX, count1 = 1000, count2 = 800; // Establishes all of the integers that are to be used//

    integral_recur (nmin, nmax, vals1); // Recursion formula stores I(0) to I(100) in the array vals1//
    integral_gen (nmin, nmax, vals2);   // GSL integration algorithm stores I(0) to I(100) in the array vals2//


    printf
        ("      --n--       --Recur--        --GSL Integrator--   --Absolute 		Error*10^9--\n");
    int x;

    for (x = 0; x < 101; x++)
    {
        printf ("   %6d     %15.15f     %15.15f      %15.15f \n", x, vals1[x],
            vals2[x], fabs (1.e9 * (vals1[x] - vals2[x])));
    }                           // Prints the values for each term in specific sequencing to fit the labels. //
    
	int p;

    printf
        ("\n--Timing for recurrence function--\nTime per call (usec) Total Time (sec)      Count\n");
    do
    {
        timer_start ();         // start timer.
        for (p = 0; p < count1; p++)    // The function is called "count1" times.
        {
            integral_recur (nmin, nmax, vals1); // The recursion formula stores each of the sequence values in the array vals1//
        }
        time1a = timer_stop (); // The timer is stopped.
        time1b = time1a / count1;       // Divide by two differnt times to create ratio. 
        printf (" %10.2f usec     %10.6f sec    %10d\n", time1b * 1.e6,
            time1a, count1);
        count1 = adjust_rep_count (count1, time1a, tmin, tmax); // The number of function calls "count1" is adjusted. 
    }
    while ((time1a > tmax) || (time1a < tmin)); // repeat untill time is within range..
    printf ("Time per recur function call = %f usec \n", time1b * 1.e6);
    printf
        ("\n--Timing for GSL integration function--\nTime per call (usec) Total Time (sec)      Count\n");
    do
    {
        timer_start ();         // Stop timer.
        for (p = 0; p < count2; p++)    // The function is called "count2" times.
        {
            integral_gen (nmin, nmax, vals2);   // The GSL integration formula stores each of the sequence values in the array vals1//
        }
        time2a = timer_stop (); // Stop timer.
        time2b = time2a / count2;       // Divide by two differerent times to create ratio. 
        printf (" %10.2f usec     %10.6f sec    %10d\n", time2b * 1.e6,
            time2a, count2);
        count2 = adjust_rep_count (count2, time2a, tmin, tmax); // The number of function calls "count2" is adjusted. 
    }
    while ((time2a > tmax) || (time2a < tmin)); // Repeat untill time is within range.
    printf ("Time per GSL function call = %f usec \n", time2b * 1.e6);

    printf ("Ratio of times Tgsl / Trecur = %f\n", time2b / time1b);    // print ratio of times//
    return 0;
}
