#include "task6.h"
#include <map>

std::vector<int> findMode(const int arr[], int size) {
    std::vector<int> modes;
    if (arr == nullptr || size <= 0) {
        return modes;
    }
    std::map<int, int> freq;
    int maxFreq = 0;
    for (int i = 0; i < size; i++) {
        freq[arr[i]]++;
        if (freq[arr[i]] > maxFreq) {
            maxFreq = freq[arr[i]];
        }
    }
    for (const auto& entry : freq) {
        if (entry.second == maxFreq) {
            modes.push_back(entry.first);
        }
    }
    return modes;
}