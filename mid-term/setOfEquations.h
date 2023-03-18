#ifndef SETOFEQUATIONS_H
#define SETOFEQUATIONS_H
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class setOfEquations
{
public:
    static setOfEquations* running() {
        return run = (run != nullptr) ? run : new setOfEquations();
    }
    bool cholesky();
    void detroittle();
    void eliminationGauss();
    void cramer();
    void jacobi();
    void gaussSeidel();
    bool canSolve();
    void setter();
    void getter();
    vector<double> solveLowerTriangle(vector<vector<double> > L, vector<double> _b);
    vector<double> solveUpperTriangle(vector<vector<double> > U, vector<double> _b);

protected:

private:
    int n;
    vector<vector<double> > matrix;
    vector<double> b;
    vector<double> ans;
    double TOL;
    int count;
    static setOfEquations* run;
};

#endif // SETOFEQUATIONS_H
