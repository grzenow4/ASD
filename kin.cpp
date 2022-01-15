#include <iostream>

using namespace std;

const int LIMIT_N = 2e4;
const int LIMIT_K = 10;
const int MOD = 1e9;
int nums[LIMIT_N];
int T[LIMIT_N][LIMIT_K + 1];
int B = 1;

// Tworzy tablice reprezentującą drzewo o B >= n liściach wypełnione zerami.
int* init(int size) {
    int *arr = new int[size];

    for (int i = 0; i < size; i++) {
        arr[i] = 0;
    }

    return arr;
}

// Wstawia wartość w na miejsce i w tablicy.
void modify(int *arr, int i, int w) {
    if (i > 1) {
        int w2 = (MOD + w - arr[i]) % MOD;
        arr[i] = w;
        i /= 2;
        modify(arr, i, (arr[i] + w2) % MOD);
    }
}

// Zwraca sumę elementów tablicy od indeksu l do r (włącznie).
int query(int *arr, int l, int r) {
    if (l > r) return 0;
    if (l == r) return arr[l];

    int res = (arr[l] + arr[r]) % MOD;
    while (r - l != 1) {
        if (l % 2 == 0) {
            res = (res + arr[l + 1]) % MOD;
        }
        if (r % 2 == 1) {
            res = (res + arr[r - 1]) % MOD;
        }

        l /= 2;
        r /= 2;
    }

    return res;
}

int main() {
    int n, k;
    cin >> n;
    cin >> k;

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        T[i][1] = 1;
    }

    while (B < n) {
        B *= 2;
    }

    for (int l = 2; l <= k; l++) {
        int *arr = init(2 * B);
        for (int i = 0; i < n; i++) {
            T[i][l] = query(arr, B + nums[i], 2 * B - 1);
            modify(arr, B + nums[i] - 1, T[i][l - 1]);
        }
    }

    int res = 0;
    for (int i = 0; i < n; i++) {
        res = (res + T[i][k]) % MOD;
    }

    cout << res;
}
