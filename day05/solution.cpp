#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

void read_input(
    unordered_map<int, vector<int>>& rules_forward,
    unordered_map<int, vector<int>>& rules_backward,
    vector<vector<int>>& updates
) {
    string line;
    char delimiter;
    int n_left, n_right;
    
    while (getline(cin, line) && !line.empty()) {
        istringstream iss(line);
        iss >> n_left >> delimiter >> n_right;
        rules_forward[n_left].push_back(n_right);
        rules_backward[n_right].push_back(n_left);
    }
    
    string n_str;
    while (getline(cin, line)) {
        istringstream iss(line);
        vector<int> update; 
            
        while (getline(iss, n_str, ',')) {
            update.push_back(stoi(n_str));
        }

        updates.push_back(update);
    }
}

int is_right_order(
    const unordered_map<int, vector<int>>& rules,
    const vector<int> update
) {
    for (size_t i = 0; i < update.size(); ++i) {
        for (size_t j = 0; j < i; ++j) {
            auto it = rules.find(update[j]);
            
            if (it != rules.end()) {
                for (int n: it->second) {
                    if (update[i] == n) {
                        return 0;
                    }
                }
            }
        }
    }

    return update[update.size()/2];
}

int solve_part_1(
    const unordered_map<int, vector<int>>& rules,
    const vector<vector<int>>& updates,
    vector<int>& wrong_updates
) {
    int sum = 0, add = 0;

    for (size_t i = 0; i < updates.size(); ++i) {
        add = is_right_order(rules, updates[i]);
        
        if (add == 0) {
            wrong_updates.push_back(i);
        } else {
            sum += add;
        }
    }

    return sum;
}

int correct_order(
    const unordered_map<int, vector<int>>& rules,
    const vector<int>& update
) {
    vector<int> correct = update;
    
    for (size_t i = 0; i < update.size(); ++i) {
        bool change = false;
        auto it = rules.find(update[i]);

        if (it != rules.end()) {
            for (size_t j = 0; j < i; ++j) {
                for (int n: it->second) {
                    if (correct[j] == n) {
                        correct.erase(correct.begin() + i);
                        correct.insert(correct.begin() + j, update[i]);
                        change = true;
                        break;
                    }
                }

                if (change) {
                    break;
                }
            }
        }
    }

    return correct[update.size()/2];
}

int solve_part_2(
    const unordered_map<int, vector<int>>& rules,
    const vector<vector<int>>& updates,
    const vector<int>& wrong_updates
) {
    int sum = 0;

    for (int n: wrong_updates) {
        sum += correct_order(rules, updates[n]);
    }

    return sum;
}

int main(int argc, char* argv[]) {
    unordered_map<int, vector<int>> rules_forward;
    unordered_map<int, vector<int>> rules_backward;
    vector<vector<int>> updates;
    vector<int> wrong_updates;

    read_input(rules_forward, rules_backward, updates);

    int res_part_1 = solve_part_1(
        rules_backward,
        updates,
        wrong_updates
    );
    cout << "Part 1: " << res_part_1 << endl;

    int res_part_2 = solve_part_2(
        rules_forward,
        updates,
        wrong_updates
    );
    cout << "Part 2: " << res_part_2 << endl;

    return 0;
}
