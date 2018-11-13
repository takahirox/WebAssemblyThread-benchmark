#include <pthread.h>
#include <stdio.h>

void multiplyDoubleVec(double *src1, double *src2, double *res, int n) {
  for (int i = 0; i < n; i++) {
    res[i] = src1[i] * src2[i];
  }
}

struct argument {
  double *src1;
  double *src2;
  double *res;
  int n;
};

void* bgFunc(void *arg) {
  struct argument *a = (struct argument*)arg;
  multiplyDoubleVec(a->src1, a->src2, a->res, a->n);
  return arg;
}

void multiplyDoubleVecThread(double *src1, double *src2, double *res, int n) {
  int n1 = n / 2;
  int n2 = n - n1;
  pthread_t thread1, thread2;

  struct argument arg1, arg2;
  arg1.src1 = src1;
  arg1.src2 = src2;
  arg1.res = res;
  arg1.n = n1;
  arg2.src1 = src1 + n1;
  arg2.src2 = src2 + n1;
  arg2.res = res + n1;
  arg2.n = n2;

  if(pthread_create(&thread1, NULL, bgFunc, &arg1)) {
    perror("Thread create failed");
    return;
  }
  if(pthread_create(&thread2, NULL, bgFunc, &arg2)) {
    perror("Thread create failed");
    return;
  }

  if(pthread_join(thread1, NULL)) {
    perror("Thread join failed");
    return;
  }
  if(pthread_join(thread2, NULL)) {
    perror("Thread join failed");
    return;
  }
}
