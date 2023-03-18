#ifndef spline_h
#define spline_h
#include<vector>
#include<iostream>
using namespace std;

class spline
{
public:
	static spline* running() {
		return run = (run != nullptr) ? run : new spline();
	}
	void getter();
	void setter();
	void solveSpline();

private:
	int n;
	vector<double> xi;
	vector<double> ai, bi, ci, di;
	vector<double> hi;
	vector<double> l, u, z, a;
	static spline* run;
};

#endif // !spline_h
