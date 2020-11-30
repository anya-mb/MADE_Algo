/* Требуется использовать самописный стек на связном списке (тоже самописном)
 *
 * A. Минимум на стеке
ограничение по времени на тест: 2 секунды
ограничение по памяти на тест: 256 мегабайт
ввод: стандартный ввод
вывод: стандартный вывод

Вам требуется реализовать структуру данных, выполняющую следующие операции:

1. Добавить элемент 𝑥 в конец структуры.
2. Удалить последний элемент из структуры.
3. Выдать минимальный элемент в структуре.

Входные данные
В первой строке входного файла задано одно целое число 𝑛 — количество операций (1≤ 𝑛 ≤ 10^6). В следующих 𝑛 строках заданы сами операции. В 𝑖–ой строке число 𝑡𝑖 — тип операции (1, если операция добавления. 2, если операция удаления. 3, если операция минимума). Если задана операция добавления, то через пробел записано целое число 𝑥 — элемент, который следует добавить в структуру (−10^9 ≤ 𝑥 ≤ 10^9). Гарантируется, что перед каждой операцией удаления или нахождения минимума структура не пуста.

Выходные данные
Для каждой операции нахождения минимума выведите одно число — минимальный элемент в структуре. Ответы разделяйте переводом строки.

Пример
входные данные
8
1 2
1 3
1 -3
3
2
3
2
3

выходные данные
-3
2
2
 */

#include <iostream>
#include <vector>

using std::vector;
using std::cin;
using std::cout;

class Node {
public:
    long long int data;
    Node* next;

    Node (long long int);
    void print ();
};

Node::Node(long long int value) {
    data = value;
    next = nullptr;
}

void Node::print() {
    cout << data;
}

class StackWithLinkedList {

public:
    Node* head;
    int size = 0;

    void push (Node* new_node);
    void pop ();
    int get_size ();
    long long int back ();

    void print ();
};

int StackWithLinkedList::get_size() {
    return size;
}

void StackWithLinkedList::push(Node* new_node) {

    if (size == 0) {
        head = new_node;

    } else {
        new_node->next = head;
        head = new_node;
    }

    size++;
}

void StackWithLinkedList::pop() {
    if (size == 0) {
        return;
    }

    Node* tmp = head;
    head = head->next;

    delete tmp;

    size--;
}

long long int StackWithLinkedList::back() {
    return head->data;
}

void StackWithLinkedList::print() {
    Node* tmp = head;

    while (tmp != nullptr) {
        tmp->print();
        cout << std::endl;
        tmp = tmp->next;
    }
}


class MinStack {
public:
    StackWithLinkedList stack_for_min;

    void push (Node* node);
    void pop ();
    int get_size ();
    long long int back ();

    void print();
};

void MinStack::push(Node *node) {

    if (stack_for_min.get_size() == 0) {
        stack_for_min.push(node);

    } else {
        long long int current_min = stack_for_min.back();

        stack_for_min.push(node);

        if (current_min < node->data) {
            stack_for_min.head->data = current_min;
        }

    }
}

void MinStack::pop() {
    stack_for_min.pop();
}

int MinStack::get_size() {
    return stack_for_min.get_size();
}

long long int MinStack::back() {
    return stack_for_min.back();
}

void MinStack::print() {
    cout << "stack_for_min:" << std::endl;
    stack_for_min.print();
}


int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    cin >> n;

    int stack_operation;

    long long int value_to_add, min_value;

    MinStack stack;

    vector <int> min_array;


    for (int i = 0; i < n; i++) {
        cin >> stack_operation;

        if (stack_operation == 1) {
            cin >> value_to_add;
            Node *new_node = new Node(value_to_add);
            stack.push(new_node);

        } else if (stack_operation == 2) {
            stack.pop();

        } else if (stack_operation == 3) {
            min_value = stack.back();
            min_array.push_back(min_value);

        } else {
            continue;
        }

    }

    for (int i : min_array) {
        cout << i << std::endl;
    }

    return 0;
}