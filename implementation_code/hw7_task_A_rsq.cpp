/* Префиксные суммы
 * A. Сумма простая
ограничение по времени на тест: 1 секунда
ограничение по памяти на тест: 512 мегабайт
ввод: стандартный ввод
вывод: стандартный вывод

Вам нужно научиться отвечать на запрос «сумма чисел на отрезке».

Массив не меняется. Запросов много. Отвечать на каждый запрос следует за O(1).

Входные данные
Размер массива — n и числа x, y, a_0, порождающие массив a: a_i = (x * a_{i - 1} + y) mod 2^16

Далее следует количество запросов m и числа z, t, b_0, порождающие массив b: b_i = (z * b_{i - 1} + t) mod 2^30

Массив c строится следующим образом: c_i = b_i mod n

Запросы: i-й из них — найти сумму на отрезке от min(c_{2i}, c_{2i + 1}) до max(c_{2i}, c_{2i + 1}) в массиве a.

Ограничения: 1 ≤ n ≤ 10^7, 0 ≤ m ≤ 10^7. Все числа целые от 0 до 2^16. t может быть равно -1.

Выходные данные
Выведите сумму всех сумм.

Пример
входные данные
3 1 2 3
3 1 -1 4

выходные данные
23

Примечание
a = {3, 5, 7}, b = {4, 3, 2, 1, 0, 2^{30} - 1}, c = {1, 0, 2, 1, 0, 0},

запросы = {[0, 1], [1, 2], [0, 0]}, суммы = {8, 12, 3}.
 */

#include <iostream>
#include <vector>
#include<cmath>

using std::cin;
using std::cout;
using std::vector;

static long long int two_in_power_16 = std::pow(2, 16);
static long long int two_in_power_30 = std::pow(2, 30);

int calculate_a_i(int x, int y, long long int prev_a_i) {
    return (x * prev_a_i + y) % two_in_power_16;
}

long long int calculate_b_i(long long int prev_b_i, int z, int t) {
    long long int inner_calculation = (z * prev_b_i + t);

    if (inner_calculation >= 0) {
        return inner_calculation % two_in_power_30;
    } else {
        return (inner_calculation + two_in_power_30) % two_in_power_30;
    }
}

int calculate_c_i(long long int b_i, int n) {
    return b_i % n;
}


vector<long long int> build_a_i_sum_array(int n, int x, int y, long long int cur_a_i) {

    vector<long long int> a_i_sum_array;
    a_i_sum_array.push_back(cur_a_i);

    for (int i = 1; i < n; i++) {

        cur_a_i = calculate_a_i(x, y, cur_a_i);
        a_i_sum_array.push_back(a_i_sum_array.back() + cur_a_i);
    }

    return a_i_sum_array;
}

long long int sum_from_left_to_right(vector<long long int> &a_i_array_sums, int left, int right) {

    if (left < 1) {
        return a_i_array_sums.at(right);

    } else {
        return a_i_array_sums.at(right) - a_i_array_sums.at(left - 1);
    }
}


long long int solve_rsq() {

    int n, x, y, m, z, t;
    long long int a_0, cur_b_i;
    cin >> n >> x >> y >> a_0 >> m >> z >> t >> cur_b_i;

    long long int sum_of_sums = 0;

    if (m == 0) {
        return sum_of_sums;
    }

    vector<long long int> a_i_array_sums = build_a_i_sum_array(n, x, y, a_0);

    int prev_c_i = calculate_c_i(cur_b_i, n);
    int cur_c_i;

    int left_bound, right_bound;

    for (int i = 1; i < m * 2; i++) {
        cur_b_i = calculate_b_i(cur_b_i, z, t);
        cur_c_i = calculate_c_i(cur_b_i, n);

        if (i % 2 == 1) {

            if (prev_c_i <= cur_c_i) {
                left_bound = prev_c_i;
                right_bound = cur_c_i;

            } else {
                left_bound = cur_c_i;
                right_bound = prev_c_i;
            }

            sum_of_sums += sum_from_left_to_right(a_i_array_sums, left_bound, right_bound);
        }

        prev_c_i = cur_c_i;
    }

    return sum_of_sums;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    long long int sum_of_sums = solve_rsq();
    cout << sum_of_sums;

    return 0;
}



