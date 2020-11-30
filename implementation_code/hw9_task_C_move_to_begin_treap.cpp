/*
 * C. Переместить в начало
ограничение по времени на тест: 6 секунд
ограничение по памяти на тест: 512 мегабайт
ввод: стандартный ввод
вывод: стандартный вывод

Вам дан массив a_1 = 1, a_2 = 2, ..., a_n = n и последовальность операций: переместить элементы с l_i по r_i в начало массива. Например, для массива 2, 3, 6, 1, 5, 4, после операции (2, 4) новый порядок будет 3, 6, 1, 2, 5, 4. А после применения операции (3, 4) порядок элементов в массиве будет 1, 2, 3, 6, 5, 4.

Выведите порядок элементов в массиве после выполнения всех операций.

Входные данные
В первой строке входного файла указаны числа n и m (2 ≤ n ≤ 100,000, 1 ≤ m ≤ 100,000) — число элементов в массиве и число операций. Следующие m строк содержат операции в виде двух целых чисел: l_i и r_i (1 ≤ l_i ≤ r_i ≤ n).

Выходные данные
Выведите n целых чисел — порядок элементов в массиве после применения всех операций.

Пример
входные данные
6 3
2 4
3 5
2 2

выходные данные
1 4 5 2 3 6
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

    void move_to_beginning(int l, int r) {
        r = r - l;
        l -= 2;

        pair<Node*, Node*> result_split_1 = split(root, l);
        Node* t1 = result_split_1.first;
        Node* t2 = result_split_1.second;

        pair<Node*, Node*> result_split_2 = split(t2, r);
        Node* t21 = result_split_2.first;
        Node* t22 = result_split_2.second;

        root = merge(t21, t1);
        root = merge(root, t22);
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


void t0() {

    Treap tree;
    vector<int> initial_array = {1, 2, 3, 4, 5, 6};

    tree.build(initial_array);

    cout << "Built: " << std::endl;
    tree.print_tree();
    cout << std::endl;

    tree.move_to_beginning(2, 4);
    tree.move_to_beginning(3, 5);
    tree.move_to_beginning(2, 2);

    cout << "should be 1 4 5 2 3 6 " << std::endl;
    tree.print_tree();
    cout << std::endl;
}

void t1() {

    Treap tree;
    vector<int> initial_array = {2, 3, 6, 1, 5, 4};

    tree.build(initial_array);

    cout << "Built: " << std::endl;
    tree.print_tree();
    cout << std::endl;

    tree.move_to_beginning(2, 4);
    cout << "move_to_beginning(2, 4): should be 3,6,1,2,5,4" << std::endl;
    tree.print_tree();
    cout << std::endl;

    tree.move_to_beginning(3, 4);
    cout << "move_to_beginning(3, 4): should be 1,2,3,6,5,4" << std::endl;
    tree.print_tree();
    cout << std::endl;
}

void test() {
    t0();
    t1();
}


void input() {

    int n, m, l, r;

    Treap tree;

    cin >> n >> m;
    vector<int> initial_array;

    for (int i = 1; i < n + 1; i++) {
        initial_array.push_back(i);
    }

    tree.build(initial_array);

    for (int i = 0; i < m; i++) {
        cin >> l >> r;
        tree.move_to_beginning(l, r);
    }

    tree.print_tree();
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    input();

//    test();

    return 0;
}


