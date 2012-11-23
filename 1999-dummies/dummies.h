/*  http://webdocs.cs.ualberta.ca/~darse/rsb-ts1.c  */

#define maxrandom 2147483648.0   /* 2^31, ratio range is 0 <= r < 1 */

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

/*  Dummy Bots  (written by Darse Billings)  */

int randbot ()  /* Random (Optimal) */
{
   /* generate action uniformly at random (optimal strategy) */
   return( random() % 3);
}

int rockbot ()  /* Good Ole Rock */
{
   /* "Good ole rock.  Nuthin' beats rock." */
   return(rock);
}

int r226bot ()  /* R-P-S 20-20-60 */
{
   /* play 20% rock, 20% paper, 60% scissors */
   return( biased_roshambo(0.2, 0.2));
}

int rotatebot ()  /* Rotate R-P-S */
{
   /* rotate choice each turn r -> p -> s */
   return( my_history[0] % 3);
}

int copybot ()  /* Beat Last Move */
{
   /* do whatever would have beat the opponent last turn */
   return( (opp_history[opp_history[0]] + 1) % 3);
}

int switchbot ()  /* Always Switchin' */
{
   /* never repeat the previous pick */
   if ( my_history[my_history[0]] == rock ) {
      return( biased_roshambo(0.0, 0.5) ); }
   else if ( my_history[my_history[0]] == paper ) {
      return( biased_roshambo(0.5, 0.0) ); }
   else return( biased_roshambo(0.5, 0.5) );
}

int freqbot ()  /* Beat Frequent Pick */
{
   /* beat the opponent's most frequent choice */

   int i, rcount, pcount, scount;

   rcount = 0;  pcount = 0;  scount = 0;
   for (i = 1; i <= opp_history[0]; i++) {
      if (opp_history[i] == rock)            { rcount++; }
      else if (opp_history[i] == paper)      { pcount++; }
      else /* opp_history[i] == scissors */  { scount++; }
   }
   if ( (rcount > pcount) && (rcount > scount) ) { return(paper); }
   else if ( pcount > scount ) { return(scissors); }
   else { return(rock); }
}

int freqbot2 ()  /* Beat Frequent Pick (again) */
{
   /* maintain stats with static variables to avoid re-scanning
      the history array  (based on code by Don Beal) */

   static int rcount, pcount, scount;
   int opp_last;

   if( opp_history[0] == 0 ) {
      rcount = 0;  pcount = 0;  scount = 0;  }
   else {
      opp_last = opp_history[opp_history[0]];
      if ( opp_last == rock)          { rcount++; }
      else if ( opp_last == paper)    { pcount++; }
      else /* opp_last == scissors */ { scount++; }
   }
   if ( (rcount > pcount) && (rcount > scount) ) { return(paper); }
   else if ( pcount > scount ) { return(scissors); }
   else { return(rock); }
}

