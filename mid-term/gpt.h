#ifndef gpt_h
#define gpt_h
#include<vector>
#include<iostream>
#include <cmath>
using namespace std;

class gpt
{
public:
	static gpt* running() {
		return run = (run != nullptr) ? run : new gpt();
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
	double l, r;
	double TOL;
	double x, prev;
	double y;
	int cnt;
	static gpt* run;
	double fx(double value);
	double Dfx(double value);
	double Dfxx(double value);
};

#endif // !gpt_h
