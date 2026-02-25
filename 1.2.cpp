#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

double s(double x, double eps, int& terms, double& sumtime) {
    double sum=0.0;
    terms = 1;
    const double time = 0.0005;
    sumtime = 0.0;

    for (int k = 1; ; k++) {
        double sum1 = 1.0 / sqrt(k * k * k + x);
        double sum2 = 1.0 / sqrt(k * k * k - x);
        sumtime += time;
        double s = sum1 - sum2;
        if (fabs(s) < eps) break;
        terms++;
        sumtime += time;
        sum += s;
    }

    return sum;
}

double s_fast(double x, double eps, int& terms, double& sumtime) {
    double sum = 0.0;
    terms = 1;
    const double time = 0.0005;
    sumtime = 0.0;

    for (int k = 1; ; k++) {
        double a = sqrt(k * k * k + x);
        double b = sqrt(k * k * k - x);
        double t = (2.0 * x) / (a*b*(a+b));
        sum += t;
        terms++;
        sumtime += time;
        if (fabs(t) < eps) break;
    }

    return sum;
}

int main() {
    setlocale(LC_ALL, "rus");
    cout << fixed << setprecision(12);

    double x1 = 0.5;
    double x2 = 0.999999999;
    double eps = 3e-8;

    int terms1;
    double time;
    double s1 = s(x1, eps, terms1, time);
    cout << "x = " << x1 << endl << " s(x) = " << s1 << " Всего членов: " << terms1  << endl;
    cout << "Время: " << time << " секунд" << endl;
    int terms1_2;
    double time_2;
    double s2 = s(x2, eps, terms1_2, time_2);
    cout << "x = " << setprecision(9) << x2 << " s(x) = " << s2 << " Всего членов: " << terms1_2 << endl;
    cout << "Время: " << time_2 << " секунд" << endl;

    cout << " Ускоренное вычисление" << endl;
    int terms_fast;
    double time_fast;
    double s1_fast = s_fast(x1, eps, terms_fast, time_fast);
    cout << "x = " << x1 << " s(x) = " << s1_fast << " Членов ряда: " << terms_fast << endl;
    cout << "Время: " << time_fast << " секунд" << endl;
    int terms_fast2;
    double time_fast2;
    double s2_fast = s_fast(x2, eps, terms_fast2, time_fast2);
    cout << "x = " << setprecision(9) << x2 << " s(x) = " << s2_fast << " Членов ряда: " << terms_fast2 << endl;
    cout << "Время: " << time_fast2 << " секунд" << endl;

    cout << "Сравнение результатов" << endl;
    cout << "Для x = 0.5. Разность: " << fabs(s1 - s1_fast) << endl;

    cout << "Для x = 0.999999999. Разность: " << fabs(s2 - s2_fast) << endl;

    return 0;
}
