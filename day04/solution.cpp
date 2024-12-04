#include <iostream>
#include <string>
#include <vector>

using namespace std;

void read_input(vector<string>& text) {
    string line;

    while (getline(cin, line)) {
        text.push_back(line);
    }
}

int solve_part_1(const vector<string>& text, size_t line_size) {
    int count = 0;
    size_t new_r = 0, new_c = 0;
    string target = "MAS";
    
    vector<vector<pair<size_t, size_t>>> directions = {
        {{0, 1}, {0, 2}, {0, 3}},
        {{0, -1}, {0, -2}, {0, -3}},
        {{1, 0}, {2, 0}, {3, 0}},
        {{-1, 0}, {-2, 0}, {-3, 0}},
        {{1, 1}, {2, 2}, {3, 3}},
        {{-1, -1}, {-2, -2}, {-3, -3}},
        {{1, -1}, {2, -2}, {3, -3}},
        {{-1, 1}, {-2, 2}, {-3, 3}},
    };

    for (size_t r = 0; r < line_size; ++r) {
        for (size_t c = 0; c < line_size; ++c) {
            if (text[r][c] == 'X') {
                for (const auto& d: directions) {
                    for (size_t i = 0; i < target.size(); ++i) {
                        new_r = r + d[i].first;
                        new_c = c + d[i].second;
                        if (
                            new_r < 0 || new_r >= line_size ||
                            new_c < 0 || new_c >= line_size ||
                            text[new_r][new_c] != target[i]
                        ) { 
                            break;
                        }
                        if (i == target.size()-1) {
                            count++;
                        }
                    }
                }
            }
        }
    }
    
    return count;
}

int solve_part_2(const vector<string>& text, size_t line_size) {
    int count = 0;
    string str_1, str_2;

    for (size_t r = 1; r < line_size - 1; ++r) {
        for (size_t c = 1; c < line_size - 1; ++c) {
            if (text[r][c] == 'A') {
                str_1 = {text[r-1][c-1], text[r+1][c+1]};
                str_2 = {text[r-1][c+1], text[r+1][c-1]};
                if (
                    (str_1 == "SM" || str_1 == "MS") &&
                    (str_2 == "SM" || str_2 == "MS")
                ) {
                    count++;
                }
            } 
        }
    }

    return count;
}

int main(int argc, char* argv[]) {
    vector<string> text;

    read_input(text);

    int res_part_1 = solve_part_1(text, text[0].size());
    cout << "Part 1: " << res_part_1 << endl;

    int res_part_2 = solve_part_2(text, text[0].size());
    cout << "Part 2: " << res_part_2 << endl;
}
