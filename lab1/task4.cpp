#include "task4.h"

int findPattern(const std::string& text, const std::string& pattern) {
    if (pattern.empty()) {
        return -1;
    }
    int n = text.length();
    int m = pattern.length();
    if (m > n) {
        return -1;
    }
    for (int i = 0; i <= n - m; i++) {
        int j = 0;
        while (j < m && text[i + j] == pattern[j]) {
            j++;
        }
        if (j == m) {
            return i;
        }
    }
    return -1;
}