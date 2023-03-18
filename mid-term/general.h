#ifndef GENERAL_H
#define GENERAL_H
#include <iostream>
#include <vector>
#include "general.h"
using namespace std;

extern const int inf = 0x3f3f3f3f;

extern vector<vector<double> > transposeMatrix(vector<vector<double> > m) {
  vector<vector<double> > mT (m[0].size(), vector<double> (m.size(), 0));

  for (int i = 0; i < m.size(); ++i) {
    for (int j = 0; j < m[0].size(); ++j) {
      mT[j][i] = m[i][j];
    }
  }
  return mT;
}

extern double sumL(vector<vector<double> > L, int i, int j) {
  double rep = 0;
  for (int k = 0; k < j; ++k) {
    rep += L[i][k] * L[j][k];
  }
  return rep;
}

extern double determinantOfMatrix (int n, vector<vector<double> > matrix) {
  double determinant = 0;

  if (n == 1) {
    return matrix[0][0];
  }
  if (n == 2) {
    return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
  }
  int sign = 1;
  vector <double> temp;
  for (int k = 0; k < n; ++k) {
    vector <vector <double> > subMatrix;
    for (int i = 1; i < n; ++i) {
      temp.resize(0);
      for (int j = 0; j < n; ++j) {
        if (k != j) temp.push_back(matrix[i][j]);
      }
      subMatrix.push_back(temp);
    }
    determinant += sign * matrix[0][k] * determinantOfMatrix(n - 1, subMatrix);
    sign = - sign;
  }

  return determinant;
}

extern vector <vector <double> > subAi (vector <vector <double> > matrix, vector <double> b, int i) {
  vector <vector <double> > matrixAi (matrix);
  for (int j = 0; j < matrix.size(); ++j) {
    matrixAi[j][i] = b[j];
  }
  return matrixAi;
}

extern vector <vector <double> > multiMatrix (vector <vector <double> > matrixA, vector <vector <double> > matrixB) {
  vector <vector <double> > matrixRes (matrixA.size(), vector <double> (matrixB[0].size()));
  for (int i = 0; i < matrixRes.size(); ++i) {
    for (int j = 0; j < matrixRes[0].size(); ++j) {
      for (int k = 0; k < matrixA[0].size(); ++k) {
        matrixRes[i][j] += matrixA[i][k] * matrixB[k][j];
      }
    }
  }
  return matrixRes;
}

extern void out(vector<vector<double> > matrix) {
  for (auto u : matrix) {
    for (auto v : u) {
      cout << v << " ";
    }
    cout << endl;
  }
}



#endif // GENERAL_H
