#ifndef polynomial_h
#define polynomial_h
#include<vector>
#include<iostream>
using namespace std;

class polynomial
{
public:
	static polynomial* running() {
		return run = (run != nullptr) ? run : new polynomial();
	}
	void lagrange();
	void newton();
	bool equalSpacing();
	void backward();
	void forward();
	void setter();
	void getter();

private:
	vector <vector<double> > difference;
	vector <vector<double> > delta;
	vector <vector<double> > P_n;
	vector <double> xi;
	vector <double> yi;
	double x;
	double y;
	int n;
	static polynomial* run;
};

#endif // !polynomial_h
