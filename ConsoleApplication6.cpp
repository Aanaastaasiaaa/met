#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const double pi = acos(-1.0);

double fuc(int x)
{
    if (x == 1 || x == 0) return 1;
    return x * fuc(x - 1);
}

double fun(double x, int maxn = 1000)
{
    double sc = 2.0 / sqrt(pi);
    double sum = 0;
    int n = 0;
    double prev = -1;

    while (n < maxn)
    {
        double a1 = pow(-1, n);
        double a2 = pow(x, 2 * n + 1);
        double a3 = fuc(n);
        double a4 = 2 * n + 1;
        double term = a1 * a2 / (a3 * a4);

        sum += term;

        if (sum == prev) {
            break;
        }

        prev = sum;
        n++;
    }

    return sum * sc;
}

int main()
{
    double x[] = { 0.5, 1.0, 5.0, 10.0 };
    for (int i = 0; i < 4; i++) {
        cout << "x = " << x[i] ;
        cout << scientific << setprecision(8);
        cout << "  erf(x) = " << erf(x[i]) << endl;
    }

    return 0;
}
