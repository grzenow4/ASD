#include <iostream>

using namespace std;

const int LIMIT = 1000000;
char str[LIMIT];
int n = 0;

int minimalneLPrim(const char t[]) {
    char prev_c = '\0';
    int prev_j = -1;
    int l = LIMIT;

    for (int j = 0; j < n; j++) {
        if (t[j] != '*') {
            if (prev_c != '\0' && t[j] != prev_c) {
                l = min(l, j + 1 - prev_j);
            }
            prev_c = t[j];
            prev_j = j;
        }
    }

    if (l == LIMIT)
        return n + 1;

    return l;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> str;

    for (int i = 0; str[i] != 0; i++) {
        n++;
    }

    int l = minimalneLPrim(str);
    cout << n - l + 2;
}
