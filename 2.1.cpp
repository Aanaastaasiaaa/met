#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

void solve_quadratic(double a, double b, double c) {
    cout << "Уравнение: " << a << "x^2 + " << b << "x + " << c << " = 0\n";
    if (abs(a) < 1e-12) 
    {
        cout << "не квадратное уравнение"<<endl;
        return;
    }

    double max_coeff = max(abs(a), max(abs(b), abs(c)));
    if (max_coeff > 1e100) {
        double scale = 1e-100;
        a *= scale; 
        b *= scale; 
        c *= scale;
    }

    double d = b * b - 4 * a * c;

    if (d < 0) {
        double real = -b / (2 * a);
        double imag = sqrt(-d) / (2 * a);
        cout << real << " + " << imag << "i\n";
        cout << real << " - " << imag << "i\n";
        return;
    }

    double x1, x2;
    double sqrt_d = sqrt(d);

    if (b >= 0) {
        x1 = (-b - sqrt_d) / (2 * a);  
    }
    else {
        x1 = (-b + sqrt_d) / (2 * a); 
    }
    x2 = c / (a * x1);
    cout << "Корни:\n";
    cout << "x1 = " << x1 << endl;
    cout << "x2 = " << x2 << endl<<endl;
}

int main() {
    setlocale(LC_ALL, "rus");
    solve_quadratic(6, 5, -4);
    solve_quadratic(6e30, 5e30, -4e30);
    solve_quadratic(0, 2, 3);

    return 0;
}