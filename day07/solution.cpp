#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

void read_input(vector<pair<long, vector<int>>>& table) {
    string line;

    while (getline(cin, line)) {
        istringstream iss(line);
        pair<long, vector<int>> entry;
        string separator;
        int number;
        
        iss >> entry.first >> separator;
        while (iss >> number) {
            entry.second.push_back(number);
        }

    table.push_back(entry);
    }
}

long find_operators_binary(const pair<long, vector<int>> entry) {
    int n_ops = entry.second.size() - 1;
    int n_combinations = pow(2, n_ops);

    for (int m = 0; m < n_combinations; ++m) {
        long res = entry.second[0];

        for (int i = 0; i < n_ops; ++i) {
            if (m & (1 << i)) {
                res *= entry.second[i+1];
            } else {
                res += entry.second[i+1];
            }

            if (res > entry.first) {
                break;
            }
        }

        if (res == entry.first) {
            return res;
        }
    }

    return 0;
}

long solve_part_1(const vector<pair<long, vector<int>>>& table) {
    long sum = 0;

    for (const auto& entry: table) {
        sum += find_operators_binary(entry);
    }

    return sum;
}

long find_operators_ternary(const pair<long, vector<int>>& entry) {
    int n_ops = entry.second.size() - 1;
    int n_combinations = pow(3, n_ops);
    string str_1, str_2;

    for (int m = 0; m < n_combinations; ++m) {
        int mask = m;
        long res = entry.second[0];

        for (int i = 0; i < n_ops; ++i) {
            int op = mask % 3;
            mask /= 3;

            if (op == 0) {
                str_1 = to_string(res);
                str_2 = to_string(entry.second[i+1]);
                res = stol(str_1 + str_2);
            } else if (op == 1) {
                res *= entry.second[i+1];
            } else {
                res += entry.second[i+1];
            }

            if (res > entry.first) {
                break;
            }
        }

        if (res == entry.first) {
            return res;
        }
    }

    return 0;
}

long solve_part_2(const vector<pair<long, vector<int>>>& table) {
    long sum = 0;
    long res = 0;

    for (const auto& entry: table) {
        res = find_operators_binary(entry);
        if (res == 0) {
            res = find_operators_ternary(entry);
        }
    
        sum += res;
    }

    return sum;
}

int main (int argc, char *argv[]) {
    vector<pair<long, vector<int>>> table;

    read_input(table);

    long res_part_1 = solve_part_1(table);
    cout << "Part 1: " << res_part_1 << endl;

    long res_part_2 = solve_part_2(table);
    cout << "Part 2: " << res_part_2 << endl;

    return 0;
}
