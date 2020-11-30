/* Dynamic programming task
 *
 * A. Кузнечик собирает монеты
ограничение по времени на тест: 2 секунды
ограничение по памяти на тест: 256 мегабайт
ввод: стандартный ввод
вывод: стандартный вывод

Кузнечик прыгает по столбикам, расположенным на одной линии на равных расстояниях друг от друга. Столбики имеют порядковые номера от 1 до N. В начале Кузнечик сидит на столбике с номером 1 и хочет добраться до столбика с номером N. Он может прыгнуть вперед на расстояние от 1 до K столбиков, считая от текущего.

На каждом столбике Кузнечик может получить или потерять несколько золотых монет (для каждого столбика это число известно). Определите, как нужно прыгать Кузнечику, чтобы собрать наибольшее количество золотых монет. Учитывайте, что Кузнечик не может прыгать назад.

Входные данные
В первой строке вводятся два натуральных числа: N и K (2 ≤ N, K ≤ 10000), разделённые пробелом. Во второй строке записаны через пробел N-2 целых числа – количество монет, которое Кузнечик получает на каждом столбике, от 2-го до N-1-го. Если это число отрицательное, Кузнечик теряет монеты. Гарантируется, что все числа по модулю не превосходят 10000.

Выходные данные
В первой строке программа должна вывести наибольшее количество монет, которое может собрать Кузнечик. Во второй строке выводится число прыжков Кузнечика, а в третьей строке – номера всех столбиков, которые посетил Кузнечик (через пробел в порядке возрастания).

Если правильных ответов несколько, выведите любой из них.

Пример
входные данные
5 3
2 -3 5

выходные данные
7
3
1 2 4 5

 */


#include <iostream>
#include <string>
#include <assert.h>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

void solve_grasshopper(int n, int k, vector <int> rewards) {
    long long int result = 0;

    vector <long long int> cumulative_rewards;
    vector <int> positions_for_max;

    for (int i = 0; i < n; i++) {
        cumulative_rewards.push_back(0);
    }

    for (int i = 1; i < n; i++) {

        long long int current_reward = rewards[i];
        cumulative_rewards[i] += current_reward;

        long long int max_from_prev_k_steps = LONG_LONG_MIN;
        int position_for_max = 0;

        for (int j = i - k; j < i; j++) {

            if (j < 0) {
                continue;
            }

            if (max_from_prev_k_steps <= cumulative_rewards[j]) {
                max_from_prev_k_steps = cumulative_rewards[j];
                position_for_max = j;
            }
        }

        if (positions_for_max.size() > 0) {
            if (positions_for_max.back() != position_for_max) {
                positions_for_max.push_back(position_for_max);
            }

        } else {
            positions_for_max.push_back(position_for_max);
        }


        cumulative_rewards[i] += max_from_prev_k_steps;

    }

    result = cumulative_rewards[n - 1];

    cout << result << std::endl;
    cout << positions_for_max.size() << std::endl;

    positions_for_max.push_back(n - 1);

    for (auto position : positions_for_max) {
        cout << position + 1 << " ";
    }
}


void input() {
    int n, k;
    cin >> n >> k;

    vector <int> rewards_on_positions;
    rewards_on_positions.push_back(0);

    for (int i = 0; i < n - 2; i++) {
        int current_reward;
        cin >> current_reward;
        rewards_on_positions.push_back(current_reward);
    }

    rewards_on_positions.push_back(0);

    solve_grasshopper(n, k, rewards_on_positions);
}



int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    input();

    return 0;
}