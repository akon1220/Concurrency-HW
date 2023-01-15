#include <stdio.h>
#include <stdlib.h>
#include "mythreads.h"

long gvar = 20;

void *thread_hello(void *args) {
  long lvar = 0;
  printf("%s: Before local %ld global %ld\n",(char *) args, lvar, gvar);
  lvar = random();
  printf("%s: After local %ld global %ld\n",(char *) args, lvar, gvar);
  return NULL;
}

int main (int argc, char **argv)
{
  pthread_t p1, p2;
  Pthread_create(&p1,NULL,thread_hello,"A");
  Pthread_create(&p2,NULL,thread_hello,"B");
  Pthread_join(p1,NULL);
  Pthread_join(p2,NULL);
  printf("main: gvar %ld\n", gvar);
  return (0);
}
