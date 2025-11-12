#include "header.h"

int npow(int base, int exp) {
	if (exp == 0) {return 1;} else {return base * npow(base, exp-1);}
}
int sumpow(int base, int exp) {
	if (exp == 0) {return 1;} else {return base * sumpow(base, exp-1) + 1;}
}
int fact(int n) {
	if (n==0) {return 1;} else {return n * fact(n-1);}
}
int bin(int n, int k) {
	return fact(n) / (fact(k) * fact(n-k));
}
int ithdigit(int n, int i, int base) {
	return (n / npow(base, i)) % base;
}
