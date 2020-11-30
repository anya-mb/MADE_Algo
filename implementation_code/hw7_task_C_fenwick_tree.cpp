/*
 * C. RSQ
ограничение по времени на тест: 2 секунды
ограничение по памяти на тест: 256 мегабайт
ввод: стандартный ввод
вывод: стандартный вывод

Входные данные
В первой строке находится число n — размер массива. (1 ≤ n ≤ 500000) Во второй строке находится n чисел a_i — элементы массива. Далее содержится описание операций, их количество не превышает 1000000. В каждой строке находится одна из следующих операций:

set i x — установить a[i] в x.
sum i j — вывести значение суммы элементов в массиве на отрезке с i по j, гарантируется, что (1 ≤ i ≤ j ≤ n).
Все числа во входном файле и результаты выполнения всех операций не превышают по модулю 10^18.

Выходные данные
Выведите последовательно результат выполнения всех операций sum. Следуйте формату выходного файла из примера.

Пример
входные данные
5
1 2 3 4 5
sum 2 5
sum 1 5
sum 1 4
sum 2 4
set 1 10
set 2 3
set 5 2
sum 2 5
sum 1 5
sum 1 4
sum 2 4

выходные данные
14
15
10
9
12
22
20
10
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <assert.h>

using std::cin;
using std::cout;
using std::vector;
using std::string;


class FenwickTree {
public:

    long long int sum(int left, int right) {
        if (left <= 1) {
            return get(right);
        } else {
            long long int sum_to_right = get(right);
            long long int sum_to_left = get(left - 1);
            return sum_to_right - sum_to_left;
        }
    }

    void set(int i, long long int x) {
        i--;
        long long int difference = x - a_array.at(i);
        a_array.at(i) = x;
        add(i, difference);
    }

    FenwickTree(vector <long long int> &a_i_array) {
        size = a_i_array.size();

        for (int i = 0; i < size; i++) {
            T_array.push_back(0);
        }

        for (int i = 0; i < size; i++) {
            long long int a_i = a_i_array.at(i);
            add(i, a_i);
        }

        a_array = a_i_array;
    }

    virtual ~FenwickTree() {
    }


private:

    vector <long long int> T_array;
    vector <long long int> a_array;
    int size;

    long long int get(int i) {
        i--;
        long long int result = 0;

        for (int j = i; j >= 0; j = fenwick_function(j) - 1) {
            result += T_array.at(j);
        }

        return result;
    }

    void add(int i, long long int x) {
        int j = i;
        while (j < size) {
            T_array.at(j) += x;
            j = j | (j + 1);
        }
    }

    long long int fenwick_function(long long int i) {
        return i & (i + 1);
    }
};


void t0() {
    vector <long long int> a_i_array = {1, 2, 3, 4, 5};
    FenwickTree fenwick_tree(a_i_array);

    long long int result1 = fenwick_tree.sum(2, 5);
    assert(result1 == 14);

    long long int result2 = fenwick_tree.sum(1, 5);
    assert(result2 == 15);

    long long int result3 = fenwick_tree.sum(1, 4);
    assert(result3 == 10);

    long long int result4 = fenwick_tree.sum(2, 4);
    assert(result4 == 9);

    fenwick_tree.set(1, 10);
    fenwick_tree.set(2, 3);
    fenwick_tree.set(5, 2);

    long long int result5 = fenwick_tree.sum(2, 5);
    assert(result5 == 12);

    long long int result6 = fenwick_tree.sum(1, 5);
    assert(result6 == 22);

    long long int result7 = fenwick_tree.sum(1, 4);
    assert(result7 == 20);

    long long int result8 = fenwick_tree.sum(2, 4);
    assert(result8 == 10);

}


void test() {
    t0();
}

void input() {

    int n;
    cin >> n;

    long long int a_i;
    vector <long long int> a_i_array;

    for (int i = 0; i < n; i++) {
        cin >> a_i;
        a_i_array.push_back(a_i);
    }

    string operation;
    FenwickTree fenwick_tree(a_i_array);

    while (cin >> operation) {
        if (operation == string("sum")) {

            int i, j;
            cin >> i >> j;

            long long int sum_value = fenwick_tree.sum(i, j);
            cout << sum_value << std::endl;

        } else if (operation == string("set")) {

            int i;
            long long int x;

            cin >> i >> x;

            fenwick_tree.set(i, x);

        } else {
            throw;
        }
    }

}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    input();

//    test();

    return 0;
}