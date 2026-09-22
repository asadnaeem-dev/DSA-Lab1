#include "task7.h"

std::vector<std::vector<int>> standardMultiply(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B) {
    int n = A.size();
    std::vector<std::vector<int>> C(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            for (int j = 0; j < n; j++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

static std::vector<std::vector<int>> addMatrix(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B) {
    int n = A.size();
    std::vector<std::vector<int>> res(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[i][j] = A[i][j] + B[i][j];
        }
    }
    return res;
}

static std::vector<std::vector<int>> subMatrix(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B) {
    int n = A.size();
    std::vector<std::vector<int>> res(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[i][j] = A[i][j] - B[i][j];
        }
    }
    return res;
}

std::vector<std::vector<int>> strassenMultiply(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B) {
    int n = A.size();
    if (n <= 2) {
        return standardMultiply(A, B);
    }

    int k = n / 2;
    std::vector<std::vector<int>> a11(k, std::vector<int>(k)), a12(k, std::vector<int>(k)), a21(k, std::vector<int>(k)), a22(k, std::vector<int>(k));
    std::vector<std::vector<int>> b11(k, std::vector<int>(k)), b12(k, std::vector<int>(k)), b21(k, std::vector<int>(k)), b22(k, std::vector<int>(k));

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            a11[i][j] = A[i][j];
            a12[i][j] = A[i][j + k];
            a21[i][j] = A[i + k][j];
            a22[i][j] = A[i + k][j + k];

            b11[i][j] = B[i][j];
            b12[i][j] = B[i][j + k];
            b21[i][j] = B[i + k][j];
            b22[i][j] = B[i + k][j + k];
        }
    }

    auto m1 = strassenMultiply(addMatrix(a11, a22), addMatrix(b11, b22));
    auto m2 = strassenMultiply(addMatrix(a21, a22), b11);
    auto m3 = strassenMultiply(a11, subMatrix(b12, b22));
    auto m4 = strassenMultiply(a22, subMatrix(b21, b11));
    auto m5 = strassenMultiply(addMatrix(a11, a12), b22);
    auto m6 = strassenMultiply(subMatrix(a21, a11), addMatrix(b11, b12));
    auto m7 = strassenMultiply(subMatrix(a12, a22), addMatrix(b21, b22));

    auto c11 = addMatrix(subMatrix(addMatrix(m1, m4), m5), m7);
    auto c12 = addMatrix(m3, m5);
    auto c21 = addMatrix(m2, m4);
    auto c22 = addMatrix(addMatrix(subMatrix(m1, m2), m3), m6);

    std::vector<std::vector<int>> C(n, std::vector<int>(n, 0));
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = c11[i][j];
            C[i][j + k] = c12[i][j];
            C[i + k][j] = c21[i][j];
            C[i + k][j + k] = c22[i][j];
        }
    }
    return C;
}