int pibot ()  /* Pi bot */
{
   /* base each decision on a digit of pi (skipping 0s) */

   static int index;
   static int pi_table [1200] =  /* skipping 0s leaves 1088 digits */
{3,1,4,1,5,9,2,6,5,3,5,8,9,7,9,3,2,3,8,4,6,2,6,4,3,3,8,3,2,7,9,5,0,2,8,8,4,1,9,7,
 1,6,9,3,9,9,3,7,5,1,0,5,8,2,0,9,7,4,9,4,4,5,9,2,3,0,7,8,1,6,4,0,6,2,8,6,2,0,8,9,
 9,8,6,2,8,0,3,4,8,2,5,3,4,2,1,1,7,0,6,7,9,8,2,1,4,8,0,8,6,5,1,3,2,8,2,3,0,6,6,4,
 7,0,9,3,8,4,4,6,0,9,5,5,0,5,8,2,2,3,1,7,2,5,3,5,9,4,0,8,1,2,8,4,8,1,1,1,7,4,5,0,
 2,8,4,1,0,2,7,0,1,9,3,8,5,2,1,1,0,5,5,5,9,6,4,4,6,2,2,9,4,8,9,5,4,9,3,0,3,8,1,9,
 6,4,4,2,8,8,1,0,9,7,5,6,6,5,9,3,3,4,4,6,1,2,8,4,7,5,6,4,8,2,3,3,7,8,6,7,8,3,1,6,
 5,2,7,1,2,0,1,9,0,9,1,4,5,6,4,8,5,6,6,9,2,3,4,6,0,3,4,8,6,1,0,4,5,4,3,2,6,6,4,8,
 2,1,3,3,9,3,6,0,7,2,6,0,2,4,9,1,4,1,2,7,3,7,2,4,5,8,7,0,0,6,6,0,6,3,1,5,5,8,8,1,
 7,4,8,8,1,5,2,0,9,2,0,9,6,2,8,2,9,2,5,4,0,9,1,7,1,5,3,6,4,3,6,7,8,9,2,5,9,0,3,6,
 0,0,1,1,3,3,0,5,3,0,5,4,8,8,2,0,4,6,6,5,2,1,3,8,4,1,4,6,9,5,1,9,4,1,5,1,1,6,0,9,
 4,3,3,0,5,7,2,7,0,3,6,5,7,5,9,5,9,1,9,5,3,0,9,2,1,8,6,1,1,7,3,8,1,9,3,2,6,1,1,7,
 9,3,1,0,5,1,1,8,5,4,8,0,7,4,4,6,2,3,7,9,9,6,2,7,4,9,5,6,7,3,5,1,8,8,5,7,5,2,7,2,
 4,8,9,1,2,2,7,9,3,8,1,8,3,0,1,1,9,4,9,1,2,9,8,3,3,6,7,3,3,6,2,4,4,0,6,5,6,6,4,3,
 0,8,6,0,2,1,3,9,4,9,4,6,3,9,5,2,2,4,7,3,7,1,9,0,7,0,2,1,7,9,8,6,0,9,4,3,7,0,2,7,
 7,0,5,3,9,2,1,7,1,7,6,2,9,3,1,7,6,7,5,2,3,8,4,6,7,4,8,1,8,4,6,7,6,6,9,4,0,5,1,3,
 2,0,0,0,5,6,8,1,2,7,1,4,5,2,6,3,5,6,0,8,2,7,7,8,5,7,7,1,3,4,2,7,5,7,7,8,9,6,0,9,
 1,7,3,6,3,7,1,7,8,7,2,1,4,6,8,4,4,0,9,0,1,2,2,4,9,5,3,4,3,0,1,4,6,5,4,9,5,8,5,3,
 7,1,0,5,0,7,9,2,2,7,9,6,8,9,2,5,8,9,2,3,5,4,2,0,1,9,9,5,6,1,1,2,1,2,9,0,2,1,9,6,
 0,8,6,4,0,3,4,4,1,8,1,5,9,8,1,3,6,2,9,7,7,4,7,7,1,3,0,9,9,6,0,5,1,8,7,0,7,2,1,1,
 3,4,9,9,9,9,9,9,8,3,7,2,9,7,8,0,4,9,9,5,1,0,5,9,7,3,1,7,3,2,8,1,6,0,9,6,3,1,8,5,
 9,5,0,2,4,4,5,9,4,5,5,3,4,6,9,0,8,3,0,2,6,4,2,5,2,2,3,0,8,2,5,3,3,4,4,6,8,5,0,3,
 5,2,6,1,9,3,1,1,8,8,1,7,1,0,1,0,0,0,3,1,3,7,8,3,8,7,5,2,8,8,6,5,8,7,5,3,3,2,0,8,
 3,8,1,4,2,0,6,1,7,1,7,7,6,6,9,1,4,7,3,0,3,5,9,8,2,5,3,4,9,0,4,2,8,7,5,5,4,6,8,7,
 3,1,1,5,9,5,6,2,8,6,3,8,8,2,3,5,3,7,8,7,5,9,3,7,5,1,9,5,7,7,8,1,8,5,7,7,8,0,5,3,
 2,1,7,1,2,2,6,8,0,6,6,1,3,0,0,1,9,2,7,8,7,6,6,1,1,1,9,5,9,0,9,2,1,6,4,2,0,1,9,8,
 9,3,8,0,9,5,2,5,7,2,0,1,0,6,5,4,8,5,8,6,3,2,7,8,8,6,5,9,3,6,1,5,3,3,8,1,8,2,7,9,
 6,8,2,3,0,3,0,1,9,5,2,0,3,5,3,0,1,8,5,2,9,6,8,9,9,5,7,7,3,6,2,2,5,9,9,4,1,3,8,9,
 1,2,4,9,7,2,1,7,7,5,2,8,3,4,7,9,1,3,1,5,1,5,5,7,4,8,5,7,2,4,2,4,5,4,1,5,0,6,9,5,
 9,5,0,8,2,9,5,3,3,1,1,6,8,6,1,7,2,7,8,5,5,8,8,9,0,7,5,0,9,8,3,8,1,7,5,4,6,3,7,4,
 6,4,9,3,9,3,1,9,2,5,5,0,6,0,4,0,0,9,2,7,7,0,1,6,7,1,1,3,9,0,0,9,8,4,8,8,2,4,0,1};

   /* corrected code courtesy of Michael Callahan */
   if (my_history[0] == 0) { index = 0; }
   else {
      index = (index + 1) % 1200;
      while (pi_table[index] == 0) { index++; }
      /* Don't have to check over 1200 again because last entry is not 0. */
   }
   return(pi_table[index] % 3);
}

