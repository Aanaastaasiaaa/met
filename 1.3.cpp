#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

const double pi = acos(-1.0);

double met1(double eps, int& n)
{
    double sum = 0.0;
    n = 1;

    while (true)
    {
        double term = 1.0 / (n * n + 1);
        sum += term;

        if (term < eps)
            break;

        n++;
    }

    return sum;
}

double met2(double eps, int& n)
{
    double sum = 0.0;
    n = 1;

    while (true)
    {
        double term = 1.0 / (n * n * (n * n + 1));
        sum += term;

        if (term < eps)
            break;

        n++;
    }

    return (pi * pi) / 6.0 - sum;
}

int main()
{
    setlocale(LC_ALL, "rus");
    cout << fixed << setprecision(12);

    double eps = 1e-10;

    int n1, n2;
    double s1 = met1(eps, n1);
    double s2 = met2(eps, n2);

    double exact = (pi * cosh(pi) / sinh(pi) - 1) / 2;

    cout << "исходный метод:" << endl;
    cout << "сумма = " << s1 <<" членов = " << n1 << endl;

    cout << "преобразованный метод:" << endl;
    cout << "сумма = " << s2 <<" членов = " << n2 << endl;

    return 0;
}