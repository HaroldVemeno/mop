#include <stdio.h>
#include <stdlib.h>

int compute_maximum(int);

int get_value_or_set_data(int i, int n, int *arr) {
  static int N = 0;
  static int a[3000000+5];
  static int Q = 0;
  const int MAXQ = 35;
  static bool fst = true;

  if (fst) {
    N = n;
    for (int i = 0; i < N; ++i) {
      a[i] = arr[i];
    }
    fst = false;
    return 0;
  }

  if(i < 0 || i >= N) {
    printf("err: Index out of range\n");
    exit(0);
  }
  
  ++Q;
  
  if(Q > MAXQ) {
    printf("err: Too many queries\n");
    exit(0);
  }

  return a[i];
}

int get_value(int i) {
  return get_value_or_set_data(i, -1, NULL);
}

int main() {
  int N;
  static int arr[3000000+5];
  if (scanf("%d", &N) != 1) {
    printf("err: Unexpected error\n");
    return 0;
  }
  for(int i = 0; i < N; ++i){
    if (scanf("%d", &arr[i]) != 1) {
      printf("err: Unexpected error\n");
      return 0;
    }
  }
  get_value_or_set_data(0, N, arr);
  printf("max: %d\n", compute_maximum(N));
}
