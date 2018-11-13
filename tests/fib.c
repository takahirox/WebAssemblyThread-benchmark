#include <pthread.h>
#include <stdio.h>

int fib(int n) {
  if (n == 1) return 1;
  if (n == 2) return 1;
  return fib(n - 1) + fib(n - 2);
}

void* bgFunc(void *arg) {
  *(int*)arg = fib(*(int*)arg);
  return arg;
}

int fibThread(int n) {
  if (n == 1) return 1;
  if (n == 2) return 1;

  int arg1 = n - 2, arg2 = n - 1;
  int *status1, *status2;
  pthread_t thread1, thread2;

  if(pthread_create(&thread1, NULL, bgFunc, &arg1)) {
    perror("Thread create failed");
    return 0;
  }

  if(pthread_create(&thread2, NULL, bgFunc, &arg2)) {
    perror("Thread create failed");
    return 0;
  }

  if(pthread_join(thread1, (void**)&status1)) {
    perror("Thread join failed");
    return 0;
  }

  if(pthread_join(thread2, (void**)&status2)) {
    perror("Thread join failed");
    return 0;
  }

  return *(int*)status1 + *(int*)status2;
}
