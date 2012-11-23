#include <stdio.h>
#include <stdlib.h>
#define ROCK 0
#define PAPER 1
#define SCISSORS 2

#define P "Elevator"

#define m(O) M[c-O]
#define j(O) J[c-O]
#define u(O,Q) o[O*3+Q]
#define lo rand()%3
#define v(O) scanf("%d",O)
#define f fflush(stdout)
#define Z int
#define r sizeof
#define a(O) malloc(r(Z)*O)
#define z(O) memset(n,0,r(O))
#define pi printf
#define y(O) return O

Z o[9];Z main(){char*Q=P;Z*M,*J,c,d,s,h;pi("%s\n",Q);h=
Q[2]>>1;c=0;f;v(&s);srand(s);v(&d);M=a(d);J=a(d);for(;;
){if(*Q?(h^=*Q++,0):h)y(1);pi("%d\n",M[c]=((c<2)?lo:((u
(m(1),(u(m(2),j(2))=j(1)))+1)%3)));f;v(J+c);c++;}y(0);}