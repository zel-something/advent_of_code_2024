#include <cstddef>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

void read_input(vector<string>& map) {
    string line;

    while (getline(cin, line)) {
        map.push_back(line);
    }
}

void get_antennas_coordinates(
    const vector<string>& map,
    unordered_map<char, vector<pair<int, int>>>& antennas
) {
    char f;

    for (size_t r = 0; r < map.size(); ++r) {
        for (size_t c = 0; c < map.size(); ++c) {
            f = map.at(r).at(c);
            if (f != '.') {
                antennas[f].push_back({r, c});
            }
        }
    }
}

bool is_inside_map(const pair<int, int>& coordinates, int size) {
    if (
        coordinates.first >= 0 &&
        coordinates.first < size &&
        coordinates.second >= 0 &&
        coordinates.second < size
    ) {
        return true;
    }

    return false;
}

void get_antinodes_coordinates(
    const vector<pair<int, int>>& same_f,
    unordered_set<int>& antinodes,
    int size
) {
    pair<int, int> x;

    for (size_t i = 0; i < same_f.size() - 1; ++i) {
        for (size_t j = i + 1; j < same_f.size(); ++j) {
            x.first = same_f[i].first * 2 - same_f[j].first;
            x.second = same_f[i].second * 2 - same_f[j].second;

            if (is_inside_map(x, size)) {
                antinodes.insert(x.first * size + x.second);
            } 

            x.first = same_f[j].first * 2 - same_f[i].first;
            x.second = same_f[j].second * 2 - same_f[i].second;
            
            if (is_inside_map(x, size)) {
                antinodes.insert(x.first * size + x.second);
            }
        }
    }
}

int solve_part_1(const vector<string>& map) {
    unordered_map<char, vector<pair<int, int>>> antennas;
    unordered_set<int> antinodes;

    get_antennas_coordinates(map, antennas);

    for (auto& it: antennas) {
        get_antinodes_coordinates(it.second, antinodes, map.size());
    }

    return antinodes.size();
}

void get_antinodes_coordinates_line(
    const vector<pair<int, int>>& same_f,
    unordered_set<int>& antinodes,
    int size
){
    pair<int, int> x;
    int diff_r = 0, diff_c = 0;

    for (size_t i = 0; i < same_f.size() - 1; ++i) {
        for (size_t j = i + 1; j < same_f.size(); ++j) {
            diff_r = same_f[i].first - same_f[j].first;
            diff_c = same_f[i].second - same_f[j].second;
            
            x.first = same_f[i].first;
            x.second = same_f[i].second;
            
            while (is_inside_map(x, size)) {
                antinodes.insert(x.first * size + x.second);
                x.first += diff_r;
                x.second += diff_c;
            }

            x.first = same_f[j].first;
            x.second = same_f[j].second;
            
            while (is_inside_map(x, size)) {
                antinodes.insert(x.first * size + x.second);
                x.first -= diff_r;
                x.second -= diff_c;
            }
        }
    }
}

int solve_part_2(const vector<string>& map) {
    unordered_map<char, vector<pair<int, int>>> antennas;
    unordered_set<int> antinodes;

    get_antennas_coordinates(map, antennas);

    for (auto& it: antennas) {
        get_antinodes_coordinates_line(it.second, antinodes, map.size());
    }

    return antinodes.size();
}

int main (int argc, char *argv[]) {
    vector<string> map;

    read_input(map);

    int res_part_1 = solve_part_1(map);
    cout << "Part 1: " << res_part_1 << endl;

    int res_part_2 = solve_part_2(map);
    cout << "Part 2: " << res_part_2 << endl;
    
    return 0;
}
