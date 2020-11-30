/*
 * B. Быстрый поиск в массиве
ограничение по времени на тест: 1 секунда
ограничение по памяти на тест: 512 мегабайт
ввод: стандартный ввод
вывод: стандартный вывод

Дан массив из 𝑛 целых чисел. Все числа от −10^9 до 10^9.

Нужно уметь отвечать на запросы вида «Cколько чисел имеют значения от 𝑙 до 𝑟»?

Входные данные
Число 𝑛 (1 ≤ 𝑛 ≤ 10^5). Далее 𝑛 целых чисел.

Затем число запросов 𝑘 (1 ≤ 𝑘 ≤ 10^5).

Далее 𝑘 пар чисел 𝑙,𝑟 (−10^9 ≤ 𝑙 ≤ 𝑟 ≤ 10^9) — собственно запросы.

Выходные данные
Выведите 𝑘 чисел — ответы на запросы.

Пример
входные данные
5
10 1 10 3 4
4
1 10
2 9
3 4
2 2
выходные данные
5 2 2 0
 */

#include <iostream>
#include <vector>

using std::vector;
using std::cin;
using std::cout;

void Swap(vector <int> &arr, int i, int j) {
    int temp;
    temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int Partition(vector <int> &arr, int begin, int end) {
    // take random index from begin to end and swap it with end index
    int pivot_id = rand() % (end - begin) + begin;

    Swap(arr, pivot_id, end);

    bool is_the_same = true;

    int pivot = arr[end];
    int i = begin;
    for (int j = begin; j < end; j++) {
        if (arr[j] != pivot) {
            is_the_same = false;
        }
        if (arr[j] < pivot) {
            Swap(arr, i, j);
            i++;
        }
    }
    if (is_the_same) {
        return -1;
    }
    Swap(arr, i, end);
    return i;
}

void QuickSort(vector <int> &arr, int begin, int end) {
    if (begin < end) {
        int pivot_id = Partition(arr, begin, end);
        if (pivot_id != -1) {
            QuickSort(arr, begin, pivot_id - 1);
            QuickSort(arr, pivot_id + 1, end);
        }
    }
}


int LowerBound(vector <int> &arr, int left, int right,
               int value_to_find) {

    if (left == right - 1) {
        return right;
    }

    int middle = (left + right) / 2;

    if (value_to_find <= arr[middle]) {
        return LowerBound(arr, left, middle, value_to_find);
    } else {
        return LowerBound(arr, middle, right, value_to_find);
    }
}

int UpperBound(vector <int> &arr, int left, int right,
               int value_to_find) {

    return LowerBound(arr, left, right, value_to_find + 1);
}

int CountNumbersFromLeftToRight(vector <int> &arr, int left_value_to_find,
                                int right_value_to_find) {

    int lower_idx = LowerBound(arr, -1, arr.size(), left_value_to_find);
    int upper_idx = UpperBound(arr, -1, arr.size(), right_value_to_find);

    return upper_idx - lower_idx;
}

int main() {

    int n;
    cin >> n;
    vector <int> initial_array;
    int temp;

    for (int i = 0; i < n; i++) {
        cin >> temp;
        initial_array.push_back(temp);
    }

    int k;
    cin >> k;

    QuickSort(initial_array, 0, n - 1);

    vector <int> results_array;
    int result, left_value_to_find, right_value_to_find;

    for (int j = 0; j < k; j++) {
        cin >> left_value_to_find >> right_value_to_find;

        result = CountNumbersFromLeftToRight(initial_array, left_value_to_find,
                                             right_value_to_find);

        results_array.push_back(result);
    }

    for (int i : results_array) {
        cout << i << std::endl;
    }

    return 0;
}