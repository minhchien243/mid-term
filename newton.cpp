#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

class cubic
{
public:
    void getter();
    void setter();
    void spline();
private:
    int n;
    vector<double> xi;
    vector<double> ai, bi, ci, di;
    vector<double> hi;
    vector<double> l, u, z, a;

};
void cubic::getter() {

}
void cubic::setter() {
    cin >> n;
    xi.resize(n + 1);
    ai.resize(n + 1);
    bi.resize(n + 1);
    ci.resize(n + 1);
    di.resize(n + 1);
    hi.resize(n + 1);
    l.resize(n + 1);
    a.resize(n + 1);
    u.resize(n + 1);
    z.resize(n + 1);
    for (int i = 0; i < n; ++i) {
      cin >> xi[i] >> ai[i];
    }
    l[0] = 1;
    u[0] = 0;
    z[0] = 0;
}
/**
4
0 1
1 2.718281828
2 7.389056099
3 20.08553692
*/
void cubic::spline() {
  for (int i = 0; i < n - 1; ++i) {
      hi[i] = xi[i + 1] - xi[i];
  }
  for (int i = 1; i < n - 1; ++i) {
      a[i] = 3 / hi[i] * (ai[i + 1] - ai[i]) - 3 / hi[i - 1] * (ai[i] - ai[i - 1]);
  }
  for (int i = 1; i < n - 1; ++i) {
    l[i] = 2 * (xi[i + 1] - xi[i - 1]) - hi[i - 1] * u[i - 1];
    u[i] = hi[i] / l[i];
    z[i] = (a[i] - hi[i - 1] * z[i - 1]) / l[i];
  }
  l[n - 1] = 1, z[n - 1] = 0, ci[n - 1] = 0;
  for (int i = n - 2; i >= 0; --i) {
    ci[i] = z[i] - u[i] * ci[i + 1];
    bi[i] = (ai[i + 1] - ai[i]) / hi[i] - hi[i] * (ci[i + 1] + 2 * ci[i]) / 3;
    di[i] = (ci[i + 1] - ci[i]) / (3 * hi[i]);
  }
  for (int i = 0; i < n - 1; ++i) {
    cout << ai[i] << " " << bi[i] << " " << ci[i] << " " << di[i] << '\n';
  }
}

int main()
{

    cubic c1;
    c1.setter();
    c1.spline();
    return 0;
}
