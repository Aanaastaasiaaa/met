#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

double s_direct(double x, double eps, int& terms1, int& terms2, double& sumtime) {
    double sum1 = 0.0, sum2 = 0.0;
    terms1 = 0, terms2 = 0;
    const double time = 0.0005; 
    sumtime = 0.0;

    for (int k = 1; ; k++) {
        double t = 1.0 / (k * (k + x));
        sum1 += t;
        terms1++;
        sumtime += time;
        if (fabs(t) < eps) break;
    }

    for (long long k = 1; ; k++) {
        double t = 1.0 / (k * (k - x));
        sum2 += t;
        terms2++;
        sumtime += time;
        if (fabs(t) < eps) break;
    }

    return sum1 - sum2;
}

double s_fast(double x, double eps, int& terms, double& sumtime) {
    double sum = 0.0;
    terms = 0;
    const double time = 0.0005;
    sumtime = 0.0;

    for (int k = 1; ; k++) {
        double t = (2.0 * x) / (k * (k * k - x * x));
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

    int terms1, terms2;
    double time;
    double s1 = s_direct(x1, eps, terms1, terms2, time);
    cout << "x = " << x1 << endl << " s(x) = " << s1 << " Всего членов: " << terms1 + terms2 << endl;
    cout << "Время: " << time << " секунд" << endl;
    int terms1_2, terms2_2;
    double time_2;
    double s2 = s_direct(x2, eps, terms1_2, terms2_2, time_2);
    cout << "x = " << setprecision(9) << x2 << " s(x) = " << s2 << " Всего членов: " << terms1_2 + terms2_2 << endl;
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
    cout << "Для x = 0.5.Разность: " << fabs(s1 - s1_fast) << endl;

    cout << "Для x = 0.999999999. Разность: " << fabs(s2 - s2_fast) << endl;

    return 0;
}
