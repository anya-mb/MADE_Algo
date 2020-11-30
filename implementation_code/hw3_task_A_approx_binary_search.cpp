/*
A. Приближенный двоичный поиск
ограничение по времени на тест: 2 секунды
ограничение по памяти на тест: 256 мегабайт
ввод: стандартный ввод
вывод: стандартный вывод

Даны два массива. Первый массив отсортирован по неубыванию, второй массив содержит запросы — целые числа.
Для каждого запроса выведите число из первого массива наиболее близкое (то есть с минимальным модулем разности) к числу в этом запросе . Если таких несколько, выведите меньшее из них.

Входные данные
В первой строке входных данных содержатся числа n и k (0<n,k≤10^5). Во второй строке задаются n чисел первого массива, отсортированного по неубыванию, а в третьей строке — k чисел второго массива. Каждое число в обоих массивах по модулю не превосходит 2·10^9 .

Выходные данные
Для каждого из k чисел выведите в отдельную строку число из первого массива, наиболее близкое к данному. Если таких несколько, выведите меньшее из них.

Пример
входные данные
5 5
1 3 5 7 9
2 4 8 1 6

выходные данные
1
3
7
1
5
 */

#include <iostream>
#include <vector>

using std::vector;
using std::cin;
using std::cout;

vector <long long int> ReadArray(int array_length) {
    vector<long long int> initial_array;
    int num;

    for (int i = 0; i < array_length; i++) {
        cin >> num;
        initial_array.push_back(num);
    }

    return initial_array;
}

long long int ApproximateBinarySearch(const vector <long long int> &arr, int left,
                                      int right, long long int num_to_find) {

    if (right - left == 1) {
        if (num_to_find == arr[left]) return num_to_find;
        if (num_to_find == arr[left+1]) return num_to_find;

        if (abs(num_to_find - arr[left]) <= abs(arr[left+1] - num_to_find)) {
            return arr[left];
        } else {
            return arr[left+1];
        }
    }

    int m = (left + right) / 2;

    if (num_to_find == arr[m]) {
        return arr[m];
    }

    if (num_to_find < arr[m]) {
        return ApproximateBinarySearch(arr, left, m, num_to_find);
    } else {
        return ApproximateBinarySearch(arr, m, right, num_to_find);
    }

}

long long int ApproximateBinarySearchWrapper(const vector <long long int> & arr, int left,
                                             int right, long long int num_to_find) {
    if (arr.size() == 1) {
        return arr[0];
    }

    if (num_to_find <= arr[0]) {
        return arr[0];
    }

    if (num_to_find >= arr[arr.size()-1]) {
        return arr[arr.size() - 1];
    }

    return ApproximateBinarySearch(arr, left, right, num_to_find);
}

int main() {
    int n, k;
    cin >> n >> k;

    vector<long long int> initial_array = ReadArray(n);
    vector<long long int> numbers_to_find_array = ReadArray(k);

    vector<int> results;
    long long int result;

    for (int j = 0; j < k; j++) {
        result = ApproximateBinarySearchWrapper(initial_array, 0, n,
                                                numbers_to_find_array[j]);
        results.push_back(result);
    }

    for (int p = 0; p < k; p++) {
        cout << results[p] << std::endl;
    }

    return 0;
}