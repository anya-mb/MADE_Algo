/* Dynamic programming task
 * D. Расстояние по Левенштейну
ограничение по времени на тест: 2 секунды
ограничение по памяти на тест: 256 мегабайт
ввод: стандартный ввод
вывод: стандартный вывод

Дана текстовая строка. С ней можно выполнять следующие операции:

1. Заменить один символ строки на другой символ.
2. Удалить один произвольный символ.
3. Вставить произвольный символ в произвольное место строки.

Например, при помощи первой операции из строки «СОК» можно получить строку «СУК», при помощи второй операции — строку «ОК», при помощи третьей операции — строку «СТОК».

Минимальное количество таких операций, при помощи которых можно из одной строки получить другую, называется стоимостью редактирования или расстоянием Левенштейна.

Определите расстояние Левенштейна для двух данных строк.

Входные данные
Программа получает на вход две строки, длина каждой из которых не превосходит 1000 символов, строки состоят только из заглавных латинских букв.

Выходные данные
Требуется вывести одно число — расстояние Левенштейна для данных строк.

Пример
входные данные
ABCDEFGH
ACDEXGIH

выходные данные
3

 */


#include <iostream>
#include <string>
#include <assert.h>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

int solve_levenshtein_distance(std::string first_sequence, std::string second_sequence) {
    int n = first_sequence.size() + 1;
    int m = second_sequence.size() + 1;

    vector<int> max_mutual_len_array;

    char letter_first_seq, letter_second_seq;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            max_mutual_len_array.push_back(-1);
        }
    }

    for (int i = 0; i < n; i++) {
        max_mutual_len_array.at(i) = i;
    }

    for (int j = 0; j < m; j++) {
        max_mutual_len_array.at(j * n) = j;
    }


    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {

            int diag_idx = (j - 1) * n + i - 1;
            int left_idx = j * n + i - 1;
            int up_idx = (j - 1) * n + i;
            int current_idx = j * n + i;

            letter_first_seq = first_sequence.at(i - 1);
            letter_second_seq = second_sequence.at(j - 1);

            int left_value = max_mutual_len_array.at(left_idx);
            int up_value = max_mutual_len_array.at(up_idx);
            int diag_value = max_mutual_len_array.at(diag_idx);

            if ((diag_value <= left_value) && (diag_value <= up_value)) {

                if (letter_first_seq == letter_second_seq) {
                    max_mutual_len_array.at(current_idx) = diag_value;

                } else {
                    max_mutual_len_array.at(current_idx) = diag_value + 1;
                }

            } else if ((left_value <= up_value) && (left_value <= diag_value)) {
                max_mutual_len_array.at(current_idx) = left_value + 1;

            } else if ((up_value <= left_value) && (up_value <= diag_value)) {
                max_mutual_len_array.at(current_idx) = up_value + 1;

            } else {
                throw;
            }

        }
    }

    int levenshtein_distance = max_mutual_len_array.back();

    return levenshtein_distance;
}


void input() {

    std::string first_sequence;
    cin >> first_sequence;

    std::string second_sequence;
    cin >> second_sequence;

    int result_distance = solve_levenshtein_distance(first_sequence, second_sequence);

    cout << result_distance;
}

void t0() {

    std::string first_sequence =  "BCEFG";
    std::string second_sequence = "CEXGI";

    int result_distance2 = solve_levenshtein_distance(first_sequence, second_sequence);
    assert(result_distance2 == 3);

}

void t1() {

    std::string first_sequence = "ABCDEFGH";
    std::string second_sequence = "ACDEXGIH";

    int result_distance2 = solve_levenshtein_distance(first_sequence, second_sequence);
    assert(result_distance2 == 3);

}

void t2() {
    std::string first_sequence = "ABCDE";
    std::string second_sequence = "BDA";

    int result_distance2 = solve_levenshtein_distance(first_sequence, second_sequence);
    assert(result_distance2 == 3);
}

void t3() {
    std::string first_sequence = "ABCDEFGH";
    std::string second_sequence = "AMCDEFGH";

    int result_distance2 = solve_levenshtein_distance(first_sequence, second_sequence);
    assert(result_distance2 == 1);
}

void t4() {
    std::string first_sequence = "ABCDEFGH";
    std::string second_sequence = "ABCDFGH";

    int result_distance2 = solve_levenshtein_distance(first_sequence, second_sequence);
    assert(result_distance2 == 1);
}

void t5() {
    std::string first_sequence = "ABCDEFGH";
    std::string second_sequence = "ALCDFH";

    int result_distance2 = solve_levenshtein_distance(first_sequence, second_sequence);
    assert(result_distance2 == 3);
}

void t6() {
    std::string first_sequence = "ABCDEFGGGGGGH";
    std::string second_sequence = "AMCDEFGH";

    int result_distance2 = solve_levenshtein_distance(first_sequence, second_sequence);
    assert(result_distance2 == 6);
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

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    input();

//    test();

    return 0;
}


