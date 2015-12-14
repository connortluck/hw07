#include<stdio.h>
#include<math.h>

// The recurrence algorithm //
void integral_recur (int nmin, int nmax, double vals[]);
void integral_recur (int nmin, int nmax, double vals[])
{
    vals[100] = 0.00367843028136748866811;      // "Initial condition" evaluated using a "brute force" integrator//
    int i;

    for (i = nmax - 1; i >= nmin; i--)  // Stable direction of recursion: from high i to low i //
    {
        vals[i] = vals[i + 1] / (i + 1) + 1 / (M_E * (i + 1));  // Rearranged recursion formula //
    }
}
