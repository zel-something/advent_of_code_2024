#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

void read_input(
    vector<int>& left_list,
    vector<int>& right_list
) {
    int left_number = 0, right_number = 0;

    while (cin >> left_number >> right_number) {
        left_list.push_back(left_number);
        right_list.push_back(right_number);
    }
}

int solve_part_1(
    vector<int>& left_list,
    vector<int>& right_list
) {
    sort (left_list.begin(), left_list.end());
    sort (right_list.begin(), right_list.end());

    int sum = 0;
    for (size_t i=0; i<left_list.size(); i++) {
        sum += abs(left_list[i] - right_list[i]);
    }

    return sum;
}

int solve_part_2(
    const vector<int>& left_list,
    const vector<int>& right_list
) {
    unordered_map<int, int> map;
    for (int elt: right_list) {
        map[elt]++;
    }

    int sum = 0;
    for (int elt: left_list) {
        sum += elt * map[elt];
    }

    return sum;
}

int main(int argc, char* argv[]) {
    vector<int> left_list, right_list;

    read_input (left_list, right_list);

    int res_part_1 = solve_part_1 (left_list, right_list);
    cout << "Part 1: " << res_part_1 << endl;

    int res_part_2 = solve_part_2 (left_list, right_list);
    cout << "Part 2: " << res_part_2 << endl;
}
