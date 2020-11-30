/*
 * C. Квадратный корень и квадратный квадрат
ограничение по времени на тест: 2 секунды
ограничение по памяти на тест: 256 мегабайт
ввод: стандартный ввод
вывод: стандартный вывод

Найдите такое число x, что x^2 + sqrt(x) = C, с точностью не менее 6 знаков после точки.

Входные данные
В единственной строке содержится вещественное число 1.0 ≤ C ≤ 10^10.

Выходные данные
Выведите одно число — искомый x.

Примеры
входные данные
2.0000000000
выходные данные
1.0

входные данные
18.0000000000
выходные данные
4.0
 */

#include <iostream>
#include <math.h>

using std::cin;
using std::cout;

const double EPS = 0.000001;
const int MAX_NUMBER_OF_ITERATIONS = 100;


double ApplyFunction(double value_x) {
    return pow(value_x, 2) + sqrt(value_x);
}

double BinSearch(double y, double left, double right) {
    for (int i = 0; i < MAX_NUMBER_OF_ITERATIONS; i++) {

        double middle = (left + right) / 2;
        double f_middle = ApplyFunction(middle);

        if (f_middle < y) {
            left = middle;
        } else {
            right = middle;
        }

        if (right - left <= EPS) {
            return (left + right) / 2;
        }
    }

    return right;
}

int main() {

    double c;
    cin >> c;

    double left_value = 50;
    double right_value = 1000;

    double f_left = ApplyFunction(left_value);
    double f_right = ApplyFunction(right_value);

    if (abs(f_left - c) < EPS) {
        return f_left;
    }
    if (abs(f_right - c) < EPS) {
        return f_right;
    }

    while (f_left > c) {
        left_value /= 2;
        f_left = ApplyFunction(left_value);
    }

    while (f_right < c) {
        right_value *= 2;
        f_right = ApplyFunction(right_value);
    }

    double answer = BinSearch(c, left_value, right_value);
    cout.precision(6);
    cout << std::fixed << answer;

    return 0;
}