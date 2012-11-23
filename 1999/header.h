/*
	The header to put before entries from 1999
	See http://webdocs.cs.ualberta.ca/~darse/rsb-ts1.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <sys/time.h>

#define rock 0
#define paper 1
#define scissors 2
#define random() rand()
#define players 2

#define TRIALS 100000            /* maximum number of trials */
int my_history[TRIALS];
int opp_history[TRIALS];
int  turns_passed = 0;
int  trials;

#define maxrandom 2147483648.0   /* 2^31, ratio range is 0 <= r < 1 */

#define verbose1 0

int flip_biased_coin (double prob)
{
   /* flip an unfair coin (bit) with given probability of getting a 1 */

   if ( (random() / maxrandom) >= prob )
      return(0);
   else return(1);
}

int biased_roshambo (double prob_rock, double prob_paper)
{
   /* roshambo with given probabilities of rock, paper, or scissors */
   double throw;

   throw = random() / maxrandom;

   if ( throw < prob_rock )                   { return(rock); }
   else if ( throw < prob_rock + prob_paper ) { return(paper); }
   else /* throw >= prob_rock + prob_paper */ { return(scissors); }
}