/* Используем самописную кучу, которую можно реализовать на стандартном саморасширяющемся массиве.
 *
 * D. Приоритетная очередь – 2
ограничение по времени на тест: 3 секунды
ограничение по памяти на тест: 256 мегабайт
ввод: стандартный ввод
вывод: стандартный вывод

Реализуйте приоритетную очередь. Ваша очередь должна поддерживать следующие операции: добавить элемент, извлечь минимальный элемент, уменьшить элемент, добавленный во время одной из операций.

Если какой-нибудь decrease-key уменьшает уже удаленный элемент, то ничего делать не нужно.

Все операции нумеруются по порядку, начиная с 1.

Входные данные
Содержится описание операций со очередью. В очередь помещаются и извлекаются только целые числа, не превышающие 10^9 по абсолютной величине.

Гарантируется, что для любого decrease-key x v из входных данных операция под номером 𝑥 является push.

Выходные данные
Выведите последовательно результат выполнения всех операций extract-min из двух целых чисел: значение элемента и номер операции push, при котором этот элемент был добавлен. Если в очереди есть несколько минимальных элементов, выведите любой. Если перед очередной операцией extract-min очередь пуста, выведите звездочку.

Пример
входные данные
push 3
push 4
push 2
extract-min
decrease-key 2 1
extract-min
extract-min
extract-min

выходные данные
2 3
1 2
3 1
*

 */


#include <iostream>
#include <string>
#include <assert.h>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::string;

class Entity {
    int value;
    int op_number;
    int idx;
public:
    Entity(int value, int opNumber, int idx) : value(value), op_number(opNumber), idx(idx) {}

    int getValue() const {
        return value;
    }

    int getOpNumber() const {
        return op_number;
    }

    void setIdx(int idx) {
        Entity::idx = idx;
    }

    virtual ~Entity() {

    }

    void setValue(int value) {
        Entity::value = value;
    }

    int getIdx() const {
        return idx;
    }
};

class Heap {
public:
    void insert(int value_to_add);

    std::pair<int, int> remove_min();

    void decrease_key(int operation_number, int new_value);

private:
    vector<Entity *> elements;

    vector<Entity *> elements_in_push_order;

    int op_number = 1;

    void swap(Entity *i, Entity *j);

    void sieve_up(int idx);

    void sieve_down();

    int get_parent_idx(int i) {
        return (i - 1) / 2;
    }

    int get_left_child_idx(int i) {
        return 2 * i + 1;
    }

    int get_right_child_idx(int i) {
        return 2 * i + 2;
    }

    void increase_op_number() {
        op_number++;
        elements_in_push_order.push_back(nullptr);
    }
};

void Heap::insert(int value_to_add) {
    Entity *new_pair = new Entity(value_to_add, op_number++, elements.size());
    elements.push_back(new_pair);
    sieve_up(elements.size() - 1);
    elements_in_push_order.push_back(new_pair);
}

std::pair<int, int> Heap::remove_min() {
    increase_op_number();
    if (elements.empty()) {
        return std::make_pair(-1, -1);
    }
    Entity *min_pair = elements.at(0);
    int min_value = min_pair->getValue();
    int push_num = min_pair->getOpNumber();
    delete min_pair;

    elements.at(0) = elements.at(elements.size() - 1);
    elements.at(0)->setIdx(0);
    elements.pop_back();
    elements_in_push_order.at(push_num - 1) = nullptr;
    sieve_down();

    return std::pair<int, int>(min_value, push_num);
}

void Heap::sieve_down() {
    if (elements.empty()) return;
    Entity *entity = elements.at(0);
    while (get_left_child_idx(entity->getIdx()) < elements.size()) {
        Entity *left_child = elements.at(get_left_child_idx(entity->getIdx()));
        // no right child
        if (get_right_child_idx(entity->getIdx()) >= elements.size()) {
            if (entity->getValue() > left_child->getValue()) {
                swap(entity, left_child);
            }
            return;
        }
        Entity *right_child = elements.at(get_right_child_idx(entity->getIdx()));

        Entity *min_child;
        if (left_child->getValue() < right_child->getValue()) {
            min_child = left_child;
        } else {
            min_child = right_child;
        }

        if (entity->getValue() > min_child->getValue()) {
            swap(entity, min_child);
        } else {
            return;
        }
    }
}

void Heap::sieve_up(int idx) {
    Entity *entity = elements.at(idx);
    while (entity->getIdx() != 0) {
        Entity *parent = elements.at(get_parent_idx(entity->getIdx()));
        if (entity->getValue() >= parent->getValue()) {
            return;
        }
        swap(entity, parent);
    }
}

void Heap::decrease_key(int operation_number, int new_value) {
    increase_op_number();
    if (elements_in_push_order.at(operation_number - 1) == nullptr) return;
    Entity *entity = elements_in_push_order.at(operation_number - 1);
    entity->setValue(new_value);
    sieve_up(entity->getIdx());

}

void Heap::swap(Entity *e1, Entity *e2) {
    int i = e1->getIdx();
    int j = e2->getIdx();
    e1->setIdx(j);
    e2->setIdx(i);

    elements.at(i) = e2;
    elements.at(j) = e1;
}

void t1() {
    Heap heap;
    heap.insert(2);
    auto result = heap.remove_min();
    assert(result.first == 2);
    assert(result.second == 1);
}

void t2() {
    Heap heap;
    heap.insert(10);
    heap.insert(15);
    heap.insert(1);
    heap.decrease_key(2, 3);
    auto r1 = heap.remove_min();
    assert(r1.first == 1);
    assert(r1.second == 3);

    auto r2 = heap.remove_min();
    assert(r2.first == 3);
    assert(r2.second == 2);

    heap.decrease_key(3, -1);

    auto r3 = heap.remove_min();
    assert(r3.first == 10);
    assert(r3.second == 1);

    auto r4 = heap.remove_min();
    assert(r4.second == -1);
    assert(r4.first == -1);

}

void test() {
    t1();
    t2();
}

void input() {
    string operation;
    Heap heap;
    while (cin >> operation) {
        if (operation == std::string("push")) {

            int value_to_push;
            cin >> value_to_push;

            heap.insert(value_to_push);

        } else if (operation == std::string("extract-min")) {

            std::pair<int, int> min_info = heap.remove_min();
            if (min_info.second < 0) {
                cout << "*" << std::endl;
            } else {
                cout << min_info.first << " " << min_info.second << std::endl;
            }

        } else if (operation == std::string("decrease-key")) {
            int x_push_operation_number, v_new_value;

            cin >> x_push_operation_number >> v_new_value;

            heap.decrease_key(x_push_operation_number, v_new_value);

        } else {
            throw;
        }

    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    input();
//    test();

    return 0;
}