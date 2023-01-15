#include <stdio.h>
#include "mythreads.h"

void *thread_hello(void *args) {
  printf("Hello from thread %s\n",(char *) args);
  return NULL;
}

int main (int argc, char **argv)
{
  
  pthread_t p1, p2;
  Pthread_create(&p1,NULL,thread_hello,"Yogi");
  Pthread_create(&p2,NULL,thread_hello,"Bear");
  Pthread_join(p1,NULL);
  Pthread_join(p2,NULL);
  printf("Hello World from main!\n");

  return (0);
}
