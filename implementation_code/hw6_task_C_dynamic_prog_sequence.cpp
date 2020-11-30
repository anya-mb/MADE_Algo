/* Dynamic programming task
 *
 * C. Наибольшая возрастающая подпоследовательность
ограничение по времени на тест2 секунды
ограничение по памяти на тест256 мегабайт
вводстандартный ввод
выводстандартный вывод
Пусть a_1,a_2,...,a_n — числовая последовательность. Длина последовательности — это количество элементов этой последовательности. Последовательность a_i1,a_i2,...,a_ik называется подпоследовательностью последовательности a, если 1 ≤ i1 < i2 <...< ik ≤ n. Последовательность a называется возрастающей, если a_1 < a_2 < ... < a_n.

Вам дана последовательность, содержащая n целых чисел. Найдите ее самую длинную возрастающую подпоследовательность.

Входные данные
В первой строке задано одно число n (1 ≤ n ≤ 2000) — длина подпоследовательности. В следующей строке задано n целых чисел a_i (-10^9 ≤ a_i ≤ 10^9) — элементы последовательности.

Выходные данные
В первой строке выведите число k — длину наибольшей возрастающей подпоследовательности. В следующей строке выведите k чисел — саму подпоследовательность.

Примеры
входные данные
8
1 4 1 5 3 3 4 2
выходные данные
3
1 4 5


входные данные
3
1 2 3
выходные данные
3
1 2 3
 */


#include <iostream>
#include <string>
#include <assert.h>
#include <vector>

using std::cin;
using std::cout;
using std::vector;


vector <int> solve_sequence(vector <int> &seq) {
    vector <int> seq_history;
    vector <int> max_length_of_sequences;

    seq_history.push_back(0);


    for (int i = 1; i < seq.size(); i++) {
        int current_number = seq.at(i);

        int max_seq_len_before = 0;
        int max_position = 0;

        for (int j = 0; j < i; j++) {
            int len_before = max_length_of_sequences.at(j);
            int number_before = seq.at(j);

            if ((current_number > number_before) && (max_seq_len_before <= len_before)) {
                max_seq_len_before = len_before;
                max_position = j;
            }
        }

        max_length_of_sequences.push_back(max_seq_len_before + 1);
        seq_history.push_back(max_position);
    }

    int last_max_position = 0;
    int max_len = max_length_of_sequences.at(last_max_position);

    for (int i = 1; i < max_length_of_sequences.size(); i++) {
        int current_length = max_length_of_sequences.at(i);

        if (current_length > max_len) {
            max_len = current_length;
            last_max_position = i;
        }
    }

    vector <int> result_seq;

    int counter = 1;

    while (last_max_position > 0) {
        result_seq.push_back(seq.at(last_max_position));
        last_max_position = seq_history.at(last_max_position);
        counter++;

        if ((last_max_position == 0) || (counter >= max_len)) {
            result_seq.push_back(seq.at(last_max_position));
            break;
        }
    }

    vector <int> final_result_seq;

    for (int r = result_seq.size() - 1; r >= 0; r--) {
        final_result_seq.push_back(result_seq.at(r));
    }

    if (final_result_seq.size() == 0) {
        final_result_seq.push_back(seq.at(0));
    }

    return final_result_seq;
}


void input() {
    int n;
    cin >> n;

    vector <int> initial_sequence;

    for (int i = 0; i < n; i++) {
        int new_number;
        cin >> new_number;
        initial_sequence.push_back(new_number);
    }

    vector <int> result_seq = solve_sequence(initial_sequence);

    cout << result_seq.size() << std::endl;

    for (auto elem: result_seq) {
        cout << elem << " ";
    }

}


void t1() {

    vector <int> initial_sequence = {1, 2, 3};

    vector <int> result_seq = solve_sequence(initial_sequence);

    assert(result_seq.size() == 3);

    vector <int> true_seq = {1, 2, 3};
    assert(result_seq == true_seq);
}

void t2() {
    vector <int> initial_sequence = {1, 4, 1, 5, 3, 3, 4, 2};

    vector <int> result_seq = solve_sequence(initial_sequence);

    assert(result_seq.size() == 3);

    vector <int> true_seq = {1, 4, 5};
    assert(result_seq == true_seq);
}

void t3() {
    vector <int> initial_sequence = {1, 4, 1, 5, 3, 3, 4, 2, 5};

    vector <int> result_seq = solve_sequence(initial_sequence);

    assert(result_seq.size() == 4);

    vector <int> true_seq = {1, 3, 4, 5};
    assert(result_seq == true_seq);
}

void t4() {
    vector <int> initial_sequence = {3, 4, 1, 2};

    vector <int> result_seq = solve_sequence(initial_sequence);

    assert(result_seq.size() == 2);

    vector <int> true_seq = {3, 4};
    assert(result_seq == true_seq);
}

void t5() {
    vector <int> initial_sequence = {5, 4, 3, 2, 1};

    vector <int> result_seq = solve_sequence(initial_sequence);

    assert(result_seq.size() == 1);

    vector <int> true_seq = {5};
    assert(result_seq == true_seq);
}

void test() {
    t1();
    t2();
    t3();
    t4();
    t5();
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    input();

//    test();

    return 0;
}
