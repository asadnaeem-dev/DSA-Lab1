#include <iostream>
#include <vector>
#include "task5.h"

using namespace std;

int main() {
    auto t0 = generatePascalsTriangle(0);
    cout << "Test 1 (n=0 size): " << t0.size() << endl;

    auto t1 = generatePascalsTriangle(1);
    cout << "Test 2 (n=1): " << t1[0][0] << endl;

    auto t5 = generatePascalsTriangle(5);
    cout << "Test 3 (n=5 row 5): ";
    for (int val : t5[4]) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}