int switchalot ()  /* Switch A Lot */
{
   /* seldom repeat the previous pick */
   if ( my_history[my_history[0]] == rock ) {
      return( biased_roshambo(0.12, 0.44) ); }
   else if ( my_history[my_history[0]] == paper ) {
      return( biased_roshambo(0.44, 0.12) ); }
   else return( biased_roshambo(0.44, 0.44) );
}

int flatbot3 ()  /* Flat bot */
{
   /* flat distribution, 20% chance of most frequent actions */
   static int rc, pc, sc;
   int mylm, choice;

   choice = 0;
   if ( my_history[0] == 0 ) {
      rc = 0; pc = 0; sc = 0; }
   else {
      mylm = my_history[my_history[0]];
      if (mylm == rock)            { rc++; }
      else if (mylm == paper)      { pc++; }
      else /* mylm == scissors */  { sc++; }
   }
   if ((rc < pc) && (rc < sc)) {
      choice = biased_roshambo(0.8, 0.1); }
   if ((pc < rc) && (pc < sc)) {
      choice = biased_roshambo(0.1, 0.8); }
   if ((sc < rc) && (sc < pc)) {
      choice = biased_roshambo(0.1, 0.1); }
   if ((rc == pc) && (rc < sc)) {
      choice = biased_roshambo(0.45, 0.45); }
   if ((rc == sc) && (rc < pc)) {
      choice = biased_roshambo(0.45, 0.1); }
   if ((pc == sc) && (pc < rc)) {
      choice = biased_roshambo(0.1, 0.45); }
   if ((rc == pc) && (rc == sc)) {
      choice = random() % 3; }
   /* printf("[%d %d %d: %d]", rc, pc, sc, choice); */
   return(choice);
}

int antiflatbot ()  /* Anti-Flat bot */
{
   /* maximally exploit flat distribution */

   static int rc, pc, sc;
   int opplm, choice;

   choice = 0;
   if ( opp_history[0] == 0 ) {
      rc = 0; pc = 0; sc = 0; }
   else {
      opplm = opp_history[opp_history[0]];
      if (opplm == rock)           { rc++; }
      else if (opplm == paper)      { pc++; }
      else /* opplm == scissors */  { sc++; }
   }
   if ((rc < pc) && (rc < sc)) {
      choice = paper; }
   if ((pc < rc) && (pc < sc)) {
      choice = scissors; }
   if ((sc < rc) && (sc < pc)) {
      choice = rock; }
   if ((rc == pc) && (rc < sc)) {
      choice = paper; }
   if ((rc == sc) && (rc < pc)) {
      choice = rock; }
   if ((pc == sc) && (pc < rc)) {
      choice = scissors; }
   if ((rc == pc) && (rc == sc)) {
      choice = random() % 3; }
   /* printf("[%d %d %d: %d]", rc, pc, sc, choice); */
   return(choice);
}

