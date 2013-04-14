#include "stdio.h"

int main (int argc, char *argv[])
{
	int K1 = atoi(argv[1]);
	int M = atoi(argv[2]);
	int K2 = atoi(argv[3]);
	int P2 = atoi(argv[4]);
	int N2 = atoi(argv[5]);
	if (P2==1 && N2==1) { // to prevent division by 0
		if (K1 <= K2)
			printf("1 1");
		else {
			int P1 = (K1-1) / (M*K2) + 1; // this is the maximum P1
			if (P1 > 1) {
				if (M == 1)
					printf("0 1");
				else
					printf("0 0");
			} else
				printf("1 0");
		}
	}
	else if (K2==1) { // apartment 1, but not on the first floor or at the first elevator?
		printf("-1 -1");
	} else {
		int X = 0; // apartments in section
		// determine what X could possibly be
		int min = (K2-1)/((P2-1)*M+N2)+1;
		int max = (K2-1)/((P2-1)*M+N2-1);
		if (min > max) {
			printf("-1 -1");
		}
		else if (min == max) {
			X = min;
			int P1 = (K1-1) / (M*X) + 1;
			int N1 = (K1-1 - (P1-1)*M*X) / X + 1;
			printf("%d %d",P1,N1);
		}
		else {
			X = min;
			int P1 = (K1-1)/(M*X)+1;
			int N1 = (K1-1-(P1-1)*M*X)/X+1;
			int P1_undef = 0;
			int N1_undef = 0;
			int P_;
			int N_;
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