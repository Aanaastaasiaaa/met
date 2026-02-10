#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

double s(double x, double eps, int& n)
{
    double sum = 0.0;
    int k = 1;
    n = 0;

    while (true)
    {
        double term = 1.0 / k - 1.0 / (k + x);
        sum += term;
        n++;

        if (fabs(term) < eps)
            break;

        k++;
    }

    return sum;
}

int main()
{
    setlocale(LC_ALL, "rus");
    cout << fixed << setprecision(10);

    double x1 = 0.5;
    double x2 = 0.999999999;
    double time_per_term = 0.0005;

    int n1;
    double s1 = s(x1, 3e-8, n1);
    cout << "x = " << x1 << " s(x) = " << s1 << endl;
    cout << "Членов ряда: " << n1 << endl;
    cout << "Время: " << n1 * time_per_term << " секунд" << endl;

    int n2;
    double s2 = s(x2, 3e-8, n2);
    cout << "x = " << setprecision(9) << x2 <<  " s(x) = " << s2 << endl;
    cout << "Членов ряда: " << n2 << endl;
    cout << "Время: " << n2 * time_per_term << " секунд" << endl;

    return 0;
}