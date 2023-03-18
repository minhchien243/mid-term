#include "polynomial.h"

using namespace std;

polynomial* polynomial::run = nullptr;

void polynomial::lagrange() {
	for (int i = 0; i < n; ++i) {
		double p = 1;
		for (int j = 0; j < n; ++j) {
			if (i != j) {
				p = p * (x - xi[j]) / (xi[i] - xi[j]);
			}
		}
		y = y + p * yi[i];
	}
}

void polynomial::newton() {
	for (int i = 0; i < n; ++i) {
		difference[i][0] = yi[i];
	}

	for (int j = 1; j < n; ++j) {
		for (int i = 0; i < n - j; ++i) {
			difference[i][j] = (difference[i + 1][j - 1] - difference[i][j - 1]) / (xi[i + j] - xi[i]);
		}
	}

	for (int i = 0; i < n; ++i) {
		double multi = 1;
		for (int j = 0; j < i; ++j) {
			multi = multi * (x - xi[j]);
		}
		y = y + difference[0][i] * multi;
	}
}

bool polynomial::equalSpacing() {
	for (int i = 1; i < n - 1; ++i) {
		if (xi[i] - xi[i - 1] != xi[i + 1] - xi[i]) {
			return false;
		}
	}
	return true;
}

void polynomial::backward() {
	double h = xi[1] - xi[0];
	for (int i = 0; i < n; ++i) {
		delta[i][0] = yi[i];
	}

	for (int j = 1; j < n; ++j) {
		for (int i = n - 1; i >= j; --i) {
			delta[i][j] = delta[i][j - 1] - delta[i - 1][j - 1];
		}
	}

	double s = (x - xi[n - 1]) / h;

	vector <int> fac(n + 1, 1);
	for (int i = 2; i <= n; ++i) {
		fac[i] = fac[i - 1] * i;
	}
	for (int i = 0; i < n; ++i) {
		double multi = 1;
		for (int j = 0; j < i; ++j) {
			multi = multi * (s + j);
		}
		multi = multi / fac[i];
		y = y + multi * delta[n - 1][i];
	}
}

void polynomial::forward() {
	double h = xi[1] - xi[0];
	for (int i = 0; i < n; ++i) {
		delta[i][0] = yi[i];
	}

	for (int j = 1; j < n; ++j) {
		for (int i = 0; i < n - j; ++i) {
			delta[i][j] = (delta[i + 1][j - 1] - delta[i][j - 1]);
		}
	}

	double s = (x - xi[0]) / h;
	vector <int> fac(n + 1, 1);
	for (int i = 2; i <= n; ++i) {
		fac[i] = fac[i - 1] * i;
	}
	for (int i = 0; i < n; ++i) {
		double multi = 1;
		for (int j = 0; j < i; ++j) {
			multi = multi * (s - j);
		}
		multi = multi / fac[i];
		y = y + multi * delta[0][i];
	}
}

void polynomial::setter() {
	cout << "enter quantity: \n";
	cin >> n;
	xi.resize(n);
	yi.resize(n);
	difference.resize(n);
	delta.resize(n);
	cout << "enter point: \n";
	for (int i = 0; i < n; ++i) {
		cin >> xi[i] >> yi[i];
		delta[i].resize(n);
		difference[i].resize(n);
	}
	cout << "enter x: \n";
	cin >> x;
}

void polynomial::getter() {
	cout << y << '\n';
}