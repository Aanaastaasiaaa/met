#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

const double pi = acos(-1.0);
const double pi2 = pi * pi;
const double pi4 = pi2 * pi2;

double method1(double eps, int& terms) {
    double sum = 0.0;
    terms = 0;

    for (int n = 1; ; n++) {
        double term = 1.0 / (n * n + 1.0);
        double prev = sum;
        sum += term;
        terms++;

        if (sum == prev) {
            break;
        }
    }

    return sum;
}

double method2(double eps, int& terms) {
    double sum = pow(pi, 2) / 6.0 - pow(pi, 4) / 90.0;
    terms = 0;

    for (int n = 1; ; n++) {
        double term = 1.0 / (n * n * n * n * n * n * (n * n + 1.0));
        double prev = sum;
        sum += term;
        terms++;

        if (sum == prev || term < eps) {
            break;
        }
    }

    return sum;
}

int main() {
    setlocale(LC_ALL, "rus");
    cout << fixed << setprecision(12);

    double eps = 1e-10;
    int n1, n2, n3;

    cout << "Исходный ряд:" << endl;
    double s1 = method1(eps, n1);
    cout << "Сумма = " << s1 << " членов = " << n1 << endl;

    cout << "Преобразованный ряд:" << endl;
    double s2 = method2(eps, n2);
    cout << "Сумма = " << s2 << " операций = " << n2 + 2  << endl;

    return 0;
}
