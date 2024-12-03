#include<iostream>
#include<sstream>
#include<string>
#include<vector>

using namespace std;

void read_input(vector<vector<int>>& reports) {
    string line;

    while (getline(cin, line)) {
        istringstream iss(line);
        vector<int> report;
        int number = 0;

        while (iss >> number) {
            report.push_back(number);
        }

        reports.push_back(report);
    }
}

int is_safe_part_1(const vector<int>& report) {
    bool is_ascending = report[0] < report[1];
    int diff = 0;

    for (size_t i=0; i<report.size()-1; i++) {
        diff = report[i] - report[i+1];

        if (
            abs(diff) > 3 ||
            diff == 0 ||
            is_ascending != (diff < 0)
        ) {
            return 0;
        }
    }

    return 1;
}

int solve_part_1(const vector<vector<int>>& reports) {
    int n_safe_reports = 0;

    for (vector<int> report: reports) {
        n_safe_reports += is_safe_part_1 (report);
    }

    return n_safe_reports;
}

int is_safe_part_2(const vector<int>& report) {
    vector<int> copy;

    for (size_t i = 0; i < (report.size()); ++i) {
        copy = report;
        copy.erase(copy.begin() + i);

        if (is_safe_part_1(copy)) {
            return 1;
        }
    }

    return 0;
}

int solve_part_2(const vector<vector<int>>& reports) {
    int n_safe_reports = 0;

    for (vector<int> report: reports) {
        n_safe_reports += is_safe_part_2 (report);
    }

    return n_safe_reports;
}

int main(int argc, char* argv[]) {
    vector<vector<int>> reports;

    read_input(reports);

    int res_part_1 = solve_part_1 (reports);
    cout << "Part 1: " << res_part_1 << endl;

    int res_part_2 = solve_part_2 (reports);
    cout << "Part 2: " << res_part_2 << endl;
    
    return 0;
}
