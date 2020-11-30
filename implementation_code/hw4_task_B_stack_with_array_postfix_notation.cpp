/* нужен стек, но в этот раз можно и нужно реализовать его на самописном саморасширяющемся массиве.
 *
 * B. Постфиксная запись
ограничение по времени на тест: 1 секунда
ограничение по памяти на тест: 256 мегабайт
ввод: стандартный ввод
вывод: стандартный вывод

В постфиксной записи (или обратной польской записи) операция записывается после двух операндов. Например, сумма двух чисел A и B записывается как A B +. Запись B C + D * обозначает привычное нам (B + C) * D, а запись A B C + D * + означает A + (B + C) * D. Достоинство постфиксной записи в том, что она не требует скобок и дополнительных соглашений о приоритете операторов для своего чтения.

Дано выражение в обратной польской записи. Определите его значение.

Входные данные
В единственной строке записано выражение в постфиксной записи, содержащее однозначные числа и операции +, -, *. Строка содержит не более 100 чисел и операций.

Выходные данные
Необходимо вывести значение записанного выражения. Гарантируется, что результат выражения, а также результаты всех промежуточных вычислений по модулю меньше 231.

Пример
входные данные
8 9 + 1 7 - *

выходные данные
-102

 *
 */

#include <iostream>
#include <string>

using std::cin;
using std::cout;

class StackWithArray {

private:
    int size;
    int capacity;

    int TIMES_SIZE_LOWER_THAN_CAPACITY_FOR_DECREASE = 4;
    int LENGTH_INCREASE_DECREASE_MULTIPLIER = 2;

    long long int *array;

    void decrease_capacity();
    void increase_capacity();
    void move_elements();

public:
    void push(long long int value);

    void pop();

    int get_size();

    long long int back();

    StackWithArray(int capacity) {
        this->capacity = capacity;
        array = new long long int[capacity];
        this->size = 0;
    }

    ~StackWithArray() {
        delete[] array;
    }

};

void StackWithArray::move_elements() {
    long long int *new_array = new long long int[capacity];

    std::copy(array, array + size, new_array);

    delete[] array;
    array = new_array;
}

void StackWithArray::decrease_capacity() {
    capacity /= LENGTH_INCREASE_DECREASE_MULTIPLIER;

    this->move_elements();
}

void StackWithArray::increase_capacity() {
    capacity *= LENGTH_INCREASE_DECREASE_MULTIPLIER;

    this->move_elements();
}

void StackWithArray::push(long long int new_value) {
    if (size + 1 == capacity) {
        increase_capacity();
    }

    array[size] = new_value;
    size++;
}

void StackWithArray::pop() {
    array[size - 1] = 0;

    size--;

    if (size != 0 && size * TIMES_SIZE_LOWER_THAN_CAPACITY_FOR_DECREASE < capacity) {
        decrease_capacity();
    }
}

long long int StackWithArray::back() {
    return array[size - 1];
}

int StackWithArray::get_size() {
    return size;
}


void PerformOperationOnStack(StackWithArray *stack, char operation) {
    long long int prev_value, before_prev_value, new_value;

    prev_value = stack->back();
    stack->pop();
    before_prev_value = stack->back();
    stack->pop();

    if (operation == '+') {
        new_value = before_prev_value + prev_value;
    } else if (operation == '-') {
        new_value = before_prev_value - prev_value;
    } else if (operation == '*') {
        new_value = before_prev_value * prev_value;
    } else {
        throw;
    }

    stack->push(new_value);
}

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int INITIAL_CAPACITY = 4;

    StackWithArray polish_notation_stack(INITIAL_CAPACITY);

    std::string line;
    std::getline(std::cin, line);

    for (char next_value : line) {

        if (next_value == ' ') {
            continue;
        }

        if (next_value >= '0' && next_value <= '9') {

            next_value -= '0';
            polish_notation_stack.push((long long int) next_value);

        } else {

            PerformOperationOnStack(&polish_notation_stack, next_value);
        }

    }

    cout << polish_notation_stack.back();

    return 0;
}