int foxtrotbot ()  /* Foxtrot bot */
{
   /* set pattern: rand prev+2 rand prev+1 rand prev+0, repeat */

   int turn;
   turn = my_history[0] + 1;
   if ( turn % 2 ) { return( random() % 3 ); }
   else { return( (my_history[turn-1] + turn) % 3 ); }
}

int debruijn81 ()  /* De Bruijn string */
{
   /* several De Bruijn strings of length 81 concatentated */

   static int db_table [1000] = /* De Bruijn sequence: */
{1,0,2,0,0,2,0,2,0,1,1,0,0,2,2,1,0,0,1,1,2,2,0,0,1,2,1,0,2,2,2,2,0,1,2,0,2,2,0,2,
 1,1,2,1,1,0,1,1,1,2,0,0,0,0,2,1,0,1,0,1,2,2,1,2,0,1,0,0,0,1,0,2,1,2,1,2,2,2,1,1,
 1,0,0,1,1,1,1,0,1,0,2,2,2,0,0,2,2,0,2,0,1,0,1,1,0,2,1,1,2,2,2,2,1,1,1,2,0,1,2,2,
 1,2,0,0,0,1,0,0,0,0,2,0,2,2,1,0,0,1,2,1,2,2,0,1,1,2,1,1,0,0,2,1,0,1,2,0,2,1,2,1,
 0,2,1,1,2,0,0,1,0,1,2,2,0,1,0,0,2,0,1,2,0,1,1,2,1,1,1,1,0,2,0,2,1,0,2,2,0,2,2,2,
 2,0,0,0,1,2,1,2,2,2,1,1,0,1,1,0,0,0,0,2,1,2,0,2,0,0,2,2,1,0,0,1,1,1,2,2,1,2,1,0,
 1,0,2,1,0,1,0,2,0,2,0,0,1,2,2,2,0,2,1,0,0,1,1,1,2,2,1,1,0,2,2,0,0,0,2,2,2,2,1,2,
 2,0,1,2,0,0,2,0,1,1,2,1,2,1,1,1,1,0,0,2,1,2,0,1,0,0,0,0,1,0,1,1,0,1,2,1,0,2,1,1,
 2,0,2,2,2,2,1,1,1,1,0,0,2,0,2,2,2,1,2,1,0,2,1,0,0,0,0,2,1,1,2,2,1,0,1,0,0,1,1,1,
 2,1,1,0,1,2,2,2,2,0,0,1,2,0,2,0,1,2,1,2,0,1,0,1,1,2,0,0,0,1,0,2,2,0,2,1,2,2,0,1,
 1,0,2,0,0,0,0,0,0,1,0,0,0,2,1,1,0,0,1,1,1,1,0,2,0,2,1,2,0,2,2,1,2,2,2,1,1,1,2,1,
 2,1,0,0,2,0,1,1,0,1,0,2,1,0,2,2,2,2,0,2,0,0,2,2,0,0,1,2,2,1,0,1,1,2,0,1,2,1,1,2,
 2,0,1,0,1,2,2,2,0,2,0,0,2,0,2,1,2,2,2,2,0,0,0,0,2,2,1,0,0,0,1,2,0,1,2,1,2,0,0,1,
 0,2,0,1,0,0,2,1,0,1,2,2,1,1,2,0,2,2,2,1,2,1,0,2,2,0,1,1,0,2,1,1,0,0,1,1,2,1,1,1,
 1,0,1,0,1,1,1,1,1,1,2,1,0,0,0,0,1,1,0,2,1,2,1,2,2,2,0,0,1,2,0,1,0,1,2,1,1,2,2,0,
 2,0,2,1,1,0,0,1,0,2,0,0,2,0,1,1,2,0,2,2,1,1,1,1,0,1,0,0,2,2,2,2,1,2,0,0,0,2,1,0,
 2,2,0,1,2,2,1,0,2,1,0,1,0,1,1,1,1,2,1,1,0,1,2,1,2,2,2,2,1,2,0,0,0,1,1,2,0,2,0,2,
 1,0,0,0,0,2,0,0,1,0,0,2,2,2,0,0,2,1,1,2,2,0,1,2,0,1,1,0,0,1,2,2,1,1,1,0,2,0,1,0,
 2,2,0,2,2,1,0,2,1,2,2,2,1,0,1,0,2,2,1,2,0,2,1,0,2,0,0,0,0,1,2,1,0,0,2,0,2,2,0,1,
 0,1,1,2,1,1,0,0,1,0,0,0,2,1,1,2,0,0,2,2,2,2,0,0,1,1,1,0,2,1,2,1,2,2,1,1,1,1,2,2,
 0,2,0,1,2,0,1,1,0,1,1,0,0,1,1,0,1,2,0,1,2,1,2,2,1,0,0,2,0,2,1,0,1,0,2,2,0,1,1,2,
 1,0,2,0,0,1,0,1,1,1,2,2,2,2,1,2,0,2,2,1,1,2,0,0,2,1,2,1,1,1,1,0,2,1,1,0,0,0,0,2,
 2,2,0,0,0,1,2,2,0,2,0,2,2,0,2,1,1,2,0,2,0,0,1,1,1,0,0,1,2,1,1,0,1,1,0,2,2,0,0,2,
 2,1,1,1,1,2,1,2,1,0,2,0,2,2,2,2,1,2,0,0,0,1,0,0,2,1,0,0,0,0,2,0,1,1,2,2,2,0,1,2,
 2,1,0,1,0,1,2,0,1,0,2,1,0,2,0,2,1,1,1,0,0,2,2,2,0,1,1,2,2,1,2,0,0,0,1,0,1,2,1,0};

   /* corrected code courtesy of Michael Callahan */
   return(db_table[my_history[0] % 1000]);
}

