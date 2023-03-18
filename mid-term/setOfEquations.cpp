#include "setOfEquations.h"
#include <iomanip>
#include <math.h>
#include <algorithm>
#include "general.h"

setOfEquations* setOfEquations::run = nullptr;

bool setOfEquations::cholesky() {
    ans.resize(n);
    bool spd = true;
    for (int i = 0; i < n; ++i) {
        if (matrix[i][i] < 0) spd = false;
        for (int j = 0; j < i; ++j) {
            if (matrix[i][j] != matrix[j][i]) {
                spd = false;
            }
        }
    }

    vector<vector<double> > L(n, vector<double>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            if (i == 0 && j == 0) L[0][0] = sqrt(matrix[0][0]);
            else if (j == 0) {
                L[i][j] = matrix[i][0] / L[0][0];
            }
            else if (i == j) {
                double sum = sumL(L, i, j);
                (matrix[i][j] - sum > 0) ? L[i][j] = sqrt(matrix[i][j] - sum) : spd = false;
            }
            else {
                L[i][j] = 1 / L[j][j] * (matrix[i][j] - sumL(L, i, j));
            }
        }
        if (spd == false) break;
    }

    if (spd) {
        ans = solveLowerTriangle(L, b);
        ans = solveUpperTriangle(transposeMatrix(L), ans);
    }
    else {
        cout << "must be symmetric positive-definite matrix" << '\n';
    }

    return spd;
}

void setOfEquations::detroittle() {
    ans.resize(n);
    vector<vector<double> > L(n, vector<double>(n));
    vector<vector<double> > U(n, vector<double>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            L[i][j] = (i == j ? 1 : inf);
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            U[i][j] = inf;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double tmp = 0;
            double rate = 0;
            for (int k = 0; k < n; ++k) {
                if (i < k || k > j) continue;
                if (L[i][k] != inf && U[k][j] != inf) {
                    tmp += L[i][k] * U[k][j];
                }
                else {
                    rate = (i > j ? U[k][j] : L[i][k]);
                }
            }
            if (i > j) {
                L[i][j] = (matrix[i][j] - tmp) / rate;
            }
            else {
                U[i][j] = (matrix[i][j] - tmp) / rate;
            }
        }
    }


    ans = solveLowerTriangle(L, b);
    ans = solveUpperTriangle(U, ans);
    return;
}

void setOfEquations::eliminationGauss() {
    ans.resize(n);
    for (int k = 0; k < n; ++k) {
        int kMax = k;
        double vMax = matrix[k][k];

        for (int i = k + 1; i < n; ++i) {
            if (abs(matrix[i][k]) > vMax) {
                vMax = abs(matrix[i][k]);
                kMax = i;
            }
        }

        if (kMax != k) {
            for (int i = 0; i < n; ++i) {
                swap(matrix[kMax][i], matrix[k][i]);
            }
            swap(b[kMax], b[k]);
        }

        for (int i = k + 1; i < n; ++i) {
            double rate = matrix[i][k] / matrix[k][k];
            for (int j = 0; j < n; ++j) {
                matrix[i][j] -= matrix[k][j] * rate;
            }
            b[i] -= b[k] * rate;
        }
    }
    ans = solveUpperTriangle(matrix, b);
    return;
}

void setOfEquations::cramer() {
    ans.resize(n);
    for (int i = 0; i < n; ++i) {
        ans[i] = determinantOfMatrix(n, subAi(matrix, b, i)) / determinantOfMatrix(n, matrix);
    }
    return;
}

void setOfEquations::gaussSeidel() {
    vector<double> x0 (n, 0);
    ans.resize(n);
    while (count < 1000) {
        for (int i = 0; i < n; ++i) {
            double val = 0;
            for (int j = 0; j < i; ++j) {
                val = val - matrix[i][j] * ans[j];
            }
            for (int j = i + 1; j < n; ++j) {
                val = val - matrix[i][j] * x0[j];
            }

            ans[i] = (val + b[i]) / matrix[i][i];
        }
        ++count;

        double num = 0;
        for (int i = 0; i < n; ++i) {
            num = max(num, abs(ans[i] - x0[i]));
        }
        if (num < TOL) {
            break;
        }
     
        for (int i = 0; i < n; ++i) {
            x0[i] = ans[i];
        }
    }
}

void setOfEquations::jacobi() {
    vector<double> x0(n, 0);
    ans.resize(n);
    while (count <= 1000) {
        for (int i = 0; i < n; ++i) {
            double val = 0;
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;
                val = val - matrix[i][j] * x0[j];
            }

            ans[i] = (val + b[i]) / matrix[i][i];
        }
        ++count;

        double num = 0;
        for (int i = 0; i < n; ++i) {
            num = max(num, abs(ans[i] - x0[i]));
        }
        if (num < TOL) {
            break;
        }
        
        for (int i = 0; i < n; ++i) {
            x0[i] = ans[i];
     
        }
    }
}

bool setOfEquations::canSolve() {
    if (determinantOfMatrix(n, matrix) == 0) {
        int frag = 0;
        for (int i = 0; i < n; ++i) {
            frag |= (bool)determinantOfMatrix(n, subAi(matrix, b, i));
            cout << determinantOfMatrix(n, subAi(matrix, b, i)) << endl;
        }
        if (frag) {
            cout << "no solution" << endl;
        }
        else {
            cout << "infinite solutions" << endl;
        }
        return false;
    }
    return true;
}

void setOfEquations::setter() {
    cout << "enter size:\n";
    cin >> n;
    matrix.resize(n);
    b.resize(n);
    for (int i = 0; i < n; ++i) {
        matrix[i].resize(n);
    }
    cout << "enter augmented matrix: \n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (j == n) cin >> b[i];
            else cin >> matrix[i][j];
        }
    }
    cout << "enter TOL (10^-TOL): \n";
    cin >> TOL;
    TOL = pow(10, -TOL);
    count = 0;
}

vector<double> setOfEquations::solveUpperTriangle(vector<vector<double> > L, vector<double> _b) {
    vector<double> rep(n);
    for (int i = n - 1; i >= 0; --i) {
        double tmp = _b[i];
        for (int j = i + 1; j < n; ++j) {
            tmp -= L[i][j] * rep[j];
        }
        rep[i] = tmp / L[i][i];
    }
    return rep;
}

vector<double> setOfEquations::solveLowerTriangle(vector<vector<double> > U, vector<double> _b) {
    vector<double> rep(n);
    for (int i = 0; i < n; ++i) {
        double tmp = _b[i];
        for (int j = i - 1; j >= 0; --j) {
            tmp -= U[i][j] * rep[j];
        }
        rep[i] = tmp / U[i][i];
    }
    return rep;
}

void setOfEquations::getter() {
    cout << fixed << setprecision(12);
    for (auto v : ans) cout << v << '\n';
}
