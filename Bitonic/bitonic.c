#include <stdio.h>
#include <stdlib.h>
#ifdef _OPENMP
#include <omp.h>
#endif

// #define DEBUG
#define PRIVATE static


// PROTOTYPES //
PRIVATE void init(int N, double *a);
PRIVATE void bitonic_sorter(int N, double *a);
PRIVATE void make_cleaner(int N, int h, int *tab);
PRIVATE void make_cleaner_r(int N, int h, int *tab);
PRIVATE void print_tab(int *tab, int N);
PRIVATE void do_parallel(int *tab, double *a, int N);

void init(int N, double *a){
  int i;
  for (i = 0; i < N; i++){
    a[i] = (double)rand()/ RAND_MAX;
  }
}

void print_tab(int *tab, int N){
  int i;
  for (i = 0; i < N; i++){
    if (i > 0) putchar(',');
    printf("%d", tab[i]);
  }
  putchar('\n');
}

void bitonic_sorter(int N, double *a){
  int w;
  int *tab;
  tab = (int *)malloc(sizeof(int) * N);
  for (w = 2; w <= N; w *= 2){
    int h;
#ifdef DEBUG
    printf("w = %d\n", w);
#endif
    for (h = w; h >= 2; h /= 2){
#ifdef DEBUG
      printf("  h = %d\n", h);
#endif
      if (h == w) make_cleaner_r(N, h, tab);
      else make_cleaner(N, h, tab);
#ifdef DEBUG
      print_tab(tab, N);
#endif
      do_parallel(tab, a, N);
    }
  }
}

void make_cleaner(int N, int h, int *tab){
  int t = 0;
  for (int base = 0; base < N; base += h){
    for (int i = 0; i < h / 2; i++){
      tab[t++] = base + i;
      tab[t++] = base + i + h / 2;
    }
  }
}

void make_cleaner_r(int N, int h, int *tab){
  int t = 0;
  for (int base = 0; base < N; base += h){
    for (int i = 0; i < h / 2; i++){
      tab[t++] = base + i;
      tab[t++] = base + h - 1 - i;
    }
  }
}

void do_parallel(int *tab, double *a, int N){
  int i;
#pragma omp parallel for
  for (i = 0; i < N; i += 2){
    int i1 = tab[i];
    int i2 = tab[i + 1];
    double v1 = a[i1];
    double v2 = a[i2];
    if (v1 > v2) {
      a[i2] = v1;
      a[i1] = v2;
    }
  }
}

void check(int N, double *a){
  int i;
  for (i = 0; i < N - 1; i++){
    if (a[i] > a[i + 1]){
      printf("the answer is NOT correct!(%d)\n", i);
      return;
    }
  }
  printf("the answer is correct!\n");
}

int main(){
  int N = 1048576 * 2 * 4;  /* N should be a power of 2 */
  // int N = 32;  /* N should be a power of 2 */
  int i;
  double *a = (double *)malloc(sizeof(double) * N);

  printf("N = %d\n", N);
#ifdef _OPENMP
  printf("The number of processors is %d\n", omp_get_num_procs());
#endif
  init(N, a);
  bitonic_sorter(N, a);
#if 0
  for (i = 0; i < N; i++){
    printf("%f  ", a[i]);
  }
  putchar('\n');
#endif
  printf("%20.18f:%20.18f:%20.18f\n", a[0], a[N / 2], a[N - 1]);
  check(N, a);
  return 0;
}
