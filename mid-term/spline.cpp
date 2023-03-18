#include "spline.h"

using namespace std;

spline* spline::run = nullptr;

void spline::getter() {
    for (int i = 0; i < n - 1; ++i) {
        cout << ai[i] << " " << bi[i] << " " << ci[i] << " " << di[i] << '\n';
    }
}
void spline::setter() {
    cout << "enter quantity: \n";
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
    cout << "enter point: \n";
    for (int i = 0; i < n; ++i) {
        cin >> xi[i] >> ai[i];
    }
    l[0] = 1;
    u[0] = 0;
    z[0] = 0;
}

void spline::solveSpline() {
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
}