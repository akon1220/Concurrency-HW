#include <stdio.h>
#include <stdlib.h>
#include "mythreads.h"


#define SIZE 1000
#define NUM_THREADS 4


static int array[SIZE];

typedef struct {
  unsigned int id;
  unsigned int start;
  unsigned int end;
} args_t;

void print_args(args_t *args) {
  printf("args: id %d start %d end %d\n", args->id, args->start, args->end);
}

void *thread_double(void *argin) {
  print_thread_info();
  //cast to arg_t type
  args_t *new_type = (args_t*) argin;
  print_args(argin);

  for (int i=new_type->start; i<new_type->end; i++) {
    array[i] = array[i]*2;
  }
  long thread_id = Thread_gettid();
  printf("%ld done\n", thread_id);

  // fill in this function to have the thread update its range of array entries
  // each entry in the array should be multiplied by 2.
  // also call print_thread_info
  return NULL;
}

int main (int argc, char **argv)
{
  pthread_t threads[4];
  args_t args[4];

  // initialize the global array
  for (int j = 0; j < SIZE; j++) {
    array[j] = j;
  }

  int sum = 0;
  for (int i =0; i < SIZE; i++) {
    sum += array[i];
  }
  printf("main: before %d\n",sum);

  // fill in this portion to create 4 threads that operate on 1/4 of the array
  // you need to setup the arg structure appriately
  // main should use join to wait for all four threads to finish before executing the finish up code

  //indexes for splitting up array into 4 equal sections
  unsigned int begin = 0;
  unsigned int end = 250;
  //loop through array 4 times in chunks of 250
  for (int i=0; i<4; i++) {
    args[i].start = begin;
    args[i].end = end;
    begin+=250;
    end+=250;
    //create thread for each chunk
    Pthread_create(&threads[i], NULL, thread_double, (void*) &args[i]);
    //return NULL since do not care about the return value
    Pthread_join(threads[i], NULL);
  }

  // main finish up code.
  sum = 0;
  for (int i =0; i < SIZE; i++) {
    sum += array[i];
  }
  printf("main: result %d\n",sum);

  return (0);
}
