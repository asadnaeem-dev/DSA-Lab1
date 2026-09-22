#include "task3.h"

std::vector<int> findAllIndices(const int arr[], int size, int key) {
    std::vector<int> indices;
    if (arr == nullptr || size <= 0) {
        return indices;
    }
    for (int i = 0; i < size; i++) {
        if (arr[i] == key) {
            indices.push_back(i);
        }
    }
    return indices;
}