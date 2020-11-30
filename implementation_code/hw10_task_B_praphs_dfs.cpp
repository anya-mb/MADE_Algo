/*
 * B. Reposts
time limit per test: 1 second
memory limit per test: 256 megabytes
input: standard input
output: standard output

One day Polycarp published a funny picture in a social network making a poll about the color of his handle. Many of his friends started reposting Polycarp's joke to their news feed. Some of them reposted the reposts and so on.

These events are given as a sequence of strings "name1 reposted name2", where name1 is the name of the person who reposted the joke, and name2 is the name of the person from whose news feed the joke was reposted. It is guaranteed that for each string "name1 reposted name2" user "name1" didn't have the joke in his feed yet, and "name2" already had it in his feed by the moment of repost. Polycarp was registered as "Polycarp" and initially the joke was only in his feed.

Polycarp measures the popularity of the joke as the length of the largest repost chain. Print the popularity of Polycarp's joke.

Input
The first line of the input contains integer n (1 ≤ n ≤ 200) — the number of reposts. Next follow the reposts in the order they were made. Each of them is written on a single line and looks as "name1 reposted name2". All the names in the input consist of lowercase or uppercase English letters and/or digits and have lengths from 2 to 24 characters, inclusive.

We know that the user names are case-insensitive, that is, two names that only differ in the letter case correspond to the same social network user.

Output
Print a single integer — the maximum length of a repost chain.

Examples

input
5
tourist reposted Polycarp
Petr reposted Tourist
WJMZBMR reposted Petr
sdya reposted wjmzbmr
vepifanov reposted sdya

output
6


input
6
Mike reposted Polycarp
Max reposted Polycarp
EveryOne reposted Polycarp
111 reposted Polycarp
VkCup reposted Polycarp
Codeforces reposted Polycarp

output
2


input
1
SoMeStRaNgEgUe reposted PoLyCaRp

output
2

 */

#include <iostream>
#include <vector>
//#include <bits/stdc++.h>

using std::cin;
using std::cout;
using std::vector;
using std::string;
using std::pair;



int const DEFAULT_COLOR = 0;
//

void mark_connected_components(pair<string, int> name_id, vector<int> &color_list,
                               int cur_color, vector<pair<string, string>> &graph_pairs,
                               vector<pair<string, int>> unique_users) {

    string cur_name = name_id.first;
    int v = name_id.second;

    color_list.at(v) = cur_color;

    vector<pair<string, int>> destinations;

    for (int i = 0; i < graph_pairs.size(); i++) {
        if (graph_pairs.at(i).first == cur_name) {
            pair<string, int> name_id_destination;

            string name_to_find = graph_pairs.at(i).second;

            for (auto username_id : unique_users) {
                if (username_id.first == name_to_find) {
                    destinations.push_back(username_id);
                }
            }

        }
    }

    for (auto u : destinations) {
        if (color_list.at(u.second) == DEFAULT_COLOR) {
            mark_connected_components(u, color_list, cur_color, graph_pairs, unique_users);
        }
    }
}


void input() {

    int number_of_reposts;

    cin >> number_of_reposts;

    string name1, reposted, name2;

    string initial_name = "polycarp";

    vector<pair<string, string>> graph_pairs;

    vector<pair<string, int>> unique_users;

    for (int i = 0; i < number_of_reposts; i++) {
        cin >> name1 >> reposted >> name2;
        assert(reposted == "reposted");

        std::transform(name1.begin(), name1.end(), name1.begin(), ::tolower);
        std::transform(name2.begin(), name2.end(), name2.begin(), ::tolower);


        if (std::find(unique_users.begin(), unique_users.end(), name1) == unique_users.end()) {
            pair<string, int> name_id = std::make_pair(name1, unique_users.size());
            unique_users.push_back(name_id);
        }

        if (std::find(unique_users.begin(), unique_users.end(), name2) == unique_users.end()) {
            pair<string, int> name_id = std::make_pair(name2, unique_users.size());
            unique_users.push_back(name_id);
        }

        pair<string, string> repost_pair = std::make_pair(name2, name1);

        graph_pairs.push_back(repost_pair);
    }



    int n = unique_users.size();

    vector<int> color_vector;

    for (int i = 0; i < n; i++) {
        color_vector.push_back(DEFAULT_COLOR);
    }


    int number_of_components = 0;

    for (auto name_id : unique_users) {
        string name = name_id.first;
        int id = name_id.second;

        if (color_vector.at(id) == DEFAULT_COLOR) {

            number_of_components++;
            mark_connected_components(name_id, color_vector, number_of_components, graph_pairs, unique_users);
        }
    }

    vector<int> max_len_by_component;

    for (int i = 0; i < number_of_components; i++) {
        max_len_by_component.push_back(0);
    }

    for (int i = 0; i < color_vector.size(); i++) {
        int cur_color = color_vector.at(i - 1);
        max_len_by_component.at(cur_color) += 1;
    }

    int max_way = 0;

    for (int i = 0; i < max_len_by_component.size(); i++) {
        if (max_way < max_len_by_component.at(i)) {
            max_way = max_len_by_component.at(i);
        }
    }

    cout << max_way;



}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    input();

    return 0;
}






