/* требуется реализовать очередь на самописном саморасширяющемся циклическом массиве
 *
 * C. Реализуйте очередь
ограничение по времени на тест: 2 секунды
ограничение по памяти на тест: 256 мегабайт
ввод: стандартный ввод
вывод: стандартный вывод

Для каждой операции изъятия элемента выведите ее результат.

На вход программе подаются строки, содержащие команды. Каждая строка содержит одну команду. Команда — это либо "+ N", либо "-". Команда "+ N" означает добавление в очередь числа 𝑁, по модулю не превышающего 10^9. Команда "-" означает изъятие элемента из очереди.

Входные данные
В первой строке содержится количество команд — 𝑚 (1 ⩽ 𝑚 ⩽ 10^5). В последующих строках содержатся команды, по одной в каждой строке.

Выходные данные
Выведите числа, которые удаляются из очереди, по одному в каждой строке. Гарантируется, что изъятий из пустой очереди не производится.

Пример
входные данные
4
+ 1
+ 10
-
-

выходные данные
1
10
 */

#include <iostream>
#include <string>

using std::cin;
using std::cout;

class QueueWithArray {

private:
    int size;
    int capacity;
    int begin;
    int end;

    int TIMES_SIZE_LOWER_THAN_CAPACITY_FOR_DECREASE = 4;
    int LENGTH_INCREASE_DECREASE_MULTIPLIER = 2;

    long long int *array;

    void decrease_capacity();
    void increase_capacity();
    void move_elements();

public:
    void push(long long int value);

    void pop_front();

    int get_size();

    long long int front();

    QueueWithArray(int capacity) {
        this->capacity = capacity;
        array = new long long int[capacity];
        this->size = 0;
        begin = 0;
        end = 0;
    }

    ~QueueWithArray() {
        delete[] array;
    }

};

void QueueWithArray::move_elements() {
    long long int *new_array = new long long int[capacity];

    if (end > begin) {
        std::copy(array + begin, array + end, new_array);
    } else {
        std::copy(array + begin, array + size, new_array);
        std::copy(array, array + end, new_array + end - begin);
    }
    begin = 0;
    end = size;

    delete[] array;
    array = new_array;
}

void QueueWithArray::decrease_capacity() {
    capacity /= LENGTH_INCREASE_DECREASE_MULTIPLIER;

    this->move_elements();
}

void QueueWithArray::increase_capacity() {
    capacity *= LENGTH_INCREASE_DECREASE_MULTIPLIER;

    this->move_elements();
}

void QueueWithArray::push(long long int new_value) {
    if (size + 1 == capacity) {
        increase_capacity();
    }

    array[end] = new_value;
    end = (end + 1) % capacity;
    size++;
}

void QueueWithArray::pop_front() {
    array[begin] = 0;
    begin = (begin + 1) % capacity;

    size--;

    if (size != 0 && size * TIMES_SIZE_LOWER_THAN_CAPACITY_FOR_DECREASE < capacity) {
        decrease_capacity();
    }
}

long long int QueueWithArray::front() {
    return array[begin];
}

int QueueWithArray::get_size() {
    return size;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int num_of_operations;
    cin >> num_of_operations;

    int INITIAL_CAPACITY = 4;

    QueueWithArray queue(INITIAL_CAPACITY);

    char operation;

    for (int i = 0; i < num_of_operations; ++i) {
        cin >> operation;

        if (operation == '+') {
            int number;
            cin >> number;

            queue.push(number);

        } else {
            int value_from_queue = queue.front();
            cout << value_from_queue << std::endl;
            queue.pop_front();

        }
    }


    return 0;
}
