/*
 * B. Неявный ключ
ограничение по времени на тест: 2 секунды
ограничение по памяти на тест: 256 мегабайт
ввод: стандартный ввод
вывод: стандартный вывод

Научитесь быстро делать две операции с массивом:  add i x — добавить после i-го элемента x (0 ≤ i ≤ n)  del i — удалить i-й элемент (1 ≤ i ≤ n)

Входные данные
На первой строке n0 и m (1 ≤ n_0, m ≤ 10^5) — длина исходного массива и количество запросов. На второй строке n0 целых чисел от 0 до 10^9 - 1 — исходный массив. Далее m строк, содержащие запросы. Гарантируется, что запросы корректны: например, если просят удалить i-й элемент, он точно есть.

Выходные данные
Выведите конечное состояние массива. На первой строке количество элементов, на второй строке сам массив.

Пример
входные данные
3 4
1 2 3
del 3
add 0 9
add 3 8
del 2

выходные данные
3
9 2 8
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

const int RANDOM_PRIORITY_MAX_VALUE = 20000000;

class Node {

private:
    int value;
    int priority;
    int size;
    Node* left;
    Node* right;

public:

    Node(int value_x, int priority_y) {
        value = value_x;
        priority = priority_y;
        size = 1;
        left = nullptr;
        right = nullptr;
    }

    int getSize() const {
        return size;
    }

    void setSize(int size) {
        Node::size = size;
    }

    int getPriority() const {
        return priority;
    }

    void setPriority(int priority) {
        Node::priority = priority;
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
        cout << value;
    }
};



class Treap {

public:

    Treap() {
        root = nullptr;
    }

    virtual ~Treap() {}

    void build(vector<int> array) {
        tree_size = 0;
        for (int i = 0; i < array.size(); i++) {
            add(i, array.at(i));
        }
    }

    void add(int key_x, int value) {
        key_x--;

        Node* new_node = new Node(value, get_random_priority());
        pair<Node*, Node*> result = split(root, key_x);

        Node* t1 = result.first;
        Node* t2 = result.second;

        t1 = merge(t1, new_node);
        root = merge(t1, t2);

        tree_size++;

    }

    void delete_element(int key_x) {
        key_x--;

        pair<Node*, Node*> result = split(root, key_x);
        Node* t1 = result.first;
        Node* t2 = result.second;

        pair<Node*, Node*> result_without_x = split(t1, key_x - 1);
        Node* t11 = result_without_x.first;

        Node* element = result_without_x.second;
        delete element;
        element = nullptr;

        root = merge(t11, t2);

        tree_size--;
    }

    void print_tree() {
        print_tree_nodes(root);
    }

    int getTreeSize() const {
        return tree_size;
    }

private:
    Node* root;

    int tree_size;

    void fix(Node* v) {
        int new_size = get_size(v->getLeft()) + get_size(v->getRight()) + 1;
        v->setSize(new_size);
    }

    int get_size(Node* node) {
        if (node == nullptr) {
            return 0;
        } else {
            return node->getSize();
        }
    }

    int get_random_priority() {
        return rand() % RANDOM_PRIORITY_MAX_VALUE;
    }

    pair<Node*, Node*> split(Node* v, int key_x) {
        if (v == nullptr) {
            return std::make_pair(nullptr, nullptr);
        }

        int v_left_size = get_size(v->getLeft());

        if (v_left_size > key_x) {

            pair<Node*, Node*> result = split(v->getLeft(), key_x);
            Node* t1 = result.first;
            Node* t2 = result.second;

            v->setLeft(t2);
            fix(v);

            return std::make_pair(t1, v);

        } else {

            pair<Node*, Node*> result = split(v->getRight(), key_x - v_left_size - 1);
            Node* t1 = result.first;
            Node* t2 = result.second;

            v->setRight(t1);
            fix(v);

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
            fix(t1);
            return t1;

        } else {
            Node* merged = merge(t1, t2->getLeft());
            t2->setLeft(merged);
            fix(t2);
            return t2;
        }
    }

    void print_tree_nodes(Node* node) {
        if (node != nullptr) {
            print_tree_nodes(node->getLeft());

            node->print();
            cout << " ";

            print_tree_nodes(node->getRight());
        }
    }
};


void test() {

    Treap tree;
    vector<int> initial_array = {1, 2, 3};

    tree.build(initial_array);

    cout << "Built: " << std::endl;
    tree.print_tree();
    cout << std::endl;

    tree.delete_element(3);
    cout << "delete_element(3): " << std::endl;
    tree.print_tree();
    cout << std::endl;

    tree.add(0, 9);
    cout << "add(0, 9): " << std::endl;
    tree.print_tree();
    cout << std::endl;

    tree.add(3, 8);
    cout << "add(3, 8): " << std::endl;
    tree.print_tree();
    cout << std::endl;

    tree.delete_element(2);
    cout << "delete_element(2): " << std::endl;
    tree.print_tree();
    cout << std::endl;

    cout << std::endl;
    cout << "Final: " << std::endl;
    cout << tree.getTreeSize() << std::endl;
    tree.print_tree();
}


void input() {

    string operation;
    int n_0, m, value, idx, x;

    Treap tree;

    cin >> n_0 >> m;
    vector<int> initial_array;

    for (int i = 0; i < n_0; i++) {
        cin >> value;
        initial_array.push_back(value);
    }

    tree.build(initial_array);

    for (int i = 0; i < m; i++) {
        cin >> operation;

        if (operation == string("del")) {
            cin >> idx;
            tree.delete_element(idx);

        } else if (operation == string("add")) {
            cin >> idx >> x;
            tree.add(idx, x);

        } else {
            throw;
        }
    }

    cout << tree.getTreeSize() << std::endl;
    tree.print_tree();
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    input();

//    test();

    return 0;
}


