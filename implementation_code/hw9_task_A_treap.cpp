/*
 * A. Сбалансированное двоичное дерево поиска
ограничение по времени на тест: 2 секунды
ограничение по памяти на тест: 512 мегабайт
ввод: стандартный ввод
вывод: стандартный вывод

Реализуйте сбалансированное двоичное дерево поиска.

Входные данные
Входной файл содержит описание операций с деревом, их количество не превышает 10^5. В каждой строке находится одна из следующих операций:

insert 𝑥 — добавить в дерево ключ 𝑥. Если ключ 𝑥 есть в дереве, то ничего делать не надо;
delete 𝑥 — удалить из дерева ключ 𝑥. Если ключа 𝑥 в дереве нет, то ничего делать не надо;
exists 𝑥 — если ключ 𝑥 есть в дереве выведите «true», если нет «false»;
next 𝑥 — выведите минимальный элемент в дереве, строго больший 𝑥, или «none» если такого нет;
prev 𝑥 — выведите максимальный элемент в дереве, строго меньший 𝑥, или «none» если такого нет.

В дерево помещаются и извлекаются только целые числа, не превышающие по модулю 10^9.

Выходные данные
Выведите последовательно результат выполнения всех операций exists, next, prev. Следуйте формату выходного файла из примера.

Пример
входные данные
insert 2
insert 5
insert 3
exists 2
exists 4
next 4
prev 4
delete 5
next 4
prev 4

выходные данные
true
false
5
3
none
3
 */

#include <iostream>
#include <vector>
#include <assert.h>
#include <cstdlib>

using std::cin;
using std::cout;
using std::vector;
using std::string;
using std::pair;

const int ELEMENT_EXISTS = 1;
const int ELEMENT_DOES_NOT_EXIST = -1;

const int RANDOM_PRIORITY_MAX_VALUE = 20000000;

class Node {

private:
    int key;
    int priority;
    Node* left;
    Node* right;

public:

    Node(int key_x, int priority_y) {
        key = key_x;
        priority = priority_y;
        left = nullptr;
        right = nullptr;
    }

    int getPriority() const {
        return priority;
    }

    void setPriority(int priority) {
        Node::priority = priority;
    }
    int getKey() const {
        return key;
    }

    void setKey(int key) {
        Node::key = key;
    }

    Node *getLeft() const {
        return left;
    }

    void setLeft(Node *left) {
        Node::left = left;
    }

    Node *getRight() const {
        return right;
    }

    void setRight(Node *right) {
        Node::right = right;
    }

    void print() {
        cout << key;
    }

};



class Treap {

public:

    Treap() {
        root = nullptr;
    }

    virtual ~Treap() {}

    void insert(int key_x) {

        if (exist(key_x)) {
            return;
        }

        Node* new_node = new Node(key_x, get_random_priority());
        pair<Node*, Node*> result = split(root, key_x);

        Node* t1 = result.first;
        Node* t2 = result.second;

        t1 = merge(t1, new_node);
        root = merge(t1, t2);

    }

    void delete_element(int key_x) {
        if (!exist(key_x)) {
            return;
        }

        pair<Node*, Node*> result = split(root, key_x);
        Node* t1 = result.first;
        Node* t2 = result.second;

        pair<Node*, Node*> result_without_x = split(t1, key_x - 1);
        Node* t11 = result_without_x.first;

        Node* element = result_without_x.second;
        delete element;
        element = nullptr;

        root = merge(t11, t2);
    }

    bool exist(int key_x) {
        return search_node(root, key_x) != nullptr;
    }

    pair <int, int> next(int key_x) {
        Node* node = root;
        Node* result = nullptr;

        while (node != nullptr) {

            if (node->getKey() > key_x) {
                result = node;
                node = node->getLeft();

            } else {
                node = node->getRight();
            }
        }

        return wrap_result(result);
    }

    pair <int, int> prev(int key_x) {
        Node* node = root;
        Node* result = nullptr;

        while (node != nullptr) {

            if (node->getKey() >= key_x) {
                node = node->getLeft();

            } else {
                result = node;
                node = node->getRight();
            }
        }

        return wrap_result(result);
    }


    void print_tree() {
        print_tree_nodes(root, 1);
    }


private:
    Node* root;

    int get_random_priority() {
        return rand() % RANDOM_PRIORITY_MAX_VALUE;
    }

    pair<Node*, Node*> split(Node* v, int key_x) {
        if (v == nullptr) {
            return std::make_pair(nullptr, nullptr);
        }

        if (v->getKey() > key_x) {

            pair<Node*, Node*> result = split(v->getLeft(), key_x);
            Node* t1 = result.first;
            Node* t2 = result.second;

            v->setLeft(t2);

            return std::make_pair(t1, v);

        } else {

            pair<Node*, Node*> result = split(v->getRight(), key_x);
            Node* t1 = result.first;
            Node* t2 = result.second;

            v->setRight(t1);

            return std::make_pair(v, t2);
        }
    }

    Node* merge(Node* t1, Node* t2) {
        if (t1 == nullptr) {
            return t2;
        }
        if (t2 == nullptr) {
            return t1;
        }

        if (t1->getPriority() > t2->getPriority()) {
            Node* merged = merge(t1->getRight(), t2);
            t1->setRight(merged);
            return t1;

        } else {
            Node* merged = merge(t1, t2->getLeft());
            t2->setLeft(merged);
            return t2;
        }
    }

    Node* search_node(Node* from_node, int key_to_find) {
        if (from_node == nullptr) {
            return nullptr;
        }

        int node_key = from_node->getKey();

        if (node_key == key_to_find) {
            return from_node;

        } else if (node_key < key_to_find) {
            return search_node(from_node->getRight(), key_to_find);

        } else {
            return search_node(from_node->getLeft(), key_to_find);
        }
    }


