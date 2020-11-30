#include <iostream>
#include <string>
#include <assert.h>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

int solve_cafe(vector<int> dinner_costs) {
    int n = dinner_costs.size() + 1;

    int PRICE_FOR_COUPON = 100;

    vector<long long int> min_cost_array;

    min_cost_array.push_back(0);

    for (int i = 1; i < n; i++) {
        min_cost_array.push_back(LONG_LONG_MAX / 2);
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n; j++) {
            min_cost_array.push_back(-1);
        }
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n; j++) {

            int receiving_coupon_idx = (i - 1) * n + j - 1;
            int using_coupon_idx = (i - 1) * n + j + 1;
            int day_before_idx = (i - 1) * n + j;
            int current_idx = i * n + j;

            long long int dinner_price = dinner_costs.at(i - 1);

            long long int cost_if_use_coupon = min_cost_array.at(using_coupon_idx);

            if (dinner_price <= PRICE_FOR_COUPON) {

                long long int cost_if_buy =
                        min_cost_array.at(day_before_idx) + dinner_price;
                if (j == n - 1) {
                    min_cost_array.at(current_idx) = cost_if_buy;
                } else if (cost_if_buy <= cost_if_use_coupon) {
                    min_cost_array.at(current_idx) = cost_if_buy;
                } else {
                    min_cost_array.at(current_idx) = cost_if_use_coupon;
                }
            } else {
                if (j == 0) {
                    min_cost_array.at(current_idx) = cost_if_use_coupon;
                } else if (j == n - 1) {
                    min_cost_array.at(current_idx) = min_cost_array.at(receiving_coupon_idx) + dinner_price;
                } else {
                    long long int cost_for_buying_plus_coupon =
                            min_cost_array.at(receiving_coupon_idx) + dinner_price;

                    if (cost_for_buying_plus_coupon <= cost_if_use_coupon) {
                        min_cost_array.at(current_idx) = cost_for_buying_plus_coupon;
                    } else {
                        min_cost_array.at(current_idx) = cost_if_use_coupon;
                    }
                }
            }
        }
    }


    long long int k1_min = INT_MAX;
    int k1_min_idx;

    for (int j = n - 1; j >= 0; j--) {
        int i = n - 1;
        int current_idx = i * n + j;

        long long int k1 = min_cost_array.at(current_idx);

        if (k1_min > k1) {
            k1_min = k1;
            k1_min_idx = j;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int current_idx = i * n + j;
            cout << min_cost_array.at(current_idx) << " ";
        }
        cout << std::endl;
    }
    cout << std::endl;


    vector<int> coupon_use_days;

    int cur_j = k1_min_idx;
    long long int cur_val;

    for (int i = n - 1; i > 0; --i) {

        cur_val = min_cost_array.at(i * n + cur_j);

        if (min_cost_array.at((i - 1) * n + cur_j + 1) == cur_val) {
            coupon_use_days.push_back(i - 1);
            cur_j++;

        } else {

            if (cur_j == 0) {
                cur_j = 0;

            } else {

                long long int up_value = min_cost_array.at((i - 1) * n + cur_j);
                long long int left_diag_val = min_cost_array.at((i - 1) * n + cur_j - 1);
                int dinner_price = dinner_costs.at(i - 1);
                if (cur_val == left_diag_val + dinner_price) {
                    cur_j--;
                }
            }
        }

    }

    cout << k1_min << std::endl;
    cout << k1_min_idx << " " << coupon_use_days.size() << std::endl;

    for (int i = coupon_use_days.size() - 1; i >= 0; --i) {
        cout << coupon_use_days.at(i) + 1;
//        cout << " " << dinner_costs.at(i);
        cout << std::endl;

    }

//    int final_cost = min_cost_array.back();

    return -1;
}


void input() {

    int n;
    cin >> n;

    vector<int> dinner_costs;

    for (int i = 0; i < n; i++) {
        int new_cost;
        cin >> new_cost;
        dinner_costs.push_back(new_cost);

    }

    int result_distance = solve_cafe(dinner_costs);

//    cout << result_distance;
}

//void t0() {
//
//    std::string first_sequence =  "BCEFG";
//    std::string second_sequence = "CEXGI";
//
//    int result_distance2 = solve_levenshtein_distance(first_sequence, second_sequence);
//    assert(result_distance2 == 3);
//
//}
//
//void t1() {
//
//    std::string first_sequence = "ABCDEFGH";
//    std::string second_sequence = "ACDEXGIH";
//
//    int result_distance2 = solve_levenshtein_distance(first_sequence, second_sequence);
//    assert(result_distance2 == 3);
//
//}
//
//void t2() {
//    std::string first_sequence = "ABCDE";
//    std::string second_sequence = "BDA";
//
//    int result_distance2 = solve_levenshtein_distance(first_sequence, second_sequence);
//    assert(result_distance2 == 3);
//}
//
//void t3() {
//    std::string first_sequence = "ABCDEFGH";
//    std::string second_sequence = "AMCDEFGH";
//
//    int result_distance2 = solve_levenshtein_distance(first_sequence, second_sequence);
//    assert(result_distance2 == 1);
//}
//
//void t4() {
//    std::string first_sequence = "ABCDEFGH";
//    std::string second_sequence = "ABCDFGH";
//
//    int result_distance2 = solve_levenshtein_distance(first_sequence, second_sequence);
//    assert(result_distance2 == 1);
//}
//
//void t5() {
//    std::string first_sequence = "ABCDEFGH";
//    std::string second_sequence = "ALCDFH";
//
//    int result_distance2 = solve_levenshtein_distance(first_sequence, second_sequence);
//    assert(result_distance2 == 3);
//}
//
//void t6() {
//    std::string first_sequence = "ABCDEFGGGGGGH";
//    std::string second_sequence = "AMCDEFGH";
//
//    int result_distance2 = solve_levenshtein_distance(first_sequence, second_sequence);
//    assert(result_distance2 == 6);
//}
//
//
//void test() {
//    t0();
//    t1();
//    t2();
//    t3();
//    t4();
//    t5();
//    t6();
//}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    input();

//    test();

    return 0;
}