int textbot ()  /* Text bot */
{
   /* English text (rsbpc post) converted to r-p-s */
   /* contains:  281 0's, 267 1's, 452 2's (heavy bias) */

   static int db_table [1000] = 
{2,0,2,2,2,1,0,0,1,2,2,1,2,2,2,0,2,1,2,0,0,2,1,0,2,1,0,2,2,1,1,0,0,2,2,0,0,1,0,1,
 1,1,0,2,1,2,1,0,1,1,2,2,0,2,0,0,2,2,2,0,1,1,1,0,1,1,2,0,0,0,2,2,2,1,2,1,0,0,1,0,
 1,1,2,2,0,2,1,0,1,1,2,1,0,0,2,0,2,1,1,2,0,0,2,0,0,1,1,0,0,1,2,2,1,2,1,2,2,2,2,2,
 0,2,0,2,2,2,0,2,1,0,1,1,2,0,2,2,1,2,2,0,1,2,2,2,0,0,1,1,2,2,0,2,0,0,2,2,1,1,1,0,
 2,1,2,2,0,2,2,2,0,2,1,0,0,1,0,1,1,1,1,2,2,2,0,0,1,0,1,2,1,2,0,0,2,2,1,1,2,2,0,0,
 2,2,2,1,2,1,2,1,1,1,2,2,2,0,2,1,0,2,2,1,0,1,2,2,2,0,2,1,1,2,2,1,0,2,2,1,1,0,0,2,
 1,1,0,1,0,2,2,2,0,2,2,2,1,1,2,1,0,0,2,0,2,1,1,2,0,0,2,0,0,1,1,0,0,1,2,2,0,1,2,1,
 2,1,0,1,1,0,2,2,1,1,1,2,2,2,2,0,2,2,2,2,2,2,2,2,1,2,2,1,2,0,1,2,2,1,1,2,0,1,2,2,
 2,2,0,0,1,2,2,2,0,0,2,2,2,0,0,1,1,0,0,0,1,2,2,1,2,2,2,2,2,2,1,0,1,1,0,2,1,2,1,1,
 1,0,2,1,2,2,0,1,0,0,0,2,0,2,2,0,1,1,0,2,2,2,2,1,2,1,1,0,0,2,2,1,1,2,2,0,1,1,2,1,
 1,2,1,2,2,0,2,2,2,1,1,1,2,2,0,1,2,1,0,1,1,2,1,2,2,2,2,2,2,2,2,2,2,2,0,2,1,0,1,1,
 2,0,1,1,2,2,1,2,2,2,1,0,2,2,2,0,0,2,2,2,2,2,2,2,1,0,1,1,2,0,1,2,1,0,1,0,0,2,1,2,
 2,0,0,1,0,1,2,0,2,0,0,1,2,2,0,2,2,2,0,0,2,1,0,0,0,2,1,2,2,1,1,1,1,2,0,1,2,2,0,0,
 2,1,1,0,0,1,1,0,0,1,1,1,2,2,1,0,2,2,2,2,1,2,0,2,0,0,1,2,2,2,2,2,2,1,1,1,2,2,0,2,
 2,1,2,2,2,2,2,2,0,2,1,0,0,2,2,0,1,2,1,2,2,0,2,2,2,0,2,2,2,0,2,0,1,2,2,1,1,1,2,0,
 2,0,0,1,2,0,1,2,0,0,0,2,2,2,1,0,0,1,1,0,0,1,2,0,0,2,1,2,1,1,1,2,0,2,2,0,0,2,0,0,
 0,2,2,0,0,0,1,2,2,1,2,1,0,0,1,1,0,0,1,1,2,2,2,2,1,1,2,0,2,2,0,0,2,1,0,1,2,1,2,0,
 0,2,1,2,1,2,0,0,2,1,2,0,0,2,2,0,0,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,2,1,0,1,1,
 2,0,1,1,2,2,0,2,2,2,1,1,1,2,2,0,1,2,2,0,0,1,0,1,0,2,0,0,0,1,2,1,2,1,1,1,2,0,2,2,
 2,0,0,2,2,0,0,2,1,0,0,2,2,2,0,0,2,1,0,2,2,1,2,2,0,2,2,2,0,1,2,0,1,1,0,2,1,0,0,2,
 1,2,1,2,0,1,2,2,1,1,2,0,1,2,2,0,2,0,2,0,0,1,2,2,1,2,2,1,0,2,0,0,2,2,0,2,0,0,0,0,
 1,0,1,2,1,2,2,0,1,2,1,0,1,2,1,0,2,2,0,2,2,0,0,1,2,1,0,0,2,1,2,0,0,0,2,1,2,0,0,2,
 2,1,0,2,2,1,2,2,0,2,0,1,2,2,0,0,0,2,2,2,1,0,0,2,2,1,2,2,0,2,1,2,0,2,1,2,2,2,0,2,
 1,0,0,2,2,0,2,2,2,2,2,2,0,0,2,1,2,0,0,2,2,2,0,2,1,1,0,1,0,2,1,1,2,0,0,2,2,0,2,2,
 1,2,0,0,2,1,2,1,0,0,2,2,0,2,2,2,2,1,2,0,2,2,2,2,2,2,0,1,1,0,2,2,2,2,2,0,1,1,2,2};

   /* corrected code courtesy of Michael Callahan */
   return(db_table[my_history[0] % 1000]);
}

