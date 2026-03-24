#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>
using namespace std;

// Функция для вычисления нормы невязки (max |Ax - b|)
double norm(const vector<vector<double>>& A, const vector<double>& x, const vector<double>& b) {
    int n = A.size();
    double maxRes = 0.0;
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int j = 0; j < n; j++) {
            sum += A[i][j] * x[j];
        }
        double res = fabs(sum - b[i]);
        if (res > maxRes) maxRes = res;
    }
    return maxRes;
}

// Вывод графика в логарифмическом масштабе
void plotResiduals(const vector<double>& residuals, const string& method) {
    if (residuals.empty()) return;

    cout << "\nГрафик нормы невязки (логарифмический масштаб):\n";
    cout << "Итерация | log10(невязка)\n";
    cout << string(50, '-') << "\n";

    double minRes = *min_element(residuals.begin(), residuals.end());
    double maxRes = *max_element(residuals.begin(), residuals.end());

    // Если минимальная невязка 0, берем следующий минимум для логарифма
    if (minRes == 0) {
        for (double r : residuals) {
            if (r > 0 && r < minRes) minRes = r;
        }
    }

    for (size_t i = 0; i < residuals.size(); i++) {
        cout << setw(5) << i + 1 << "    | ";
        if (residuals[i] > 0) {
            double logVal = log10(residuals[i]);
            int barLen = max(0, min(50, static_cast<int>((logVal + 10) * 5)));
            cout << setw(8) << fixed << setprecision(2) << residuals[i];
            cout << "  ";
            for (int j = 0; j < barLen; j++) cout << "*";
            cout << " (" << fixed << setprecision(1) << logVal << ")";
        }
        else {
            cout << setw(8) << "0.000000" << "  ************** (-inf)";
        }
        cout << "\n";
    }
}

// Метод Якоби
void jacobi(const vector<vector<double>>& A, const vector<double>& b, vector<double> x0, double eps, int maxIter) {
    int n = A.size();
    vector<double> x = x0;
    vector<double> x_new(n, 0.0);
    vector<double> residuals;

    cout << "\n=== Метод Якоби ===\n";
    cout << "Начальное приближение: ";
    for (double v : x0) cout << v << " ";
    cout << "\n";

    for (int iter = 0; iter < maxIter; iter++) {
        for (int i = 0; i < n; i++) {
            double sum = 0.0;
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    sum += A[i][j] * x[j];
                }
            }
            x_new[i] = (b[i] - sum) / A[i][i];
        }

        double res = norm(A, x_new, b);
        residuals.push_back(res);

        if (res < eps) {
            cout << "\nРешение найдено за " << iter + 1 << " итераций\n";
            cout << "Решение:\n";
            for (int i = 0; i < n; i++) {
                cout << "  x" << i + 1 << " = " << fixed << setprecision(8) << x_new[i] << "\n";
            }
            cout << "Норма невязки: " << scientific << setprecision(2) << res << "\n";
            plotResiduals(residuals, "Якоби");
            return;
        }

        x = x_new;
    }

    cout << "Максимальное число итераций достигнуто\n";
    plotResiduals(residuals, "Якоби");
}

// Метод Зейделя
void seidel(const vector<vector<double>>& A, const vector<double>& b, vector<double> x0, double eps, int maxIter) {
    int n = A.size();
    vector<double> x = x0;
    vector<double> residuals;

    cout << "\n=== Метод Зейделя ===\n";
    cout << "Начальное приближение: ";
    for (double v : x0) cout << v << " ";
    cout << "\n";

    for (int iter = 0; iter < maxIter; iter++) {
        vector<double> x_old = x;

        for (int i = 0; i < n; i++) {
            double sum1 = 0.0, sum2 = 0.0;
            for (int j = 0; j < i; j++) {
                sum1 += A[i][j] * x[j];
            }
            for (int j = i + 1; j < n; j++) {
                sum2 += A[i][j] * x_old[j];
            }
            x[i] = (b[i] - sum1 - sum2) / A[i][i];
        }

        double res = norm(A, x, b);
        residuals.push_back(res);

        if (res < eps) {
            cout << "\nРешение найдено за " << iter + 1 << " итераций\n";
            cout << "Решение:\n";
            for (int i = 0; i < n; i++) {
                cout << "  x" << i + 1 << " = " << fixed << setprecision(8) << x[i] << "\n";
            }
            cout << "Норма невязки: " << scientific << setprecision(2) << res << "\n";
            plotResiduals(residuals, "Зейделя");
            return;
        }
    }

    cout << "Максимальное число итераций достигнуто\n";
    plotResiduals(residuals, "Зейделя");
}

int main() {
    setlocale(LC_ALL, "rus");
    vector<vector<double>> A = {
        {12.14, 1.32, -0.78, -2.75},
        {-0.89, 16.75, 1.88, -1.55},
        {2.65, -1.27, -15.64, -0.64},
        {2.44, 1.52, 1.93, -11.43}
    };

    vector<double> b = { 14.78, -12.14, -11.65, 4.26 };

    double eps = 1e-6;
    int maxIter = 1000;

    vector<vector<double>> startVectors = {
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {10, -10, 10, -10}
    };

    for (auto& x0 : startVectors) {
        cout << "\n\n" << string(70, '=') << "\n";
        cout << "Начальное приближение: ";
        for (double v : x0) cout << v << " ";
        cout << "\n" << string(70, '=') << "\n";

        jacobi(A, b, x0, eps, maxIter);
        seidel(A, b, x0, eps, maxIter);
    }
}
