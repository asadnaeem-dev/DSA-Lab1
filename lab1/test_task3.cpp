#include <iostream>
#include <vector>
#include "task3.h"

using namespace std;

int main() {
    int arr1[] = {10, 20, 10, 30, 10};
    vector<int> res1 = findAllIndices(arr1, 5, 10);
    cout << "Test 1 (Multiple): ";
    for (int idx : res1) cout << idx << " ";
    cout << endl;

    int arr2[] = {1, 2, 3, 4};
    vector<int> res2 = findAllIndices(arr2, 4, 99);
    cout << "Test 2 (Not Found Size): " << res2.size() << endl;

    vector<int> res3 = findAllIndices(nullptr, 0, 5);
    cout << "Test 3 (Empty Size): " << res3.size() << endl;

    return 0;
}