/*
 * A. Простое двоичное дерево поиска
ограничение по времени на тест: 2 секунды
ограничение по памяти на тест: 512 мегабайт
ввод: стандартный ввод
вывод: стандартный вывод

Реализуйте просто двоичное дерево поиска.

Входные данные
Входной файл содержит описание операций с деревом, их количество не превышает 100. В каждой строке находится одна из следующих операций:

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
 *
 */

#include <iostream>
#include <vector>
#include <assert.h>

using std::cin;
using std::cout;
using std::vector;
using std::string;
using std::pair;

const int ELEMENT_EXISTS = 1;
const int ELEMENT_DOES_NOT_EXIST = -1;

class Node {

private:
    int key;
    Node* left;
    Node* right;

public:

    Node(int key_x) {
        key = key_x;
        left = nullptr;
        right = nullptr;
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




class Binary_Search_Tree {

public:

    Binary_Search_Tree() {
        root = nullptr;
    }

    virtual ~Binary_Search_Tree() {}

    void insert(int key_x) {
        if (exist(key_x)) {
            return;
        }
        root = insert_node(root, key_x);
    }

    void delete_element(int key_x) {
        if (!exist(key_x)) {
            return;
        }
        root = delete_node(root, key_x);
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

    Node* insert_node(Node* node, int key_to_insert) {

        if (node == nullptr) {
            return new Node(key_to_insert);

        } else if (node->getKey() < key_to_insert) {
            Node* new_right = insert_node(node->getRight(), key_to_insert);
            node->setRight(new_right);

        } else if (node->getKey() > key_to_insert) {
            Node* new_left = insert_node(node->getLeft(), key_to_insert);
            node->setLeft(new_left);
        }

        return node;
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

    Node* delete_current_node(Node* node) {
        Node* left_child = node->getLeft();
        Node* right_child = node->getRight();

        if ((left_child == nullptr) && (right_child == nullptr)) {
            delete node;
            node = nullptr;

        } else if (left_child == nullptr) {
            delete node;
            node = right_child;

        } else if (right_child == nullptr) {
            delete node;
            node = left_child;

        } else {

            Node* left_max_node = find_max(left_child);

            if (left_max_node == left_child) {
                delete node;
                node = left_child;
                node->setRight(right_child);

            } else {
                int max_key_left = left_max_node->getKey();
                node->setKey(max_key_left);
                left_child = delete_node(left_child, max_key_left);
            }
        }
        return node;
    }

    Node* delete_node(Node* node, int key_to_delete) {

        if (node == nullptr) {
            return nullptr;
        }

        Node* left_child = node->getLeft();
        Node* right_child = node->getRight();
        int node_key = node->getKey();

        if (node_key > key_to_delete) {

            Node* left_sub_tree_root = delete_node(left_child, key_to_delete);
            node->setLeft(left_sub_tree_root);

        } else if (node_key < key_to_delete) {

            Node* right_sub_tree_root = delete_node(right_child, key_to_delete);
            node->setRight(right_sub_tree_root);

        } else {
            node = delete_current_node(node);
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

    Binary_Search_Tree binarySearchTree;

    binarySearchTree.insert(2);
    binarySearchTree.insert(5);
    binarySearchTree.insert(3);

    bool result1 = binarySearchTree.exist(2);
    assert(result1 == true);

    bool result2 = binarySearchTree.exist(4);
    assert(result2 == false);

    pair <int, int> result3 = binarySearchTree.next(4);
    assert(result3.first == ELEMENT_EXISTS);
    assert(result3.second == 5);

    pair <int, int> result4 = binarySearchTree.prev(4);
    assert(result4.first == ELEMENT_EXISTS);
    assert(result4.second == 3);

    binarySearchTree.delete_element(5);

    pair <int, int> result5 = binarySearchTree.next(4);
    assert(result5.first == ELEMENT_DOES_NOT_EXIST);

    pair <int, int> result6 = binarySearchTree.prev(4);
    assert(result6.first == ELEMENT_EXISTS);
    assert(result6.second == 3);

}

void t1() {

    Binary_Search_Tree binarySearchTree;

    binarySearchTree.insert(6);
    binarySearchTree.insert(10);
    binarySearchTree.insert(2);
    binarySearchTree.insert(1);
    binarySearchTree.insert(0);

    binarySearchTree.delete_element(3);

    pair <int, int> result1 = binarySearchTree.prev(5);
    assert(result1.first == ELEMENT_EXISTS);
    assert(result1.second == 2);

    binarySearchTree.delete_element(6);
    binarySearchTree.delete_element(2);

    pair <int, int> result2 = binarySearchTree.prev(5);
    assert(result2.first == ELEMENT_EXISTS);
    assert(result2.second == 1);

    assert(binarySearchTree.exist(3) == false);
    assert(binarySearchTree.exist(2) == false);
    assert(binarySearchTree.exist(0) == true);

}

void t2() {

    Binary_Search_Tree binarySearchTree;

    binarySearchTree.insert(7);
    binarySearchTree.insert(3);
    binarySearchTree.insert(10);
    binarySearchTree.insert(9);
    binarySearchTree.insert(15);
    binarySearchTree.insert(1);
    binarySearchTree.insert(5);
    binarySearchTree.insert(0);
    binarySearchTree.insert(2);
    binarySearchTree.insert(4);
    binarySearchTree.insert(6);

    bool result1 = binarySearchTree.exist(2);
    assert(result1 == true);

    bool result2 = binarySearchTree.exist(14);
    assert(result2 == false);

    pair <int, int> result3 = binarySearchTree.next(5);
    assert(result3.first == ELEMENT_EXISTS);
    assert(result3.second == 6);

    pair <int, int> result4 = binarySearchTree.prev(5);
    assert(result4.first == ELEMENT_EXISTS);
    assert(result4.second == 4);

    binarySearchTree.insert(8);

    binarySearchTree.print_tree();

    pair <int, int> result4_1 = binarySearchTree.next(6);
    assert(result4_1.first == ELEMENT_EXISTS);
    assert(result4_1.second == 7);

    pair <int, int> result4_2 = binarySearchTree.prev(6);
    assert(result4_2.first == ELEMENT_EXISTS);
    assert(result4_2.second == 5);

    pair <int, int> result4_3 = binarySearchTree.next(7);
    assert(result4_3.first == ELEMENT_EXISTS);
    assert(result4_3.second == 8);

    pair <int, int> result4_4 = binarySearchTree.prev(7);
    assert(result4_4.first == ELEMENT_EXISTS);
    assert(result4_4.second == 6);

    binarySearchTree.delete_element(3);

    assert(binarySearchTree.exist(3) == false);
    assert(binarySearchTree.exist(4) == true);
    assert(binarySearchTree.exist(5) == true);
    assert(binarySearchTree.exist(2) == true);
    assert(binarySearchTree.exist(8) == true);

    pair <int, int> result5 = binarySearchTree.next(2);
    assert(result5.first == ELEMENT_EXISTS);
    assert(result5.second == 4);

    pair <int, int> result6 = binarySearchTree.prev(4);
    assert(result6.first == ELEMENT_EXISTS);
    assert(result6.second == 2);

    binarySearchTree.delete_element(3);
    binarySearchTree.delete_element(4);
    binarySearchTree.delete_element(5);
    binarySearchTree.delete_element(6);

    pair <int, int> result7 = binarySearchTree.prev(4);
    assert(result7.first == ELEMENT_EXISTS);
    assert(result7.second == 2);

    binarySearchTree.delete_element(2);

    pair <int, int> result8 = binarySearchTree.prev(4);
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

    Binary_Search_Tree binarySearchTree;

    while (cin >> operation) {
        cin >> x;

        if (operation == string("insert")) {
            binarySearchTree.insert(x);

        } else if (operation == string("delete")) {
            binarySearchTree.delete_element(x);

        } else if (operation == string("exists")) {
            bool result = binarySearchTree.exist(x);
            if (result) {
                cout << "true" << std::endl;
            } else {
                cout << "false" << std::endl;
            }

        } else if (operation == string("next")) {
            pair <int, int> result_next = binarySearchTree.next(x);
            print_value(result_next);

        } else if (operation == string("prev")) {
            pair <int, int> result_prev = binarySearchTree.prev(x);
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




