#ifndef bptt_h
#define bptt_h
#include<vector>
#include<iostream>
#include <cmath>
using namespace std;

class bptt
{
public:
	static bptt* running() {
		return run = (run != nullptr) ? run : new bptt();
	}
	void chiadoi();
	void diembatdong();
	void newton();
	void daycung();
	void diemsai();
	void setter();
	void getter();
	bool error();

private:
	const double PI = 3.141592653589793238463;
	const double EULER = 2.71828182845904523536;
	double h, x;
	static bptt* run;
	double fx(double value);
	double Dfx(double value);
};

#endif // !bptt_h
