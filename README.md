This is your first lab getting familiar with concurrency through the use
of posix threads.  

There are three .c files, but only one that you have to implement. The first two,
thread1.c and thread2.c, are for you to compile and run just to see the thread
interface in action and to show the difference between local and global (shared) state
in a multithreaded program.

Your programming task is thread3.c where you are to complete the program by
finishing the `thread_double` and `main` routines.  

---

**Pthread library**

As with the fork/exec labs, we are using some wrapper functions that replace the default 
library functions. You must use use posix thread calls with a capital 'P' (e.g., `Pthread_create` instead of `pthread_create`).
The arguments are the same as the pthread library routines.  The autograder requires
that you use the given capital letter functions in order to measure the 
correctness of the program. See [mythreads.h](mythreads.h) for function declarations.

---
**thread3.c**

**thread_double**: Takes a pointer to an `args_t` structure (cast as a void* per the pthread API) which
provides an integer id as well as a start and end index into the global `array`. The function should:
1. First, call the function `print_thread_info()` to print the current process and thread ID.
2. Then, call the function `print_args()` to print the input args. `print_args()` needs a `arg_t` which means you will have to cast argin to an `arg_t` type before passing it to the `print_args()` function.
3. Multiply each entry within its range (start <= index < end) in `array` by 2. The start index and end index can be found from `argin` casted to a `arg_t` variable and by accessing its fields.
4. Use printf with format `"%ld done\n"` to print the thread's id returned from the `Thread_getid()` function right before returning from the function.

**main**: you need to create 4 threads that each operate on 1/4 of the global `array`.
You need to allocate and initialize the `arg_t` argument structures appropriately.
You should assign the child threads ids 0-3 based on which part of the array they
are accessing, where thread 0 has a start index of 0 and thread 3 has an end index
of 1000.
The `main` routine should wait for all four child threads to complete before continuing
to the finish up code provided.

You can run the programs manually on the command line to quickly see their print outputs.
Compare them to the example output below--the only differences should be that (1) your
program can print different thread `tid` values and (2) the threads can execute in any order.

**Example output for thread3:** 
```
main: before 499500
tid 56719 id 0 start 0 end 250
56719 done
tid 56720 id 1 start 250 end 500
56720 done
tid 56721 id 2 start 500 end 750
56721 done
tid 56722 id 3 start 750 end 1000
56722 done
main: result 999000
```

---

**Local Testing and Submission**

To run the test harness, use the following command
```bash
python3 test_kit.py ALL
```
Submit your completed thread3.c to Gradescope.
