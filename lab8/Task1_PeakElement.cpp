// Task 1: Peak element in a 2D array in O(n log n)
#include <iostream>
#include <vector>
#include <climits>
#include <cstdlib>
using namespace std;

// Returns {row, col} of a peak element (>= all 4 neighbours).
// Binary search over columns: O(rows) per step, O(log cols) steps.
pair<int,int> findPeak(const vector<vector<int>>& a) {
    int rows = a.size(), cols = a[0].size();
    int lo = 0, hi = cols - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        // 1) find the row holding the maximum of the middle column
        int maxRow = 0;
        for (int r = 1; r < rows; r++)
            if (a[r][mid] > a[maxRow][mid]) maxRow = r;
        int cur   = a[maxRow][mid];
        int left  = (mid > 0)        ? a[maxRow][mid - 1] : INT_MIN;
        int right = (mid < cols - 1) ? a[maxRow][mid + 1] : INT_MIN;
        // 2) it is >= up/down (it is the column max); check left/right
        if (cur >= left && cur >= right) return {maxRow, mid};
        if (left > cur) hi = mid - 1;   // a peak must exist in left half
        else            lo = mid + 1;   // a peak must exist in right half
    }
    return {-1, -1};
}

bool isPeak(const vector<vector<int>>& a, int r, int c) {
    int dr[] = {-1,1,0,0}, dc[] = {0,0,-1,1};
    for (int k = 0; k < 4; k++) {
        int nr = r + dr[k], nc = c + dc[k];
        if (nr >= 0 && nr < (int)a.size() && nc >= 0 && nc < (int)a[0].size() && a[nr][nc] > a[r][c])
            return false;
    }
    return true;
}

int main() {
    vector<vector<int>> a = {
        {10, 8, 10, 10},
        {14, 13, 12, 11},
        {15, 9, 11, 21},
        {16, 17, 19, 20}
    };
    auto p = findPeak(a);
    cout << "Peak at (" << p.first << ", " << p.second << ") = " << a[p.first][p.second]
         << (isPeak(a, p.first, p.second) ? "  [verified]" : "  [WRONG]") << endl;

    vector<vector<int>> b = {{1, 4, 3}, {6, 7, 5}, {2, 8, 9}};
    p = findPeak(b);
    cout << "Peak at (" << p.first << ", " << p.second << ") = " << b[p.first][p.second]
         << (isPeak(b, p.first, p.second) ? "  [verified]" : "  [WRONG]") << endl;

    // random stress test
    srand(1);
    int bad = 0;
    for (int t = 0; t < 2000; t++) {
        int R = rand()%8+1, C = rand()%8+1;
        vector<vector<int>> m(R, vector<int>(C));
        for (auto& row : m) for (auto& x : row) x = rand()%20;
        auto q = findPeak(m);
        if (!isPeak(m, q.first, q.second)) bad++;
    }
    cout << "Random tests failed: " << bad << " / 2000" << endl;
}
