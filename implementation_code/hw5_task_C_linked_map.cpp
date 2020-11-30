/*
 * C. LinkedMap
ограничение по времени на тест: 2 секунды
ограничение по памяти на тест: 256 мегабайт
ввод: стандартный ввод
вывод: стандартный вывод

Реализуйте прошитый ассоциативный массив с использованием хеш таблицы.

Входные данные
Входной файл содержит описание операций, их количество не превышает 100000. В каждой строке находится одна из следующих операций:

put 𝑥 𝑦 — поставить в соответствие ключу 𝑥 значение 𝑦. Если элемент уже есть, то значение необходимо изменить.
delete 𝑥 — удалить ключ 𝑥. Если элемента 𝑥 нет, то ничего делать не надо.
get 𝑥 — если ключ 𝑥 есть в множестве выведите соответствующее ему значение, если нет выведите «none».
prev 𝑥 — вывести значение соответствующее ключу находящемуся в ассоциативном массиве, который был вставлен позже всех, но до 𝑥 или «none», если такого нет или в массиве нет 𝑥.
next 𝑥 — вывести значение соответствующее ключу находящемуся в ассоциативном массиве, который был вставлен раньше всех, но после 𝑥 или «none», если такого нет или в массиве нет 𝑥.

 Ключи и значения — строки из латинских букв длинной не более 20 символов.

Выходные данные
Выведите последовательно результат выполнения всех операций get, prev, next. Следуйте формату выходного файла из примера.

Пример
входные данные
put zero a
put one b
put two c
put three d
put four e
get two
prev two
next two
delete one
delete three
get two
prev two
next two
next four

выходные данные
c
b
d
c
a
e
none

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
    Entity(string new_key, string new_value, Entity* previous_entity) {
        key = new_key;
        value = new_value;
        next_added = nullptr;
        prev_added = previous_entity;
        next_entity_same_hash = nullptr;
        prev_entity_same_hash = nullptr;
        status = OCCUPIED_STATUS;
    }

    Entity(string new_key, string new_value) {
        key = new_key;
        value = new_value;
        next_added = nullptr;
        prev_added = nullptr;
        next_entity_same_hash = nullptr;
        prev_entity_same_hash = nullptr;
        status = OCCUPIED_STATUS;
    }

    Entity() {
        next_added = nullptr;
        prev_added = nullptr;
        next_entity_same_hash = nullptr;
        prev_entity_same_hash = nullptr;
        status = NOT_OCCUPIED_STATUS;
    }

    string get_value() {
        return value;
    }

    void set_value(string new_value) {
        value = new_value;
    }

    string get_key() {
        return key;
    }

    bool has_next_added() {
        return next_added != nullptr;
    }
    Entity* get_next_added() {
        return next_added;
    }
    void set_next_added(Entity* new_entity) {
        next_added = new_entity;
    }


    bool has_prev_added() {
        return prev_added != nullptr;
    }
    Entity* get_prev_added() {
        return prev_added;
    }
    void set_prev_added(Entity* new_entity) {
        prev_added = new_entity;
    }


    bool has_next_entity_same_hash() {
        return next_entity_same_hash != nullptr;
    }
    Entity* get_next_entity_same_hash() {
        return next_entity_same_hash;
    }
    void set_next_entity_same_hash(Entity* new_entity) {
        next_entity_same_hash = new_entity;
    }


    bool has_prev_entity_same_hash() {
        return prev_entity_same_hash != nullptr;
    }
    Entity* get_prev_entity_same_hash() {
        return prev_entity_same_hash;
    }
    void set_prev_entity_same_hash(Entity* new_entity) {
        prev_entity_same_hash = new_entity;
    }


    bool is_occupied() {
        return status == OCCUPIED_STATUS;
    }

private:
    string value;
    string key;
    Entity* next_added;
    Entity* prev_added;
    Entity* next_entity_same_hash;
    Entity* prev_entity_same_hash;

    int status;
    static const int NOT_OCCUPIED_STATUS = 0;
    static const int OCCUPIED_STATUS = 1;
};

class LinkedMap {
public:

    LinkedMap();
    virtual ~LinkedMap();

    void put(string key, string value);
    void delete_element(string key);
    string get(string key);
    string prev(string key);
    string next(string key);

private:

    vector <Entity *> elements;
    int size = 0;

    Entity* previously_added_entity = nullptr;

    static const int MAX_NUMBER_OF_ELEMENTS = 200000;
    static const int PRIME_FOR_HASH = 4000081;
    static const int MULTIPLIER_FOR_HASH = 11;

    int calculate_position(string initial_string);

    static const int NO_KEY_FOUND = -1;
    int find_element_position(string key);

    static const string inline ELEMENT_DOES_NOT_EXIST = string("none");

    Entity* get_entity(string key);

    string get_value_wrapper(Entity* current_entity);
};


LinkedMap::LinkedMap() {

    for (int i = 0; i < MAX_NUMBER_OF_ELEMENTS; i++) {
        Entity* entity = new Entity();
        elements.push_back(entity);
    }
}

LinkedMap::~LinkedMap() {
}

int LinkedMap::calculate_position(string initial_string) {
    int result = 0;

    for (char letter : initial_string) {
        int new_x = letter % PRIME_FOR_HASH;
        result = (result * MULTIPLIER_FOR_HASH + new_x) % PRIME_FOR_HASH;

    }

    result %= MAX_NUMBER_OF_ELEMENTS;

    return result;
}

void LinkedMap::put(string key, string value) {
    int existing_position = find_element_position(key);

    if (existing_position < 0) {
        // add new element
        Entity* new_entity;

        if (size == 0) {
            new_entity = new Entity(key, value);

        } else {
            new_entity = new Entity(key, value, previously_added_entity);
            previously_added_entity->set_next_added(new_entity);
        }

        int position_by_hash = calculate_position(key);
        Entity* previous_entity_at_position = elements.at(position_by_hash);

        if (previous_entity_at_position->is_occupied()) {
            // if collision

            // move to the last entity in linked list
            while (previous_entity_at_position->has_next_entity_same_hash()) {
                previous_entity_at_position = previous_entity_at_position->get_next_entity_same_hash();
            }

            previous_entity_at_position->set_next_entity_same_hash(new_entity);
            new_entity->set_prev_entity_same_hash(previous_entity_at_position);

        } else {
            // first node on linked list for this hash position

            elements.at(position_by_hash) = new_entity;

        }

        previously_added_entity = new_entity;
        size++;

    } else {
        // change value of existing key
        Entity* existing_entity = elements.at(existing_position);

        while (existing_entity->has_next_entity_same_hash()
               || existing_entity->get_key() == key) {

            if (existing_entity->get_key() == key) {
                existing_entity->set_value(value);
                break;

            } else {
                existing_entity = existing_entity->get_next_entity_same_hash();
            }
        }
    }
}

int LinkedMap::find_element_position(string key) {

    if (size == 0) {
        return NO_KEY_FOUND;
    }

    int position = calculate_position(key);

    Entity* entity = elements.at(position);

    if (entity == nullptr) {
        Entity* clean_entity = new Entity();
        entity = clean_entity;

        return NO_KEY_FOUND;
    }

    if (!entity->is_occupied()) {
        return NO_KEY_FOUND;

    } else {

        while (entity->has_next_entity_same_hash()
               || entity->get_key() == key) {

            if (entity->get_key() == key) {
                return position;

            } else {
                entity = entity->get_next_entity_same_hash();
            }
        }

        return NO_KEY_FOUND;
    }
}

void LinkedMap::delete_element(string key) {
    int existing_position = find_element_position(key);

    if (existing_position >= 0) {
        // element exists at position
        Entity* existing_entity = elements.at(existing_position);

        // iterate in linked list of positions with the same hashes
        // to find our entity with right key
        if (existing_entity->get_key() != key) {
            while (existing_entity->has_next_entity_same_hash()) {
                if (existing_entity->get_key() == key) {
                    break;

                } else {
                    existing_entity = existing_entity->get_next_entity_same_hash();
                }
            }
        }

        // fixing links for next_existing and previous_existing in added order
        if (existing_entity->has_prev_added()) {
            // not the first added to map
            Entity* previous_existing_entity = existing_entity->get_prev_added();

            if (existing_entity->has_next_added()) {

                Entity* next_existing_entity = existing_entity->get_next_added();

                next_existing_entity->set_prev_added(previous_existing_entity);
                previous_existing_entity->set_next_added(next_existing_entity);

            } else {

                previously_added_entity = previous_existing_entity;
                previous_existing_entity->set_next_added(nullptr);
            }

        } else {
            // the first added to map
            if (existing_entity->has_next_added()) {

                Entity* next_existing_entity = existing_entity->get_next_added();
                next_existing_entity->set_prev_added(nullptr);

            } else {

                // the only one element in map
                Entity* clean_entity = new Entity();
                existing_entity = clean_entity;
                previously_added_entity = nullptr;
            }
        }



        // fixing links for collisions
        if (!existing_entity->has_prev_entity_same_hash()) {
            // if this is head

            if (existing_entity->has_next_entity_same_hash()) {

                Entity* next_entity_same_hash = existing_entity->get_next_entity_same_hash();
                next_entity_same_hash->set_prev_entity_same_hash(nullptr);
                elements.at(existing_position) = next_entity_same_hash;

            } else {
                // if first and the only element
                Entity* clean_entity = new Entity();
                elements.at(existing_position) = clean_entity;

            }
        } else {
            // if not head

            Entity* prev_entity_same_hash = existing_entity->get_prev_entity_same_hash();

            if (existing_entity->has_next_entity_same_hash()) {

                Entity* next_entity_same_hash = existing_entity->get_next_entity_same_hash();
                next_entity_same_hash->set_prev_entity_same_hash(prev_entity_same_hash);
                prev_entity_same_hash->set_next_entity_same_hash(next_entity_same_hash);

            } else {

                prev_entity_same_hash->set_next_entity_same_hash(nullptr);
            }
        }

        // links are fixed, can finally delete element
        delete existing_entity;
        size--;
    }
}

Entity *LinkedMap::get_entity(string key) {
    int existing_position = find_element_position(key);

    if (existing_position < 0) {
        // entity does not exist
        return nullptr;
    }

    Entity* current_entity = elements.at(existing_position);

    if (current_entity == nullptr) {
        Entity* clean_entity = new Entity();
        current_entity = clean_entity;
        return nullptr;
    }

    if (!current_entity->is_occupied()) {
        return nullptr;
    }

    if (current_entity->get_key() == key) {
        return current_entity;
    }

    // search for this key in linked list
    if (!current_entity->has_next_entity_same_hash()) {
        throw;
    }
    while (current_entity->has_next_entity_same_hash()) {

        current_entity = current_entity->get_next_entity_same_hash();

        if (current_entity->get_key() == key) {
            return current_entity;
        }
    }
}

string LinkedMap::get_value_wrapper(Entity *current_entity) {
    if (current_entity == nullptr ) {
        return ELEMENT_DOES_NOT_EXIST;

    } else if (!current_entity->is_occupied()) {
        return ELEMENT_DOES_NOT_EXIST;

    } else {

        return current_entity->get_value();
    }
}

string LinkedMap::get(string key) {
    Entity* current_entity = get_entity(key);
    return get_value_wrapper(current_entity);
}

string LinkedMap::prev(string key) {
    Entity* current_entity = get_entity(key);

    if (current_entity == nullptr) {
        return ELEMENT_DOES_NOT_EXIST;

    }

    Entity* prev_entity = current_entity->get_prev_added();
    return get_value_wrapper(prev_entity);
}

string LinkedMap::next(string key) {
    Entity* current_entity = get_entity(key);

    if (current_entity == nullptr) {
        return ELEMENT_DOES_NOT_EXIST;
    }

    Entity* next_entity = current_entity->get_next_added();
    return get_value_wrapper(next_entity);
}





void t1() {
    LinkedMap linked_map;

    linked_map.put("zero", "a");
    linked_map.put("one", "b");
    linked_map.put("two", "c");
    linked_map.put("three", "d");
    linked_map.put("four", "e");

    string result1 = linked_map.get("two");
    assert(result1 == "c");
    string result2 = linked_map.prev("two");
    assert(result2 == "b");
    string result3 = linked_map.next("two");
    assert(result3 == "d");

    linked_map.delete_element("one");
    linked_map.delete_element("three");

    string result4 = linked_map.get("two");
    assert(result4 == "c");
    string result5 = linked_map.prev("two");
    assert(result5 == "a");
    string result6 = linked_map.next("two");
    assert(result6 == "e");

    string result7 = linked_map.next("four");
    assert(result7 == "none");
}

void t2() {
    LinkedMap linked_map;

    linked_map.put("hello", "privet");
    linked_map.put("bye", "poka");

    string result1 = linked_map.get("hello");
    assert(result1 == "privet");
    string result2 = linked_map.get("bye");
    assert(result2 == "poka");

    linked_map.delete_element("hello");

    string result4 = linked_map.get("hello");
    assert(result4 == "none");

}

void t3() {
    LinkedMap linked_map;

    linked_map.put("hello", "privet");
    linked_map.put("bye", "poka");

    string result1 = linked_map.get("hello");
    assert(result1 == "privet");
    string result2 = linked_map.get("bye");
    assert(result2 == "poka");

    linked_map.delete_element("hello");

    string result3 = linked_map.get("hello");
    assert(result3 == "none");

    linked_map.delete_element("hello");

    string result4 = linked_map.get("hello");
    assert(result4 == "none");

    linked_map.delete_element("bye");

    string result5 = linked_map.get("bye");
    assert(result5 == "none");

    linked_map.delete_element("wow");
    string result6 = linked_map.get("wow");
    assert(result6 == "none");
}

void t4() {
    LinkedMap linked_map;

    linked_map.put("hello", "privet");
    linked_map.put("bye", "poka");

    string result1 = linked_map.get("hello");
    assert(result1 == "privet");
    string result2 = linked_map.get("bye");
    assert(result2 == "poka");

    linked_map.delete_element("bye");

    string result3 = linked_map.get("bye");
    assert(result3 == "none");

    linked_map.put("wow", "wow");
    string result4 = linked_map.get("wow");
    assert(result4 == "wow");

    string result5 = linked_map.prev("wow");
    assert(result5 == "privet");

    string result6 = linked_map.next("hello");
    assert(result6 == "wow");

    linked_map.delete_element("wow");
    string result7 = linked_map.next("wow");
    assert(result7 == "none");

    string result8 = linked_map.next("hello");
    assert(result8 == "none");
}

void t5() {
    LinkedMap linked_map;

    linked_map.put("hello", "privet");
    linked_map.put("bye", "poka");
    linked_map.put("three", "privet3");
    linked_map.put("four", "poka4");
    linked_map.put("five", "privet5");
    linked_map.put("six", "poka6");

    string result1 = linked_map.get("hello");
    assert(result1 == "privet");
    string result2 = linked_map.get("bye");
    assert(result2 == "poka");

    linked_map.delete_element("bye");

    string result3 = linked_map.get("bye");
    assert(result3 == "none");

    linked_map.put("wow", "wow_val");
    string result4 = linked_map.get("wow");
    assert(result4 == "wow_val");

    string result5 = linked_map.prev("wow");
    assert(result5 == "poka6");

    string result6 = linked_map.next("hello");
    assert(result6 == "privet3");

    linked_map.delete_element("wow");
    string result7 = linked_map.next("wow");
    assert(result7 == "none");

    linked_map.delete_element("three");
    string result8 = linked_map.next("hello");
    assert(result8 == "poka4");
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
    string key, value;
    LinkedMap linked_map;

    while (cin >> operation) {

        if (operation == std::string("put")) {
            cin >> key >> value;
            linked_map.put(key, value);

        } else if (operation == std::string("delete")) {
            cin >> key;
            linked_map.delete_element(key);

        } else if (operation == std::string("get")){
            cin >> key;
            cout << linked_map.get(key) << std::endl;

        } else if (operation == std::string("prev")){
            cin >> key;
            cout << linked_map.prev(key) << std::endl;

        } else if (operation == std::string("next")){
            cin >> key;
            cout << linked_map.next(key) << std::endl;

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