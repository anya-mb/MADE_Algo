/* Dynamic programming task
 *
 * B. Черепаха и монеты
ограничение по времени на тест: 2 секунды
ограничение по памяти на тест: 256 мегабайт
ввод: стандартный ввод
вывод: стандартный вывод

Черепаха хочет переползти из левого верхнего угла поля размером N на M клеток (2 ≤ N, M ≤ 1000) в правый нижний. За один шаг она может переместиться на соседнюю клетку вправо или на соседнюю клетку вниз. Кроме того, проходя через каждую клетку, Черепаха получает (или теряет) несколько золотых монет (это число известно для каждой клетки).

Определите, какое максимальное количество монет может собрать Черепаха по пути и как ей нужно идти для этого.

Входные данные
В первой строке вводятся два натуральных числа: N и M (2 ≤ N, M ≤ 1000), разделённые пробелом. В каждой из следующих N строк записаны через пробел по M чисел aij(|aij| ≤ 10), которые обозначают количество монет, получаемых Черепашкой при проходе через каждую клетку. Если это число отрицательное, Черепашка теряет монеты.

Выходные данные
В первой строке программа должна вывести наибольшее количество монет, которое может собрать Черепаха. Во второй строке без пробелов выводятся команды, которые нужно выполнить Черепахе: буква 'R' (от слова right) обозначает шаг вправо, а буква 'D' (от слова down) – шаг вниз.

Пример
входные данные
3 3
0 2 -3
2 -5 7
1 2 0

выходные данные
6
RRDD

 */


#include <iostream>
#include <string>
#include <assert.h>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

void input() {
    int n, m;
    cin >> n >> m;

    int result_num_of_coins;

    int rewards_on_positions[n][m];
    int cumulative_rewards[n][m];
    int travel_history[n][m];

    const int GO_RIGHT = 0;
    const int GO_DOWN = 1;

    int reward;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> reward;
            rewards_on_positions[i][j] = reward;
            cumulative_rewards[i][j] = 0;
            travel_history[i][j] = -1;
//            travel_history[n][m] = -1;
        }
    }

    cout << std::endl;

    cout << "rewards_on_positions: " << std::endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << rewards_on_positions[i][j] << " ";
        }
        cout << std::endl;
    }

    cout << std::endl;

    cout << "cumulative_rewards: " << std::endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << cumulative_rewards[i][j] << " ";
        }
        cout << std::endl;
    }

    cout << std::endl;

    int max_travel_reward;

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < m; j++) {

            int current_reward = rewards_on_positions[i][j];
            cumulative_rewards[i][j] += current_reward;

            if (i == 0) {

                if (j == 0) {
                    travel_history[i][j] = -1;
                    max_travel_reward = 0;

                } else {
                    max_travel_reward = cumulative_rewards[i][j - 1];
                    travel_history[i][j] = GO_RIGHT;
                }

            } else {

                if (j == 0) {
                    max_travel_reward = cumulative_rewards[i - 1][j];
                    travel_history[i][j] = GO_DOWN;

                } else {

                    if (cumulative_rewards[i - 1][j] >= cumulative_rewards[i][j - 1]) {
                        max_travel_reward = cumulative_rewards[i - 1][j];
                        travel_history[i][j] = GO_DOWN;

                    } else {
                        max_travel_reward = cumulative_rewards[i][j - 1];
                        travel_history[i][j] = GO_RIGHT;
                    }

                }
            }

            cumulative_rewards[i][j] += max_travel_reward;
        }
    }

    cout << std::endl;

    cout << "cumulative_rewards: " << std::endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << cumulative_rewards[i][j] << " ";
        }
        cout << std::endl;
    }
//
//    cout << "travel_history: " << std::endl;
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < m; j++) {
//            cout << travel_history[i][j] << " ";
//        }
//        cout << std::endl;
//    }
//    cout << std::endl;

    result_num_of_coins = cumulative_rewards[n - 1][m - 1];

    cout << result_num_of_coins << std::endl;

    int row_iterator = n - 1;
    int col_iterator = m - 1;
    int direction;

    vector <std::string> directions;

    while ((row_iterator > 0) || (col_iterator > 0)) {

        direction = travel_history[row_iterator][col_iterator];

        if (direction == GO_RIGHT) {
            col_iterator--;
            directions.push_back("R");
        } else if (direction == GO_DOWN) {
            row_iterator--;
            directions.push_back("D");
        } else {
            throw;
        }

    }

//    std::reverse(directions.begin(), directions.end());

//    for (auto letter : directions) {
//        cout << letter;
//    }

    for (int k = directions.size() - 1; k >= 0; k--) {
        cout << directions[k];
    }
}



int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    input();

    return 0;
}