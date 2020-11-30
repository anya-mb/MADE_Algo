/*
 * C. Topological sorting
time limit per test: 2 seconds
memory limit per test: 256 megabytes
input: standard input
output: standard output

You are given a directed graph. Find it's topological sorting.

Input
First line contains two integers 𝑛 and 𝑚 — number of vertices and edges in the graph, respectively (1 ≤ 𝑛 ≤ 100000, 𝑚 ≤ 100000).

Next 𝑚 lines describe edges of the graph. Each line contains two integers 𝑣 and 𝑢 — describing the edge starting at 𝑣 and ending at 𝑢 (1≤𝑣,𝑢≤𝑛; 𝑣≠𝑢).

Output
If no topological sorting exists, output -1.

Otherwise output the sequence of vertices which describes the topological ordering. If several orderings exist, output any.

Example

input
6 6
1 2
3 2
4 2
2 5
6 5
4 6

output
4 6 3 1 2 5

 */

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

int const NOT_VISITED_COLOR = 0;
int const CURRENT_COLOR = 1;
int const VISITED_BEFORE_COLOR = 2;

int const DEFAULT_TIME = 0;


bool has_cycle(int v, vector<int> &color_list,
               int color, vector<vector<int>> &graph) {

    color_list.at(v) = color;

    for (auto u : graph.at(v)) {
        if (color_list.at(u) == NOT_VISITED_COLOR) {
            has_cycle(u, color_list, color, graph);
        }
        if (color_list.at(u) == CURRENT_COLOR) {
            return true;
        }
    }

    color_list.at(v) = VISITED_BEFORE_COLOR;
    return false;
}

void topological_sort(int v, vector<bool> &used_list,
                      vector<int> &ans_list, vector<vector<int>> &graph) {

    used_list.at(v) = true;

    for (auto u : graph.at(v)) {
        if (used_list.at(u) == false) {
            topological_sort(u, used_list, ans_list, graph);
        }
    }
    ans_list.push_back(v);

}


void input() {

    int n, m, begin_v, end_v;

    cin >> n >> m;

    vector<vector<int>> graph;

    for (int i = 0; i < n; i++) {
        vector<int> g;

        graph.push_back(g);
    }

    for (int i = 0; i < m; i++) {
        cin >> begin_v >> end_v;
        begin_v--;
        end_v--;

        graph.at(begin_v).push_back(end_v);
        graph.at(end_v).push_back(begin_v);
    }

    vector<int> color_vector;
    vector<bool> used_vector;
    vector<int> tout_vector;

    for (int i = 0; i < n; i++) {
        color_vector.push_back(NOT_VISITED_COLOR);
        used_vector.push_back(false);
        tout_vector.push_back(DEFAULT_TIME);
    }

//    bool has_cycle_in_g = false;
//
//    for (int i = 0; i < color_vector.size(); i++) {
//
//        if (color_vector.at(i) == NOT_VISITED_COLOR) {
//
//            has_cycle_in_g = has_cycle(i, color_vector, CURRENT_COLOR, graph);
//        }
//    }
//
//    if (has_cycle_in_g) {
//        cout << -1;
//        return;
//    }


    vector<int> topological_sort_answer;

    for (int i = 0; i < n; i++) {

        if (!used_vector.at(i)) {

            topological_sort(i, used_vector, topological_sort_answer, graph);
        }
    }

    for (int i = topological_sort_answer.size() - 1; i >= 0; i--) {
        cout << topological_sort_answer.at(i) + 1 << " ";
    }

}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    input();

    return 0;
}




