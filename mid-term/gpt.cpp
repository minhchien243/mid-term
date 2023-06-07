#include "gpt.h"

using namespace std;

gpt* gpt::run = nullptr;

double gpt::fx(double value) {
	return sin(value);
}

double gpt::Dfx(double value) {
	return (fx(value + TOL) - fx(TOL)) / TOL;
}

bool gpt::error() {
	return abs(fx(x) - sin(prev)) > TOL;
}

void gpt::chiadoi() {
	while (error()) {
		double mid = (l + r) / 2;
		if (fx(mid) > 0) {
			l = mid;
		}
		else {
			r = mid;
		}
		prev = x;
		x = mid;
		++cnt;
	}
}

void gpt::diembatdong() {
	while (error()) {
		prev = x;
		x = fx(x) + x;
		++cnt;
	}
}

void gpt::newton() {
	while (error()) {
		prev = x;
		x = x - fx(x) / Dfxx(x);
		++cnt;
	}
}

void gpt::daycung() {
	while (error()) {
		double tmp = x;
		x = x - (fx(x) * (x - prev)) / (fx(x) - fx(prev));
		prev = tmp;
		++cnt;
	}
}

void gpt::diemsai() {
	while (error()) {
		double p = (l * fx(r) - r * fx(l)) / (fx(r) - fx(l));
		if (fx(p) < 0) {
			l = p;
		}
		else {
			r = p;
		}
		prev = x;
		x = p;
		cnt++; 
	}
}

void gpt::setter() {
	cout << "l & r:" << '\n';
	//cin >> l >> r;
	l = 3, r = 4;
	TOL = 0.000000001;
	prev = r;
	x = l;
}

void gpt::getter() {
	cout << x << " " << cnt << '\n';
}