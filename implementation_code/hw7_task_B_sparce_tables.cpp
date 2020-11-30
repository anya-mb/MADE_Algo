/*
 * B. Разреженные таблицы
ограничение по времени на тест: 2 секунды
ограничение по памяти на тест: 256 мегабайт
ввод: стандартный ввод
вывод: стандартный вывод

Дан массив из 𝑛 чисел. Требуется написать программу, которая будет отвечать на запросы следующего вида: найти минимум на отрезке между 𝑢 и 𝑣 включительно.

Входные данные
В первой строке зданы три натуральных числа 𝑛, 𝑚 (1 ⩽ 𝑛 ⩽ 10^5, 1 ⩽ 𝑚 ⩽ 10^7) и 𝑎_1 (0 ⩽ 𝑎_1 < 16714589) — количество элементов в массиве, количество запросов и первый элемент массива соответственно. Вторая строка содержит два натуральных числа 𝑢_1 и 𝑣_1 (1 ⩽ 𝑢_1, 𝑣_1 ⩽ 𝑛) — первый запрос.

Для того, размер ввода был небольшой, массив и запросы генерируются.

Элементы 𝑎2,𝑎3,…,𝑎𝑛 задаются следующей формулой:
𝑎_{𝑖 + 1} = (23 ⋅ 𝑎_𝑖 + 21563) mod 16714589.

Например, при 𝑛 = 10, 𝑎_1 = 12345 получается следующий массив: 𝑎 = (12345, 305498, 7048017, 11694653, 1565158, 2591019, 9471233, 570265, 13137658, 1325095).

Запросы генерируются следующим образом:

𝑢_{𝑖 + 1} = ((17 ⋅ 𝑢_𝑖 + 751 + 𝑟_𝑖 + 2𝑖) mod 𝑛) + 1, 𝑣_{𝑖 + 1} = ((13 ⋅ 𝑣_𝑖 + 593 + 𝑟_𝑖 + 5𝑖) mod 𝑛) + 1,
где 𝑟_𝑖 — ответ на запрос номер 𝑖.
Обратите внимание, что 𝑢_𝑖 может быть больше, чем 𝑣_𝑖.

Выходные данные
В выходной файл выведите 𝑢_𝑚, 𝑣_𝑚 и 𝑟_𝑚 (последний запрос и ответ на него).

Примеры
входные данные
10 8 12345
3 9

выходные данные
5 3 1565158
 *
 */


#include <iostream>
#include <vector>
#include <cmath>

using std::cin;
using std::cout;
using std::vector;

static int BIG_NUMBER = 16714589 + 1;

int calculate_a_i(long long int prev_a_i) {
    return (23 * prev_a_i + 21563) % 16714589;
}

int calculate_u_i(long long int prev_u_i, long long int prev_r_i, int i, int n) {
    return (17 * prev_u_i + 751 + prev_r_i + 2 * i) % n + 1;
}

int calculate_v_i(long long int prev_v_i, long long int prev_r_i, int i, int n) {
    return (13 * prev_v_i + 593 + prev_r_i + 5 * i) % n + 1;
}

vector <int> generate_max_power_array(int n) {
    vector <int> max_power_array;

    int power = 0;
    int two_in_the_power = std::pow(2, power);

    for (int i = 1; i < n + 1; i++) {

        if (i >= two_in_the_power) {
            two_in_the_power *= 2;
            power++;
        }

        max_power_array.push_back(power - 1);
    }
    return max_power_array;
}

vector<long long int> build_a_i_array(int n, long long int cur_a_i) {
    vector<long long int> a_i_array;
    a_i_array.push_back(cur_a_i);

    for (int i = 1; i < n; i++) {
        cur_a_i = calculate_a_i(cur_a_i);
        a_i_array.push_back(cur_a_i);
    }

    return a_i_array;
}


void build_a_i_array_sparce_table(vector<long long int> &a_i_array, vector <int> &max_power_array) {

    int n = a_i_array.size();
    int max_k = max_power_array.back();
    int two_power_k_prev = 1;

    for (int row_idx = 1; row_idx < max_k + 1; row_idx++) {

        for (int l = 0; l < n; l++) {
            int k_prev_l_idx = (row_idx - 1) * n + l;
            int k_prev_next_l_idx = k_prev_l_idx + two_power_k_prev;

            if (l + two_power_k_prev < n) {

                long long int min_k_prev_l = a_i_array.at(k_prev_l_idx);
                long long int min_k_prev_next_l = a_i_array.at(k_prev_next_l_idx);

                if (min_k_prev_l <= min_k_prev_next_l) {
                    a_i_array.push_back(min_k_prev_l);

                } else {
                    a_i_array.push_back(min_k_prev_next_l);
                }

            } else {
                a_i_array.push_back(BIG_NUMBER);
            }
        }

        two_power_k_prev *= 2;
    }
}

long long int min_from_left_to_right(vector<long long int> &a_i_array_dp,
                                     int left, int right,
                                     vector <int> &max_power_array, int n) {

    int k = max_power_array.at(right - left);
    int calculated_right = right - std::pow(2, k) + 1;

    long long int min_l_k = a_i_array_dp.at(k * n + left);
    long long int min_calc_r_k = a_i_array_dp.at(k * n + calculated_right);

    if (min_l_k <= min_calc_r_k) {
        return min_l_k;
    } else {
        return min_calc_r_k;
    }
}

long long int min_from_left_to_right_wrapper(vector<long long int> &a_i_array_dp,
                                     int left, int right,
                                     vector <int> &max_power_array, int n) {

    left--;
    right--;

    if (left <= right) {
        return min_from_left_to_right(a_i_array_dp, left, right, max_power_array, n);
    } else {
        return min_from_left_to_right(a_i_array_dp, right, left, max_power_array, n);
    }
}


vector <int> solve_rmq(int n, int m, long long int a_i, int u_i, int v_i) {

    int r_i;

    vector <int> max_power_array = generate_max_power_array(n);

    vector<long long int> a_i_array = build_a_i_array(n, a_i);
    build_a_i_array_sparce_table(a_i_array, max_power_array);

    r_i = min_from_left_to_right_wrapper(a_i_array, u_i, v_i, max_power_array, n);

    vector <int> result_u_v_r_array;

    if (m == 1) {
        result_u_v_r_array.insert(result_u_v_r_array.end(),{u_i, v_i, r_i});
        return result_u_v_r_array;
    }

    for (int i = 1; i < m; i++) {

        u_i = calculate_u_i(u_i, r_i, i, n);
        v_i = calculate_v_i(v_i, r_i, i, n);
        r_i = min_from_left_to_right_wrapper(a_i_array, u_i, v_i, max_power_array, n);
    }

    result_u_v_r_array.insert(result_u_v_r_array.end(),{u_i, v_i, r_i});
    return result_u_v_r_array;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m, u_i, v_i;
    long long int a_i;
    cin >> n >> m >> a_i >> u_i >> v_i;

    vector <int> result = solve_rmq(n, m, a_i, u_i, v_i);

    for (auto elem : result) {
        cout << elem << " ";
    }

    return 0;
}
