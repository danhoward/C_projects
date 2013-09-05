/*
*   basic implementation for gcd simplifying fractions
*   ideas is based on for u and v if u > v then gcd of u and v is also gcd of v and u-v
*   in while loop of gcd set a conditional swap of u and v if u < v 
*/
#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>

double calculate(const struct rusage* b, const struct rusage* a);

int gcd(int u, int v) {
	int t;
	while (u > 0) {
		if ( u < v) {
			t = u;
			u = v;
			v = t;
		}
		u = u % v;
	}
	return v;
}

int main(void) {
	struct rusage before, after;
	double ti_calc = 0.0;

	int x, y;
	x = 40;
	y = 20;
	while (scanf("%d %d", &x, &y) != EOF) {
		if (x > 0 && y > 0)
			getrusage(RUSAGE_SELF, &before);
			printf("%d %d %d\n", x, y, gcd(x,y));
			getrusage(RUSAGE_SELF, &after);
			ti_calc = calculate(&before, &after);
			printf("\nTime to calculate 		%.6f\n", ti_calc);
	}
	return 0;
}


double calculate(const struct rusage* b, const struct rusage* a) {
	if (b == NULL || a == NULL) {
		return 0.0;
	}
	else {
		return ((((a->ru_utime.tv_sec * 1000000 + a->ru_utime.tv_usec) -
				  (b->ru_utime.tv_sec * 1000000 + b->ru_utime.tv_usec)) +
				 ((a->ru_stime.tv_sec * 1000000 + b->ru_stime.tv_usec) -
				  (b->ru_stime.tv_sec * 1000000 + b->ru_stime.tv_usec)))
				 / 1000000.0);
	}
}

