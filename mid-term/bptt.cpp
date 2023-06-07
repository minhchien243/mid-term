#include "bptt.h"

double bptt::fx(double value) {
	return sqrt(2 * PI) * pow(EULER, - value * value / 2);
}

void bptt::setter() {
	h = 0.1;
	x = 0;
}