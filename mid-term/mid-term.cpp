#include <iostream>
#include "setOfEquations.h"
#include "polynomial.h"
#include "spline.h"

using namespace std;

void equations() {
    cout << "0->cholesky        1->detroittle       2->eliminationGauss         3->cramer       4->gaussSeidel    5->jacobi\n";
    int choice; cin >> choice;
    setOfEquations::running()->setter();
    if (setOfEquations::running()->canSolve()) {
        switch (choice) {
        case 0:
            if (setOfEquations::running()->cholesky()) {
                setOfEquations::running()->getter();
            }
            break;
        case 1:
            setOfEquations::running()->detroittle();
            setOfEquations::running()->getter();
            break;
        case 2:
            setOfEquations::running()->eliminationGauss();
            setOfEquations::running()->getter();
            break;
        case 3:
            setOfEquations::running()->cramer();
            setOfEquations::running()->getter();
            break;
        case 4:
            setOfEquations::running()->gaussSeidel();
            setOfEquations::running()->getter();
            break;
        case 5:
            setOfEquations::running()->jacobi();
            setOfEquations::running()->getter();
            break;
        default:
            break;
        }
    }
}

void polynomial() {
    cout << "0->lagrange        1->newton           2->backward                 3->forward\n";
    int choice; cin >> choice;
    polynomial::running()->setter();
    switch (choice) {
    case 0:
        polynomial::running()->lagrange();
        polynomial::running()->getter();
        break;
    case 1:
        polynomial::running()->newton();
        polynomial::running()->getter();
        break;
    case 2:
        if (!polynomial::running()->equalSpacing()) {
            cout << "request equal spacing" << '\n';
            break;
        }
        polynomial::running()->backward();
        polynomial::running()->getter();
        break;
    case 3:
        if (!polynomial::running()->equalSpacing()) {
            cout << "request equal spacing" << '\n';
            break;
        }
        polynomial::running()->forward();
        polynomial::running()->getter();
        break;
    default:
        break;
    }
}

void spline() {
    int choice; cin >> choice;
}

int main()
{
    bool run = true;

    while (run) {
        cout << "1->setOfEquations          2->polynomial       3->spline       0->quit\n";
        int choice; cin >> choice;
        switch (choice) {
            case 0:
                run = false;
                break;
            case 1:
                equations();
                break;
            case 2:
                polynomial();
                break;
            case 3:
                spline();
                break;
            default:
                break;
        }
    }
  return 0;
}
/*
2 2 5 
5 150
7 392
11 1452
13 2366
17 5202
9
*/