int antirotnbot ()  /* Anti-rotn bot */
{
   /* observes rotations in opponent's sequence,
      exploits max or min, whichever difference is greater */
  
   /* crude implementation, could be simplified */

   static int no, up, dn, score;
   int mv, diff, diff2, small, med, large;

   mv = opp_history[0];
   if (mv == 0) {
      no = 0; up = 0; dn = 0; score = 0;
   }
   else {
      diff = (my_history[mv] - opp_history[mv] + 3) % 3;
      if ( diff == 1 ) { score++; }
      if ( diff == 2 ) { score--; }
      if (mv > 1) {
	 diff = (opp_history[mv] - opp_history[mv-1] + 3) % 3;
	 if (diff == 0) { no++; }
	 if (diff == 1) { up++; }
	 if (diff == 2) { dn++; }
      }
   }

   /* fail-safe at 4% of match length */
   if ( score < -trials/25 ) {
      return(random() % 3); }

   if ((no == up) && (no == dn)) {
      return(random() % 3); }

   /* sort */
   if ((no <= up) && (no <= dn)) {
      small = no;
      if (up <= dn) { med = up; large = dn; }
      else { med = dn; large = up; }
   }
   else if (up <= dn) {
      small = up;
      if (no <= dn) { med = no; large = dn; }
      else { med = dn; large = no; }
   }
   else {
      small = dn;
      if (no <= up) { med = no; large = up; }
      else { med = up; large = no; }
   }

   diff = med - small;    diff2 = large - med;

   if (diff < diff2) { /* clear maximum */
      if ((no > up) && (no > dn)) {
	 return((opp_history[opp_history[0]] + 1) % 3); }
      if ((up > no) && (up > dn)) {
	 return((opp_history[opp_history[0]] + 2) % 3); }
      if ((dn > no) && (dn > up)) {
	 return(opp_history[opp_history[0]]); }
   }
   else if (diff > diff2) { /* clear minimum */
      if ((dn < up) && (dn < no)) {
	 return((opp_history[opp_history[0]] + 1) % 3); }
      if ((up < dn) && (up < no)) {
	 return(opp_history[opp_history[0]]); }
      if ((no < dn) && (no < up)) {
	 return((opp_history[opp_history[0]] + 2) % 3); }
   }
   else if (diff == diff2) {
      if ((no > up) && (up > dn)) {
	 return((opp_history[opp_history[0]] + 1) % 3); }
      if ((dn > up) && (up > no)) {
	 if (flip_biased_coin(0.5)) {
	    return(opp_history[opp_history[0]]); }
	 else { return((opp_history[opp_history[0]] + 2) % 3); }
      }
      if ((dn > no) && (no > up)) {
	 return(opp_history[opp_history[0]]); }
      if ((up > no) && (no > dn)) {
	 if (flip_biased_coin(0.5)) {
	    return((opp_history[opp_history[0]] + 1) % 3); }
	 else { return((opp_history[opp_history[0]] + 2) % 3); }
      }
      if ((up > dn) && (dn > no)) {
	 return((opp_history[opp_history[0]] + 2) % 3); }
      if ((no > dn) && (dn > up)) {
	 if (flip_biased_coin(0.5)) {
	    return(opp_history[opp_history[0]]); }
	 else { return((opp_history[opp_history[0]] + 1) % 3); }
      }
   }
   printf("Error in antirotnbot decision tree!\n");
   return(0);
}

