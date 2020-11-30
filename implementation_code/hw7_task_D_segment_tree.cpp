/* Segment tree for finding min
 *
 * D. RMQ2
ограничение по времени на тест: 2 секунды
ограничение по памяти на тест: 256 мегабайт
ввод: стандартный ввод
вывод: стандартный вывод

Входные данные
В первой строке находится число n — размер массива. (1 ≤ n ≤ 10^5) Во второй строке находится n чисел a_i — элементы массива. Далее содержится описание операций, их количество не превышает 2·10^5. В каждой строке находится одна из следующих операций:

set i j x — установить все a[k], i ≤ k ≤ j в x.
add i j x — увеличить все a[k], i ≤ k ≤ j на x.
min i j — вывести значение минимального элемента в массиве на отрезке с i по j, гарантируется, что (1 ≤ i ≤ j ≤ n).

Все числа во входном файле и результаты выполнения всех операций не превышают по модулю 10^18.

Выходные данные
Выведите последовательно результат выполнения всех операций min. Следуйте формату выходного файла из примера.

Пример
входные данные
5
1 2 3 4 5
min 2 5
min 1 5
min 1 4
min 2 4
set 1 3 10
add 2 4 4
min 2 5
min 1 5
min 1 4
min 2 4

выходные данные
2
1
1
2
5
5
8
8
 *
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <assert.h>

using std::cin;
using std::cout;
using std::vector;
using std::string;


class SegmentTree {
public:

    long long int min(int a, int b) {
        a--;
        b--;
        return min_recursive(0, 0, (T_array.size() - 1) / 2, a, b);
    }

    void add(int a, int b, long long int x) {
        a--;
        b--;
        add_recursive(0, 0, (T_array.size() - 1) / 2, a, b, x);
    }

    SegmentTree(vector <long long int> &a_i_array) {
        size = a_i_array.size();
        long long int x = 1;

        while (x < size) {
            x *= 2;
        }

        for (int i = 0; i < x - 1; i++) {
            T_array.push_back(0);
            additions_array.push_back(0);
        }

        for (int i = 0; i < x; i++) {

            if (i < size) {
                T_array.push_back(a_i_array.at(i));
            } else {
                T_array.push_back(0);
            }

            additions_array.push_back(0);
        }

        for (int i = x - 2; i >= 0; i--) {
            fill_parent_value(i);
        }
    }

    virtual ~SegmentTree() {
    }

    void set(int left, int right, long long int x) {
        left = T_array.size() / 2 + left - 1;
        right = T_array.size() / 2 + right - 1;

        for (int i = left; i <= right; i++) {
            T_array.at(i) = x;
            additions_array.at(x) = 0;
        }

        int patent_left = (left - 1) / 2;
        int patent_right = (right - 1) / 2;

        int parent_idx = patent_left;

        while (parent_idx > 0) {

            for (parent_idx = patent_left; parent_idx <= patent_right; parent_idx++) {
                fill_parent_value(parent_idx);
            }

            patent_left = (patent_left - 1) / 2;
            patent_right = (patent_right - 1) / 2;
            parent_idx = patent_left;
        }

        fill_parent_value(0);
    }


private:

    vector <long long int> T_array;
    vector <long long int> additions_array;
    int size;

    void fill_parent_value(int parent_v) {
        long long int child_1 = get(2 * parent_v + 1);
        long long int child_2 = get(2 * parent_v + 2);

        if (child_1 <= child_2) {
            T_array.at(parent_v) = child_1;
        } else {
            T_array.at(parent_v) = child_2;
        }
        additions_array.at(parent_v) = 0;
    }


    void add_recursive(int v, int left, int right, int a, int b, long long int x) {
        push(v, left, right);

        if ((left > b) || (right < a)) {
            return;
        }

        if ((left >= a) && (right <= b)) {
            additions_array.at(v) += x;
            return;
        }

        int middle = (left + right) / 2;

        add_recursive(2 * v + 1, left, middle, a, b, x);
        add_recursive(2 * v + 2, middle + 1, right, a, b, x);

    }

    long long int min_recursive(int v, int left, int right, int a, int b) {

        push(v, left, right);

        if ((left > b) || (right < a)) {
            return LONG_LONG_MAX;
        }

        if ((left >= a) && (right <= b)) {
            return get(v);
        }

        int middle = (left + right) / 2;

        long long int left_min = min_recursive(2 * v + 1, left, middle, a, b);
        long long int right_min = min_recursive(2 * v + 2, middle + 1, right, a, b);

        if (left_min <= right_min) {
            return left_min;
        } else {
            return right_min;
        }
    }

    long long int get(int i) {
        return T_array.at(i) + additions_array.at(i);
    }

    void push(int v, int left, int right) {

        if (additions_array.at(v) == 0) {
            return;
        }

        if ((right - left <= 1) && (v >= T_array.size() / 2)) {
            T_array.at(v) += additions_array.at(v);
            additions_array.at(v) = 0;
            return;

        } else {
            additions_array.at(2 * v + 1) += additions_array.at(v);
            additions_array.at(2 * v + 2) += additions_array.at(v);

            fill_parent_value(v);
        }


        int current_parent_idx = (v - 1) / 2;
        long long int current_parent_value = get(current_parent_idx);

        long long int child_1 = get(2 * current_parent_idx + 1);
        long long int child_2 = get(2 * current_parent_idx + 2);
        long long int lowest_child = child_2;

        if (child_1 <= child_2) {
            lowest_child = child_1;
        }

        if (current_parent_value != lowest_child) {
            while (current_parent_idx > 0) {
                fill_parent_value(current_parent_idx);
                current_parent_idx = (current_parent_idx - 1) / 2;
            }
            fill_parent_value(0);
        }
    }
};



void t0() {
    vector<long long int> a_i_array = {1, 2, 3};
    SegmentTree segment_tree(a_i_array);

    long long int result1 = segment_tree.min(1, 1);
    assert(result1 == 1);

    long long int result2 = segment_tree.min(2, 2);
    assert(result2 == 2);

    long long int result3 = segment_tree.min(3, 3);
    assert(result3 == 3);

    long long int result_12 = segment_tree.min(1, 2);
    assert(result_12 == 1);

    long long int result_23 = segment_tree.min(2, 3);
    assert(result_23 == 2);

    long long int result_13 = segment_tree.min(1, 3);
    assert(result_13 == 1);
}
void t1() {
    vector<long long int> a_i_array = {3, 1, 2, 8, 0, 1};
    SegmentTree segment_tree(a_i_array);

    long long int result1 = segment_tree.min(1, 1);
    assert(result1 == 3);

    long long int result2 = segment_tree.min(2, 2);
    assert(result2 == 1);

    long long int result3 = segment_tree.min(3, 3);
    assert(result3 == 2);

    long long int result4 = segment_tree.min(4, 4);
    assert(result4 == 8);

    long long int result5 = segment_tree.min(5, 5);
    assert(result5 == 0);

    long long int result6 = segment_tree.min(6, 6);
    assert(result6 == 1);

    long long int result_12 = segment_tree.min(1, 2);
    assert(result_12 == 1);

    long long int result_23 = segment_tree.min(2, 3);
    assert(result_23 == 1);

    long long int result_13 = segment_tree.min(1, 3);
    assert(result_13 == 1);

    long long int result_25 = segment_tree.min( 2, 5);
    assert(result_25 == 0);

    long long int result_56 = segment_tree.min(5, 6);
    assert(result_56 == 0);

    long long int result_16 = segment_tree.min(1, 6);
    assert(result_16 == 0);
}
void t2() {
    vector<long long int> a_i_array = {1, 2, 3};
    SegmentTree segment_tree(a_i_array);

    long long int result1 = segment_tree.min(1, 1);
    assert(result1 == 1);

    long long int result2 = segment_tree.min(2, 2);
    assert(result2 == 2);

    long long int result3 = segment_tree.min(3, 3);
    assert(result3 == 3);

    segment_tree.add(1, 3, 1);

    long long int result1_1 = segment_tree.min(1, 1);
    assert(result1_1 == 2);

    long long int result2_1 = segment_tree.min(2, 2);
    assert(result2_1 == 3);

    long long int result3_1 = segment_tree.min(3, 3);
    assert(result3_1 == 4);
}
void t3() {
    vector <long long int> a_i_array = {1, 2, 3, 4, 5};
    SegmentTree segment_tree(a_i_array);

    long long int result1 = segment_tree.min(1, 1);
    assert(result1 == 1);

    long long int result2 = segment_tree.min(2, 2);
    assert(result2 == 2);

    long long int result3 = segment_tree.min(3, 3);
    assert(result3 == 3);

    long long int result4 = segment_tree.min(4, 4);
    assert(result4 == 4);

    long long int result5 = segment_tree.min(5, 5);
    assert(result5 == 5);

    segment_tree.add(1, 5, 1);

    long long int result1_1 = segment_tree.min(1, 1);
    assert(result1_1 == 2);

    long long int result2_1 = segment_tree.min(2, 2);
    assert(result2_1 == 3);

    long long int result3_1 = segment_tree.min(3, 3);
    assert(result3_1 == 4);

    long long int result4_1 = segment_tree.min(4, 4);
    assert(result4_1 == 5);

    long long int result5_1 = segment_tree.min(5, 5);
    assert(result5_1 == 6);

    segment_tree.add(3, 4, 10);
    segment_tree.add(5, 5, 100);
    segment_tree.add(1, 4, 1000);

    long long int result1_2 = segment_tree.min(1, 1);
    assert(result1_2 == 1002);

    long long int result2_2 = segment_tree.min(2, 2);
    assert(result2_2 == 1003);

    long long int result3_2 = segment_tree.min(3, 3);
    assert(result3_2 == 1014);

    long long int result4_2 = segment_tree.min(4, 4);
    assert(result4_2 == 1015);

    long long int result5_2 = segment_tree.min(5, 5);
    assert(result5_2 == 106);

}
void t4() {
    vector <long long int> a_i_array = {1, 2, 3, 4, 5};
    SegmentTree segment_tree(a_i_array);

    long long int result1 = segment_tree.min(2, 5);
    assert(result1 == 2);

    long long int result2 = segment_tree.min(1, 5);
    assert(result2 == 1);

    long long int result3 = segment_tree.min(1, 4);
    assert(result3 == 1);

    long long int result4 = segment_tree.min(2, 4);
    assert(result4 == 2);

    long long int result0_1 = segment_tree.min(1, 1);
    assert(result0_1 == 1);

    segment_tree.add(1, 5, 1);

    long long int result4_1 = segment_tree.min(2, 5);
    assert(result4_1 == 3);

    segment_tree.add(2, 4, 4); // 2 7 8 9 6

    long long int result5 = segment_tree.min(2, 5);
    assert(result5 == 6);

    long long int result6 = segment_tree.min(1, 5);
    assert(result6 == 2);

    long long int result7 = segment_tree.min(1, 4);
    assert(result7 == 2);

    long long int result8 = segment_tree.min(3, 3);
    assert(result8 == 8);

}
void t5() {
    vector<long long int> a_i_array = {1, 2, 3, 4};
    SegmentTree segment_tree(a_i_array);

    segment_tree.set(1, 3, 3);

    long long int result1 = segment_tree.min(1, 1);
    assert(result1 == 3);

    segment_tree.set(2, 2, 5);

    long long int result2 = segment_tree.min(2, 4);
    assert(result2 == 3);

    segment_tree.set(3, 4, 0); // 3 5 0 0

    long long int result3 = segment_tree.min(3, 3);
    assert(result3 == 0);

    long long int result_12 = segment_tree.min(1, 2);
    assert(result_12 == 3);

    long long int result_23 = segment_tree.min(2, 3);
    assert(result_23 == 0);

    long long int result_14 = segment_tree.min(1, 4);
    assert(result_14 == 0);
}
void t6() {
    vector <long long int> a_i_array = {1, 2, 3, 4, 5};
    SegmentTree segment_tree(a_i_array);

    long long int result1 = segment_tree.min(2, 5);
    assert(result1 == 2);

    long long int result2 = segment_tree.min(1, 5);
    assert(result2 == 1);

    long long int result3 = segment_tree.min(1, 4);
    assert(result3 == 1);

    long long int result4 = segment_tree.min(2, 4);
    assert(result4 == 2);

    segment_tree.set(1, 3, 10);
    segment_tree.add(2, 4, 4); // 10 14 14 8 5

    long long int result5 = segment_tree.min(2, 5);
    assert(result5 == 5);

    long long int result6 = segment_tree.min(1, 5);
    assert(result6 == 5);

    long long int result7 = segment_tree.min(1, 4);
    assert(result7 == 8);

    long long int result8 = segment_tree.min(2, 4);
    assert(result8 == 8);

}

void test() {
    t0();
    t1();
    t2();
    t3();
    t4();
    t5();
    t6();
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
    SegmentTree segment_tree(a_i_array);

    int i, j;
    long long int x;

    while (cin >> operation) {
        if (operation == string("min")) {

            cin >> i >> j;

            long long int min_value = segment_tree.min(i, j);
            cout << min_value << std::endl;

        } else if (operation == string("set")) {

            cin >> i >> j >> x;
            segment_tree.set(i, j, x);

        } else if (operation == string("add")) {

            cin >> i >> j >> x;
            segment_tree.add(i, j, x);

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


