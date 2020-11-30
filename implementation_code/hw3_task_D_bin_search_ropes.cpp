/*
 * D. Веревочки
ограничение по времени на тест: 1 секунда
ограничение по памяти на тест: 256 мегабайт
ввод: стандартный ввод
вывод: стандартный вывод

С утра шел дождь, и ничего не предвещало беды. Но к обеду выглянуло солнце, и в лагерь заглянула СЭС. Пройдя по всем домикам и корпусам, СЭС вынесла следующий вердикт: бельевые веревки в жилых домиках не удовлетворяют нормам СЭС. Как выяснилось, в каждом домике должно быть ровно по одной бельевой веревке, и все веревки должны иметь одинаковую длину. В лагере имеется N бельевых веревок и K домиков. Чтобы лагерь не закрыли, требуется так нарезать данные веревки, чтобы среди получившихся веревочек было K одинаковой длины. Размер штрафа обратно пропорционален длине бельевых веревок, которые будут развешены в домиках. Поэтому начальство лагеря стремиться максимизировать длину этих веревочек.

Входные данные
В первой строке заданы два числа — N и K (1 ≤ N,K ≤ 10001). Далее в каждой из последующих N строк записано по одному числу — длине очередной бельевой веревки. Длина веревки задана в сантиметрах. Все длины лежат в интервале от 1 сантиметра до 100 километров включительно.

Выходные данные
В выходной файл следует вывести одно целое число — максимальную длину веревочек, удовлетворяющую условию, в сантиметрах. В случае, если лагерь закроют, выведите 0.

Пример
входные данные
4 11
802
743
457
539

выходные данные
200
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
        if (arr[j] > pivot) {
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

void QuickSortBackward(vector <int> &arr, int begin, int end) {
    if (begin < end) {
        int pivot_id = Partition(arr, begin, end);
        if (pivot_id != -1) {
            QuickSortBackward(arr, begin, pivot_id - 1);
            QuickSortBackward(arr, pivot_id + 1, end);
        }
    }
}


bool IsPossible(vector <int> &arr, int rope_length, int k_house_number) {
    int current_rope_len;
    int house_counter = 0;

    for (int i = 0; i < arr.size(); i++) {
        current_rope_len = arr[i];

        while (current_rope_len >= rope_length) {
            current_rope_len -= rope_length;
            house_counter += 1;
        }

        if (house_counter >= k_house_number) {
            return true;
        }
    }

    if (current_rope_len < rope_length && house_counter < k_house_number) {
        return false;
    }
}


int BinarySearchByAnswer(vector <int> &arr, int left,
                         int right, int k_house_number) {

    if (left == right - 1) {
        return left;
    }

    int middle = (left + right) / 2;
    bool middle_possible = IsPossible(arr, middle, k_house_number);

    if (middle_possible) {
        return BinarySearchByAnswer(arr, middle, right, k_house_number);
    } else {
        return BinarySearchByAnswer(arr, left, middle, k_house_number);
    }

}

int BinarySearchByAnswerWrapper(vector <int> &arr, int left,
                                int right, int k_house_number) {

    if (!IsPossible(arr, 1, k_house_number)) {
        return 0;
    }

    return BinarySearchByAnswer(arr, left, right, k_house_number);
}

int main() {

    int n_ropes, k_homes;
    cin >> n_ropes >> k_homes;

    vector <int> ropes_length_array;
    int temp;

    for (int i = 0; i < n_ropes; i++) {
        cin >> temp;
        ropes_length_array.push_back(temp);
    }

    QuickSortBackward(ropes_length_array, 0, n_ropes - 1);

    int lower_rope_length = 1;
    int upper_rope_length = ropes_length_array[0] + 1;

    int result_max_rope_length = BinarySearchByAnswerWrapper(ropes_length_array,
                                                             lower_rope_length,
                                                             upper_rope_length,
                                                             k_homes);

    cout << result_max_rope_length;

    return 0;
}