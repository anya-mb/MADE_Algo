/*
 * A. Disjoint-Sets
time limit per test: 2 seconds
memory limit per test: 256 megabytes
input: standard input
output: standard output

Your task is to maintain DSU. Moreover, you'll have to find minimum and maximum element and number of elements in the subset.

Initially, each element is in it's own subset.

Input
First line of input consists of a single integer n — number of elements in set (1 ≤ n ≤ 300 000).

Each of the next lines contains a single operation. For each of operation get, you should output minimum and maximum element and number of elements in corresponding subset.

Output
Output the sequence of results of operations get.

Example

input
5
union 1 2
get 3
get 2
union 2 3
get 2
union 1 3
get 5
union 4 5
get 5
union 4 1
get 5

output
3 3 1
1 2 2
1 3 3
5 5 1
4 5 2
1 5 5
 */

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

class Node {

public:
    Node(int root, int max, int min) : root(root), max(max), min(min) {}

    virtual ~Node() {

    }

    int getRoot() const {
        return root;
    }

    void setRoot(int root) {
        Node::root = root;
    }

    int getMax() const {
        return max;
    }

    void setMax(int max) {
        Node::max = max;
    }

    int getMin() const {
        return min;
    }

    void setMin(int min) {
        Node::min = min;
    }

private:
    int root;
    int max;
    int min;
};


class DisjointSet {

public:

    DisjointSet(int size_n) {

        for (int i = 0; i < size_n; i++) {

            Node* node = new Node(i, i, i);
            content.push_back(node);

            rangs.push_back(0);
        }
    }

    virtual ~DisjointSet() {

    }

    Node* get(int position_x) {

        Node* node_at_x = content.at(position_x);
        int node_at_x_root = node_at_x->getRoot();

        if (node_at_x_root != position_x) {

            int parent_root = get(node_at_x_root)->getRoot();
            node_at_x->setRoot(parent_root);
        }

        return node_at_x;
    }

    void join(int position_x, int position_y) {
        Node* x = get(position_x);
        Node* y = get(position_y);

        if (rangs.at(position_x) > rangs.at(position_y)) {
            swap(x, y);
        }

        if (rangs.at(position_x) == rangs.at(position_y)) {
            rangs.at(position_y)++;
        }

        hang(position_x, position_y);
    }


private:

    vector<Node*> content;
    vector<int> rangs;

    void swap(Node* x, Node* y) {
        Node* tmp_node = x;
        x = y;
        y = tmp_node;
    }

    void hang(int position_x, int position_y) {
        Node* x = get(position_x);
        Node* y = get(position_y);

        if (x->getMax() < y->getMax()) {

        }
    }

};