int driftbot ()  /* Copy-drift bot */
{
   /* bias decision by opponent's last move, but drift over time */
   /* max -EV = -0.50 ppt */

   static int gear;
   int mv, throw;

   mv = my_history[0];
   if (mv == 0) { 
      gear = 0;
      throw = random() % 3; }
   else {
      if (flip_biased_coin(0.5)) {    
	 throw = opp_history[mv]; }
      else { throw = random() % 3; }
      if ( mv % 111 == 0 ) {
	 gear += 2; }
   }
   return((throw + gear) % 3);
}

int addshiftbot3 ()  /* Add-react bot */
{
   /* base on sum of previous pair (my & opp), shift if losing */
   /* deterministic 80% of the time, thus max -EV = -0.800 ppt */

   static int gear, recent, score;
   int mv, diff;

   mv = my_history[0];
   if (mv == 0) {
      gear = 0; recent = 0; score = 0;
      return( random() % 3 );
   }
   else {
      diff = (my_history[mv] - opp_history[mv] + 3) % 3;
      if ( diff == 1 ) { score++; }
      if ( diff == 2 ) { score--; }
      recent++;
   }

   if (((recent <= 20) && (score <= -3)) ||
       ((recent >  20) && (score <= -recent/10))) {
      /* printf("switching gears at turn %d (%d / %d)\n", mv, score, recent); */
      gear += 2;
      recent = 0;
      score = 0;
   }
   if ( flip_biased_coin(0.2) ) {
      return( random() % 3 ); }
   else {
      return((my_history[mv] + opp_history[mv] + gear) % 3);
   }
}

int adddriftbot2 ()  /* Add-drift bot */
{
   /* base on sum of previous pair (my & opp), drift over time */
   /* deterministic 50% of the time, thus max -EV = -0.500 ppt */

   static int gear;
   int mv;

   mv = my_history[0];
   if (mv == 0) {
      gear = 0;
      return( random() % 3 );
   }
   else if ( mv % 200 == 0 ) { gear += 2; }

   if ( flip_biased_coin(0.5) ) {
      return( random() % 3 ); }
   else {
      return((my_history[mv] + opp_history[mv] + gear) % 3);
   }
}
/**********************************************************************/