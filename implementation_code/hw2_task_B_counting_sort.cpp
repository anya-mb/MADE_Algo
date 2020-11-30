/*
B. Сортировка подсчетом
ограничение по времени на тест: 1 секунда
ограничение по памяти на тест: 64 мегабайта
ввод: стандартный ввод
вывод: стандартный вывод
Дан список из N элементов, которые принимают целые значения от 0 до 100. Отсортируйте этот список в порядке неубывания элементов. Выведите полученный список.

Входные данные
На одной строке дан массив из N элементов. (1≤N≤2·10^5) — количество элементов в массиве. Гарантируется, что все элементы массива принимают целые значения от 0 до 100.

Выходные данные
Выведите отсортированный список элeментов

Пример
входные данные
7 3 4 2 5
выходные данные
2 3 4 5 7

Примечание
Использовать встроенные функции сортировки нельзя.
 */


#include <iostream>
#include <vector>
#include <sstream>

const int kArrayValueLowerBound = 0;
const int kArrayValueUpperBound = 100;

using std::vector;

void CountingSort(vector <int> &arr) {
    vector <int> values_count(kArrayValueUpperBound - kArrayValueLowerBound + 1);

    for (int i = 0; i < arr.size(); i++) {
        values_count[arr[i]] += 1;
    }

    int arr_idx = 0;

    for (int i = 0; i < values_count.size(); i++) {
        while (values_count[i] > 0) {
            arr[arr_idx] = kArrayValueLowerBound + i;
            values_count[i] -= 1;
            arr_idx++;
        }
    }
}

int main() {
    std::string s;
    int elem;
    vector<int> array_to_sort;

    getline(std::cin, s);
    std::istringstream iss(s);

    while (iss >> elem) {
        array_to_sort.push_back(elem);
    }

    CountingSort(array_to_sort);

    for (int i : array_to_sort) {
        std::cout << i << " ";
    }

    return 0;
}