    Node* find_max(Node* node) {
        if (node == nullptr) {
            throw;
        }

        while (node->getRight() != nullptr) {
            node = node->getRight();
        }
        return node;
    }


    void print_tree_nodes(Node* node, int intend) {
        if (node != nullptr) {
            print_tree_nodes(node->getLeft(), intend + 2);

            cout << std::endl;
            for (int i = 0; i < intend; i++) {
                cout << " ";
            }
            node->print();

            print_tree_nodes(node->getRight(), intend + 2);
        }
    }

    pair <int, int> wrap_result(Node* result) {
        if (result == nullptr) {
            return std::make_pair(ELEMENT_DOES_NOT_EXIST, 0);

        } else {
            return std::make_pair(ELEMENT_EXISTS, result->getKey());
        }
    }

};


void t0() {

    Treap tree;

    tree.insert(2);
    tree.insert(5);
    tree.insert(3);

    bool result1 = tree.exist(2);
    assert(result1 == true);

    bool result2 = tree.exist(4);
    assert(result2 == false);

    pair <int, int> result3 = tree.next(4);
    assert(result3.first == ELEMENT_EXISTS);
    assert(result3.second == 5);

    pair <int, int> result4 = tree.prev(4);
    assert(result4.first == ELEMENT_EXISTS);
    assert(result4.second == 3);

    tree.delete_element(5);

    pair <int, int> result5 = tree.next(4);
    assert(result5.first == ELEMENT_DOES_NOT_EXIST);

    pair <int, int> result6 = tree.prev(4);
    assert(result6.first == ELEMENT_EXISTS);
    assert(result6.second == 3);

}

void t1() {

    Treap tree;

    tree.insert(6);
    tree.insert(10);
    tree.insert(2);
    tree.insert(1);
    tree.insert(0);

    tree.delete_element(3);

    pair <int, int> result1 = tree.prev(5);
    assert(result1.first == ELEMENT_EXISTS);
    assert(result1.second == 2);

    tree.delete_element(6);
    tree.delete_element(2);

    pair <int, int> result2 = tree.prev(5);
    assert(result2.first == ELEMENT_EXISTS);
    assert(result2.second == 1);

    assert(tree.exist(3) == false);
    assert(tree.exist(2) == false);
    assert(tree.exist(0) == true);

}

void t2() {

    Treap tree;

    tree.insert(7);
    tree.insert(3);
    tree.insert(10);
    tree.insert(9);
    tree.insert(15);
    tree.insert(1);
    tree.insert(5);
    tree.insert(0);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);

    bool result1 = tree.exist(2);
    assert(result1 == true);

    bool result2 = tree.exist(14);
    assert(result2 == false);

    pair <int, int> result3 = tree.next(5);
    assert(result3.first == ELEMENT_EXISTS);
    assert(result3.second == 6);

    pair <int, int> result4 = tree.prev(5);
    assert(result4.first == ELEMENT_EXISTS);
    assert(result4.second == 4);

    tree.insert(8);

    tree.print_tree();

    pair <int, int> result4_1 = tree.next(6);
    assert(result4_1.first == ELEMENT_EXISTS);
    assert(result4_1.second == 7);

    pair <int, int> result4_2 = tree.prev(6);
    assert(result4_2.first == ELEMENT_EXISTS);
    assert(result4_2.second == 5);

    pair <int, int> result4_3 = tree.next(7);
    assert(result4_3.first == ELEMENT_EXISTS);
    assert(result4_3.second == 8);

    pair <int, int> result4_4 = tree.prev(7);
    assert(result4_4.first == ELEMENT_EXISTS);
    assert(result4_4.second == 6);

    tree.delete_element(3);

    assert(tree.exist(3) == false);
    assert(tree.exist(4) == true);
    assert(tree.exist(5) == true);
    assert(tree.exist(2) == true);
    assert(tree.exist(8) == true);

    pair <int, int> result5 = tree.next(2);
    assert(result5.first == ELEMENT_EXISTS);
    assert(result5.second == 4);

    pair <int, int> result6 = tree.prev(4);
    assert(result6.first == ELEMENT_EXISTS);
    assert(result6.second == 2);

    tree.delete_element(3);
    tree.delete_element(4);
    tree.delete_element(5);
    tree.delete_element(6);

    pair <int, int> result7 = tree.prev(4);
    assert(result7.first == ELEMENT_EXISTS);
    assert(result7.second == 2);

    tree.delete_element(2);

    pair <int, int> result8 = tree.prev(4);
    assert(result8.first == ELEMENT_EXISTS);
    assert(result8.second == 1);

}


void test() {
    t0();
    t1();
    t2();
}

void print_value(pair <int, int> result) {
    if (result.first == ELEMENT_EXISTS) {
        cout << result.second << std::endl;
    } else {
        cout << "none" << std::endl;
    }
}

void input() {

    string operation;
    int x;

    Treap tree;

    while (cin >> operation) {
        cin >> x;

        if (operation == string("insert")) {
            tree.insert(x);

        } else if (operation == string("delete")) {
            tree.delete_element(x);

        } else if (operation == string("exists")) {
            bool result = tree.exist(x);
            if (result) {
                cout << "true" << std::endl;
            } else {
                cout << "false" << std::endl;
            }

        } else if (operation == string("next")) {
            pair <int, int> result_next = tree.next(x);
            print_value(result_next);

        } else if (operation == string("prev")) {
            pair <int, int> result_prev = tree.prev(x);
            print_value(result_prev);

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




