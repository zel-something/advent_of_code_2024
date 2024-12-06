#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

void read_input(vector<string>& map) {
    string line;

    while (getline(cin, line)) {
        map.push_back(line);
    }
}

pair<int, int> get_start_pos(const vector<string>& map) {
    pair<int, int> start_pos;

    for (size_t r = 0; r < map.size(); ++r) {
        for (size_t c = 0; c < map.size(); ++c) {
            if (map[r][c] == '^') {
                start_pos.first = r;
                start_pos.second = c;
            }
        }
    }

    return start_pos;
}

bool is_inside(const pair<int, int>& pos, int size) {
    if (
        pos.first < 0 ||
        pos.first >= size ||
        pos.second < 0 ||
        pos.second >= size
    ) {
        return false;
    }

    return true;
}

int solve_part_1(vector<string> map, set<pair<int, int>>& path) {
    int count = 0;
    pair<int, int> pos = get_start_pos(map);
    pair<int, int> dir = {-1, 0};

    while (is_inside(pos, map.size())) {
        if (map[pos.first][pos.second] != '#') {
            map[pos.first][pos.second] = 'X';
        } else {
            pos.first -= dir.first;
            pos.second -= dir.second;

            int temp = dir.first;
            dir.first = dir.second;
            dir.second = -temp;
        }

        pos.first += dir.first;
        pos.second += dir.second;
    }

    for (size_t r = 0; r < map.size(); ++r) {
        for (size_t c = 0; c < map.size(); ++c) {
            if (map[r][c] == 'X') {
                count++;
                path.insert({r, c});
            }
        }
    }

    return count;
}

bool is_looping(const vector<string>& map) {
    pair<int, int> pos = get_start_pos(map);
    pair<int, int> dir = {-1, 0};
    unordered_map<int, vector<pair<int, int>>> visited;

    while (is_inside(pos, map.size())) {
        if (map[pos.first][pos.second] != '#') {
            int idx = pos.first * map.size() + pos.second;

            for (pair<int, int> d : visited[idx]) {
                if (d == dir) {
                    return true;
                }
            }

            visited[idx].push_back(dir);
        } else {
            pos.first -= dir.first;
            pos.second -= dir.second;

            int temp = dir.first;
            dir.first = dir.second;
            dir.second = -temp;
        }

        pos.first += dir.first;
        pos.second += dir.second;
    }

    return false;
}

int solve_part_2(
    const vector<string>& map,
    const set<pair<int, int>>& path
) {
    int count = 0;

    for (const auto &coord : path) {
        vector<string> new_map = map;
        new_map[coord.first][coord.second] = '#';

        if (is_looping(new_map)) {
            count++;
        }
    }

    return count;
}

int main(int argc, char *argv[]) {
    vector<string> map;
    set<pair<int, int>> path;

    read_input(map);

    int res_part_1 = solve_part_1(map, path);
    cout << "Part 1: " << res_part_1 << endl;

    int res_part_2 = solve_part_2(map, path);
    cout << "Part 2: " << res_part_2 << endl;

    return 0;
}
