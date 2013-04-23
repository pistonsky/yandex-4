#include "stdio.h"

int main (int argc, char *argv[]) {
  int K1 = atoi(argv[1]);
  int M = atoi(argv[2]);
  int K2 = atoi(argv[3]);
  int P2 = atoi(argv[4]);
  int N2 = atoi(argv[5]);
  int P1;
  int N1;
  int P1_undef; // a flag, to check if there are more than one possible P1 values
  int N1_undef; // a flag, to check if there are more than one possible N1 values
  int P_; // for storing the next possible P1 value
  int N_; // for storing the next possible N1 value
  int X; // apartments in section
  int min; // minimum possible number of apts in section
  int max; // maximum possible number of apts in section
  if (P2==1 && N2==1) { // to prevent division by 0
    if (K1 <= K2) {
      printf("1 1");
    } else {
      P1 = (K1-1) / (M*K2) + 1; // this is the maximum P1
      if (P1 > 1) {
        if (M == 1) {
          printf("0 1");
        } else {
          printf("0 0");
        } 
      }else {
        printf("1 0");
      }
    }
  } else if (K2==1) { // apartment 1, but not on the first floor or at the first elevator?
    printf("-1 -1");
  } else {
    // determine how many apartments in each section could there possibly be
    min = (K2-1)/((P2-1)*M+N2)+1;
    max = (K2-1)/((P2-1)*M+N2-1);
    if (min > max) {
      printf("-1 -1");
    } else if (min == max) {
      X = min;
      P1 = (K1-1) / (M*X) + 1;
      N1 = (K1-1 - (P1-1)*M*X) / X + 1;
      printf("%d %d",P1,N1);
    } else {
      X = min;
      P1 = (K1-1)/(M*X)+1;
      N1 = (K1-1-(P1-1)*M*X)/X+1;
      P1_undef = 0;
      N1_undef = 0;
      for (X=min+1;X<=max;X++) {
        P_ = (K1-1)/(M*X)+1;
        N_ = (K1-1-(P_-1)*M*X)/X+1;
        if (P_ != P1) P1_undef = 1;
        if (N_ != N1) N1_undef = 1;
      }
      if (P1_undef && N1_undef)
        printf("0 0");
      else if (P1_undef)
        printf("0 %d",N1);
      else if (N1_undef)
        printf("%d 0",P1);
      else
        printf("%d %d",P1,N1);
    }
  }
  return 0;
}