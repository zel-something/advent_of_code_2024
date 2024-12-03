#include <iostream>
#include <regex>
#include <iterator>
#include <string>

using namespace std;

void read_input(string& instructions) {
    instructions.assign((istreambuf_iterator<char>(cin)),
                        istreambuf_iterator<char>());
}

int solve_part_1(const string& instructions) {
    int sum = 0;

    regex pattern("mul\\(([0-9]+),([0-9]+)\\)");

    auto matches_begin = sregex_iterator(
        instructions.begin(),
        instructions.end(),
        pattern
    );
    auto matches_end = sregex_iterator();

    smatch match;
    
    for (auto it = matches_begin; it != matches_end; ++it) {
        match = *it;
        sum += stoi(match[1].str()) * stoi(match[2].str());
    }

    return sum;
}

int solve_part_2(const string& instructions) {
    int sum = 0;
    bool enable = true;

    regex pattern("mul\\(([0-9]+),([0-9]+)\\)|do\\(\\)|don't\\(\\)"); 

    auto matches_begin = sregex_iterator(
        instructions.begin(),                                  
        instructions.end(),              
        pattern  
    );    
    auto matches_end = sregex_iterator();

    smatch match;

    for (auto it = matches_begin; it != matches_end; ++it) {  
        match = *it;
        
        if (match.str() == "do()") {
            enable = true;
        } else if (match.str() == "don't()") {
            enable = false;
        } else {
            sum += (enable)? stoi(match[1].str()) * stoi(match[2].str()): 0;
        }
    }
    
    return sum;
}

int main(int argc, char* argv[]) {
    string instructions;

    read_input(instructions);

    int res_part_1 = solve_part_1(instructions);
    cout << "Part 1: " << res_part_1 << endl;

    int res_part_2 = solve_part_2(instructions);
    cout << "Part 2: " << res_part_2 << endl;

    return 0;
}
