/* Требуется реализовать Set на самописной Хеш-таблице с использованием открытой адресации.
 *
 * A. Set
ограничение по времени на тест: 2 секунды
ограничение по памяти на тест: 256 мегабайт
ввод: стандартный ввод
вывод: стандартный вывод

Реализуйте множество с использованием хеш таблицы.

Входные данные
Входной файл содержит описание операций, их количество не превышает 1000000. В каждой строке находится одна из следующих операций:

insert 𝑥 — добавить элемент 𝑥 в множество. Если элемент уже есть в множестве, то ничего делать не надо.
delete 𝑥 — удалить элемент 𝑥. Если элемента 𝑥 нет, то ничего делать не надо.
exists 𝑥 — если ключ 𝑥 есть в множестве выведите «true», если нет «false».

В множество помещаются и извлекаются только целые числа, не превышающие по модулю 10^9.

Выходные данные
Выведите последовательно результат выполнения всех операций exists. Следуйте формату выходного файла из примера.

Пример
входные данные
insert 2
insert 5
insert 3
exists 2
exists 4
insert 2
delete 2
exists 2

выходные данные
true
false
false

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
public:
    Entity(int new_value) {
        value = new_value;
        status = EMPTY_CODE;
    }

    int get_value() {
        return value;
    }

    bool is_empty() {
        return status == EMPTY_CODE;
    }

    bool is_occupied() {
        return status == OCCUPIED_CODE;
    }

    bool is_deleted() {
        return status == DELETED_CODE;
    }

    void delete_value() {
        status = DELETED_CODE;
    }

    virtual ~Entity() {

    }

    void update_value(int new_value) {
        Entity::value = new_value;
        Entity::status = OCCUPIED_CODE;
    }

    void set_empty() {
        Entity::status = EMPTY_CODE;
    }

private:
    int value;
    const static int EMPTY_CODE = 1;
    const static int OCCUPIED_CODE = 2;
    const static int DELETED_CODE = 3;

    int status = EMPTY_CODE;
};

class Set {
public:
    Set();
    void insert(int x);
    void delete_element(int x);
    bool contains(int x);

    virtual ~Set();

private:

    static const int MAX_NUMBER_OF_ELEMENTS = 2000000;
    static const int PRIME_FOR_HASH = 4000081;
    static const int MULTIPLIER_FOR_HASH = 10007;

    vector <Entity *> elements;

    int rip_count = 0;
    int size = 0;

    int calculate_position(int value) {
        long long int new_x = value % PRIME_FOR_HASH;
        long long int result = ((new_x * MULTIPLIER_FOR_HASH) % PRIME_FOR_HASH) % MAX_NUMBER_OF_ELEMENTS;
        if (result < 0) {
            result += MAX_NUMBER_OF_ELEMENTS;
        }
        return (int) result;
    }

    void reform_set();

    int find_element_position(int value);

    int calc_next_circular_position(int position) {
        return (position + 1) % MAX_NUMBER_OF_ELEMENTS;;
    }
};



void Set::insert(int x) {
    if (find_element_position(x) >= 0) {
        return;
    }

    Entity* element;
    int position = calculate_position(x);

    for (int i = 0; i < MAX_NUMBER_OF_ELEMENTS; i++) {
        element = elements.at(position);

        if (element->is_empty() || element->is_deleted()) {
            element->update_value(x);
            size++;
            break;
        }

        position = calc_next_circular_position(position);

    }

}

void Set::delete_element(int x) {
    int position = find_element_position(x);

    if (position != -1) {
        elements.at(position)->delete_value();
        rip_count++;
        size--;
    }


    if ((rip_count > MAX_NUMBER_OF_ELEMENTS / 4)
    && (size > MAX_NUMBER_OF_ELEMENTS / 3)) {
        reform_set();
    };

}

bool Set::contains(int x) {
    int position = find_element_position(x);
    return position >= 0;
}

int Set::find_element_position(int value) {
    if (size == 0) {
        return -1;
    }

    int position = calculate_position(value);

    Entity* element = elements.at(position);

    int element_seen_counter = 0;

    while (!element->is_empty()) {
        if (element->get_value() == value && !element->is_deleted()) {
            return position;
        }

        position = calc_next_circular_position(position);
        element = elements.at(position);
        element_seen_counter++;

        if (element_seen_counter == MAX_NUMBER_OF_ELEMENTS) {
            break;
        }
    }

    return -1;
}


void Set::reform_set() {
    vector <Entity *> previous_elements;
    size = 0;

    for (int i = 0; i < MAX_NUMBER_OF_ELEMENTS; i++) {
        Entity* entity = elements.at(i);

        previous_elements.push_back(entity);

        Entity* new_entity = new Entity(0);
        elements.at(i) = new_entity;
    }

    for (int i = 0; i < MAX_NUMBER_OF_ELEMENTS; i++) {
        Entity* entity = previous_elements.at(i);

        if (entity->is_occupied()) {
            entity->set_empty();
            insert(entity->get_value());
        }
        delete entity;
    }
    rip_count = 0;

}

Set::Set() {

    for (int i = 0; i < MAX_NUMBER_OF_ELEMENTS; i++) {
        Entity* entity = new Entity(0);
        elements.push_back(entity);
    }
}

Set::~Set() {

}


void t1() {
    Set set;

    set.insert(2);
    assert(set.contains(2));

    set.delete_element(2);
    assert(!set.contains(2));
}
void t2() {
    Set set;

    set.insert(2);
    set.insert(5);
    set.insert(3);
    bool result = set.contains(2);
    assert(result == true);

    bool result2 = set.contains(4);
    assert(result2 == false);

    set.insert(2);

    set.delete_element(2);
    bool result3 = set.contains(2);
    assert(result3 == false);
}


void t3() {
    Set set;

    set.insert(2);
    set.insert(5);
    set.insert(8);
    bool result = set.contains(2);
    assert(result == true);

    bool result2 = set.contains(12);
    assert(result2 == false);

    set.insert(8);
    set.insert(12);
    set.insert(22);

    set.delete_element(2);
    bool result3 = set.contains(2);
    assert(result3 == false);

    bool result4 = set.contains(12);
    assert(result4 == true);

    set.insert(2);
    set.insert(18);
    set.insert(32);
    set.delete_element(2);
    bool result5 = set.contains(2);
    assert(result5 == false);

    bool result6 = set.contains(12);
    assert(result6 == true);

    set.insert(42);
    set.insert(52);
    set.insert(62);

    bool result7 = set.contains(22);
    assert(result7 == true);

    bool result8 = set.contains(42);
    assert(result8 == true);

    set.delete_element(52);
    bool result9 = set.contains(52);
    assert(result9 == false);

    bool result10 = set.contains(62);
    assert(result10 == true);

    bool result11 = set.contains(18);
    assert(result11 == true);

    bool result12 = set.contains(28);
    assert(result12 == false);
}

void t4() {
    Set set;

    bool result = set.contains(2);
    assert(result == false);

    bool result2 = set.contains(12);
    assert(result2 == false);

    set.delete_element(10);
}

void t5() {
    Set set;
    set.insert(-2);
    set.insert(-2);
    assert(set.contains(-2));
    set.delete_element(-2);
    assert(!set.contains(-2));
    set.insert(-2);
    assert(set.contains(-2));

}


void test() {
    t1();
    t2();
    t3();
    t4();
    t5();
}

void input() {
    string operation;
    int value;
    Set set;


    while (cin >> operation) {
        cin >> value;

        if (operation == std::string("insert")) {

            set.insert(value);

        } else if (operation == std::string("delete")) {

            set.delete_element(value);

        } else {

            bool if_exist = set.contains(value);

            if (if_exist) {
                cout << "true" << std::endl;
            } else {
                cout << "false" << std::endl;
            }

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