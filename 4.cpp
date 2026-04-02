#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <sstream>
using namespace std;

const int N = 4;
vector<vector<double>> A = {
    {12.14,  1.32, -0.78, -2.75},
    {-0.89, 16.75,  1.88, -1.55},
    {2.65,  -1.27, -15.64, -0.64},
    {2.44,   1.52,  1.93, -11.43}
};
vector<double> b = { 14.78, -12.14, -11.65, 4.26 };

double Norm(const vector<vector<double>>& A, const vector<double>& b, const vector<double>& x) {
    double sum = 0;
    for (int i = 0; i < N; i++) {
        double Ax = 0;
        for (int j = 0; j < N; j++) {
            Ax += A[i][j] * x[j];
        }
        double diff = b[i] - Ax;
        sum += diff * diff;
    }
    return sqrt(sum);
}

vector<double> jacobi(const vector<vector<double>>& A, const vector<double>& b,
    const vector<double>& x0, double tol, int maxIter,
    vector<double>& solution, vector<double>& residuals) {

    vector<double> x_old = x0;
    vector<double> x_new(N);
    residuals.clear();

    for (int iter = 0; iter < maxIter; iter++) {

        for (int i = 0; i < N; i++) {
            double sum = 0;
            for (int j = 0; j < N; j++) {
                if (j != i) {
                    sum += A[i][j] * x_old[j];
                }
            }
            x_new[i] = (b[i] - sum) / A[i][i];
        }

        double res = Norm(A, b, x_new);
        residuals.push_back(res);

        if (res < tol) {
            solution = x_new;
            return residuals;
        }
        x_old = x_new;
    }

    solution = x_old;
    return residuals;
}

vector<double> seidel(const vector<vector<double>>& A, const vector<double>& b,
    const vector<double>& x0, double tol, int maxIter,
    vector<double>& solution, vector<double>& residuals) {

    vector<double> x = x0;
    residuals.clear();

    for (int iter = 0; iter < maxIter; iter++) {

        for (int i = 0; i < N; i++) {
            double sum = 0;
            for (int j = 0; j < N; j++) {
                if (j != i) {
                    sum += A[i][j] * x[j];
                }
            }
            x[i] = (b[i] - sum) / A[i][i];
        }

        double res = Norm(A, b, x);
        residuals.push_back(res);

        if (res < tol) {
            solution = x;
            return residuals;
        }
    }

    solution = x;
    return residuals;
}

void saveToCSV(const string& filename, const vector<double>& residuals) {
    ofstream file(filename.c_str());
    file << "Итерация,Невязка" << endl;
    for (size_t i = 0; i < residuals.size(); i++) {
        file << i + 1 << ", " << scientific << setprecision(15) << residuals[i] << endl;
    }
    file.close();
}

void printSolution(const vector<double>& x) {
    for (int i = 0; i < N; i++) {
        cout << "  x" << i + 1 << " = " << fixed << setprecision(8) << x[i] << endl;
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    cout << fixed;

    cout << "\nИсходная система:" << endl;
    for (int i = 0; i < N; i++) {
        cout << "  ";
        for (int j = 0; j < N; j++) {
            if (A[i][j] >= 0 && j > 0) cout << "+";
            cout << A[i][j] << "·x" << j + 1 << " ";
        }
        cout << "= " << b[i] << endl;
    }

    double tol = 1e-6;
    int maxIter = 200;

    vector<vector<double>> starts = {
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {10, -10, 10, -10},
        {100, 100, 100, 100}
    };

    for (size_t k = 0; k < starts.size(); k++) {
        cout << "Начальное приближение " << k + 1 << ": ";
        for (int i = 0; i < N; i++) {
            cout << starts[k][i];
            if (i < N - 1) cout << ", ";
        }
        cout << endl;

        vector<double> solution;
        vector<double> residuals;

        cout << "\n МЕТОД ЯКОБИ" << endl;
        jacobi(A, b, starts[k], tol, maxIter, solution, residuals);
        cout << "  Решение:" << endl;
        printSolution(solution);
        cout << "  Число итераций: " << residuals.size() << endl;
        cout << "  Финальная невязка: " << residuals.back() << endl;

        stringstream ss;
        ss << "C:\\Users\\User\\OneDrive\\Desktop\\4\\jacobi_" << k + 1 << ".docx";
        saveToCSV(ss.str(), residuals);

        cout << "\nМЕТОД ЗЕЙДЕЛЯ" << endl;
        seidel(A, b, starts[k], tol, maxIter, solution, residuals);
        cout << "  Решение:" << endl;
        printSolution(solution);
        cout << "  Число итераций: " << residuals.size() << endl;
        cout << "  Финальная невязка: " << residuals.back() << endl;

        stringstream ss2;
        ss2 << "C:\\Users\\User\\OneDrive\\Desktop\\4\\seidel_" << k + 1 << ".docx";
        saveToCSV(ss2.str(), residuals);
    }
}
