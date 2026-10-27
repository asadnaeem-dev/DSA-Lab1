// Task 2: Knight's Tour - backtracking with Warnsdorff's heuristic
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <tuple>
#include <cstdlib>
using namespace std;

const int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2};
const int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

int N;
vector<vector<int>> board;
long long steps = 0;   // counts recursive calls (for analysis)

bool isSafe(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < N && board[x][y] == -1;
}

// number of onward moves available from (x, y)
int degree(int x, int y) {
    int c = 0;
    for (int k = 0; k < 8; k++)
        if (isSafe(x + dx[k], y + dy[k])) c++;
    return c;
}

bool solve(int x, int y, int move) {
    steps++;
    board[x][y] = move;
    if (move == N * N - 1) return true;

    // collect candidate moves, ordered by Warnsdorff's rule:
    // try the square with the FEWEST onward moves first
    vector<tuple<int,int,int>> cand;   // (degree, -distance from centre, direction)
    for (int k = 0; k < 8; k++) {
        int nx = x + dx[k], ny = y + dy[k];
        if (isSafe(nx, ny)) {
            // tie-break: prefer squares FARTHER from the centre (edges/corners first)
            int d2 = (2*nx-(N-1))*(2*nx-(N-1)) + (2*ny-(N-1))*(2*ny-(N-1));
            cand.push_back(make_tuple(degree(nx, ny), -d2, k));
        }
    }
    sort(cand.begin(), cand.end());

    for (auto& c : cand) {
        int k = get<2>(c);
        if (solve(x + dx[k], y + dy[k], move + 1)) return true;
    }
    board[x][y] = -1;   // BACKTRACK
    return false;
}

bool knightsTour(int n, int sx, int sy) {
    N = n; steps = 0;
    // Parity pre-check: on an odd board an open tour must start on the
    // majority colour ((x+y) even); on 2x2, 3x3, 4x4 no tour exists at all.
    if (n == 1) { board.assign(1, vector<int>(1, 0)); return true; }
    if (n <= 4) return false;
    if (n % 2 == 1 && (sx + sy) % 2 == 1) return false;
    board.assign(N, vector<int>(N, -1));
    return solve(sx, sy, 0);
}

void print() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) cout << setw(4) << board[i][j];
        cout << "\n";
    }
}

bool verify(int sx, int sy) {
    vector<pair<int,int>> pos(N*N, {-1,-1});
    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
        int v = board[i][j];
        if (v < 0 || v >= N*N || pos[v].first != -1) return false;
        pos[v] = {i, j};
    }
    if (pos[0] != make_pair(sx, sy)) return false;
    for (int v = 1; v < N*N; v++) {
        int ddx = abs(pos[v].first - pos[v-1].first), ddy = abs(pos[v].second - pos[v-1].second);
        if (!((ddx == 1 && ddy == 2) || (ddx == 2 && ddy == 1))) return false;
    }
    return true;
}

int main() {
    int n = 8, x = 0, y = 0;
    if (knightsTour(n, x, y)) { print(); cout << "verified: " << verify(x,y) << ", calls: " << steps << " (N*N = " << n*n << ")\n"; }
    else cout << "No tour found\n";

    cout << "\nAll starting squares, various N:\n";
    for (int s : {5, 6, 7, 8, 10, 12, 16, 20, 30}) {
        long long maxSteps = 0; int fails = 0, notv = 0;
        for (int i = 0; i < s; i++) for (int j = 0; j < s; j++) {
            if (!knightsTour(s, i, j)) { fails++; continue; }
            if (!verify(i, j)) notv++;
            maxSteps = max(maxSteps, steps);
        }
        cout << "N=" << s << " N*N=" << s*s << " max calls=" << maxSteps << " no-tour starts=" << fails << " invalid=" << notv << "\n";
    }
}
