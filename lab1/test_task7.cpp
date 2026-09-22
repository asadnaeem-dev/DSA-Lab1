#include <iostream>
#include <vector>
#include "task7.h"

using namespace std;

int main() {
    vector<vector<int>> A2 = {{1, 2}, {3, 4}};
    vector<vector<int>> B2 = {{5, 6}, {7, 8}};
    auto S2 = strassenMultiply(A2, B2);
    auto N2 = standardMultiply(A2, B2);
    cout << "Test 1 (2x2 Matches): " << (S2 == N2 ? "PASS" : "FAIL") << endl;

    vector<vector<int>> A4 = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 1, 2, 3},
        {4, 5, 6, 7}
    };
    vector<vector<int>> B4 = {
        {7, 6, 5, 4},
        {3, 2, 1, 9},
        {8, 7, 6, 5},
        {4, 3, 2, 1}
    };
    auto S4 = strassenMultiply(A4, B4);
    auto N4 = standardMultiply(A4, B4);
    cout << "Test 2 (4x4 Matches): " << (S4 == N4 ? "PASS" : "FAIL") << endl;

    cout << "4x4 Result Matrix:" << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << S4[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}