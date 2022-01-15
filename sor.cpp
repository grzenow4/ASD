#include <iostream>

using namespace std;

const int m = 1000000000;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    int A[n], L[n][n], R[n][n];
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    for (int i = 0; i < n - 1; i++) {
        L[i][i] = R[i][i] = 1;

        if (A[i] < A[i + 1]) {
            L[i][i + 1] = R[i][i + 1] = 1;
        }
        else {
            L[i][i + 1] = R[i][i + 1] = 0;
        }
    }
    L[n - 1][n - 1] = R[n - 1][n - 1] = 1;

    int i = 0, j = 2, r = 2;

    while (r < n) {
        while (j < n) {
            L[i][j] = ((A[i] < A[i + 1]) * L[i + 1][j] + (A[i] < A[j]) * R[i + 1][j]) % m;
            R[i][j] = ((A[i] < A[j]) * L[i][j - 1] + (A[j - 1] < A[j]) * R[i][j - 1]) % m;
            i++;
            j++;
        }
        r++;
        i = 0;
        j = i + r;
    }

    if (n == 1)
        cout << 1;
    else
        cout << (L[0][n - 1] + R[0][n - 1]) % m;
}
