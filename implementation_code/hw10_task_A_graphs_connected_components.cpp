/*
 * A. Connected components
time limit per test: 2 seconds
memory limit per test: 256 megabytes
input: standard input
output: standard output

Given an undirected graph. Your task is to find connected components in it.

Input
The first line of the input file contains two integers 𝑛 and 𝑚, the number of vertices and edges of the graph, respectively (1 ≤ 𝑛 ≤ 100000, 0 ≤ 𝑚 ≤ 200000).

The following 𝑚 lines contain descriptions of edges one per line. Edge number 𝑖 is described by two integers 𝑏_𝑖, 𝑒_𝑖, numbers of edge ends (1 ≤ 𝑏_𝑖, 𝑒_𝑖 ≤ 𝑛). Loops and parallel edges are allowed.

Output
In the first line of the output file output an integer 𝑘, the number of connected components in the graph.

In the second line output 𝑛 numbers 𝑎_1, 𝑎_2, …, 𝑎_𝑛 from 1 to 𝑘, where 𝑎_𝑖 is the number of the connected component the 𝑖-th vertex belongs to.

Examples

input
3 1
1 2
output
2
1 1 2

input
4 2
1 3
2 4
output
2
1 2 1 2

 */

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

int const DEFAULT_COLOR = 0;

void mark_connected_components(int v, vector<int> &color_list,
                               int cur_color, vector<vector<int>> &graph) {

    color_list.at(v) = cur_color;

    for (auto u : graph.at(v)) {
        if (color_list.at(u) == DEFAULT_COLOR) {
            mark_connected_components(u, color_list, cur_color, graph);
        }
    }
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

    for (int i = 0; i < n; i++) {
        color_vector.push_back(DEFAULT_COLOR);
    }


    int number_of_components = 0;

    for (int i = 0; i < color_vector.size(); i++) {

        if (color_vector.at(i) == DEFAULT_COLOR) {

            number_of_components++;
            mark_connected_components(i, color_vector, number_of_components, graph);
        }
    }

    cout << number_of_components << std::endl;

    for (int i = 0; i < color_vector.size(); i++) {
        cout << color_vector.at(i) << " ";
    }

}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    input();

    return 0;
}




