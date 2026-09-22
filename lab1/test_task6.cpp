#include <iostream>
#include <vector>
#include "task6.h"

using namespace std;

int main() {
    int arr1[] = {1, 2, 2, 3, 4};
    auto res1 = findMode(arr1, 5);
    cout << "Test 1 (Unique Mode): ";
    for (int val : res1) cout << val << " ";
    cout << endl;

    int arr2[] = {1, 1, 2, 2, 3};
    auto res2 = findMode(arr2, 5);
    cout << "Test 2 (Multiple Modes): ";
    for (int val : res2) cout << val << " ";
    cout << endl;

    auto res3 = findMode(nullptr, 0);
    cout << "Test 3 (Empty Array Size): " << res3.size() << endl;

    return 0;
}