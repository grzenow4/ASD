#include <iostream>
#include <vector>

using namespace std;

int n, m, p1 = 47, p2 = 37, q1 = 1e9, q2 = 2126969212;
vector<int> s;
vector<long long> hash1, hash2, p1_power, p2_power;

void calc_power() {
    p1_power[0] = p2_power[0] = 1;

    for (int i = 1; i <= n; i++) {
        p1_power[i] = (p1_power[i - 1] * p1) % q1;
        p2_power[i] = (p2_power[i - 1] * p2) % q2;
    }
}

void calc_hash() {
    hash1[n] = hash2[n] = 0;

    for (int i = n - 1; i >= 0; i--) {
        hash1[i] = (s[i] + hash1[i + 1] * p1) % q1;
        hash2[i] = (s[i] + hash2[i + 1] * p2) % q2;
    }
}

long long hash1_query(int i, int j) {
    return ((hash1[i] - hash1[j + 1] * p1_power[j - i + 1]) % q1 + q1) % q1;
}

long long hash2_query(int i, int j) {
    return ((hash2[i] - hash2[j + 1] * p2_power[j - i + 1]) % q2 + q2) % q2;
}

int lcp(int a, int b, int c, int d) {
    int l = 0, r = min(b - a + 1, d - c + 1);
    while (l < r) {
        int mid = (l + r) / 2;
        if (hash1_query(a, a + mid) == hash1_query(c, c + mid) &&
            hash2_query(a, a + mid) == hash2_query(c, c + mid))
            l = mid + 1;
        else
            r = mid;
    }
    return l;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    hash1 = hash2 = vector<long long>(n + 1);
    p1_power = p2_power = vector<long long>(n + 1);

    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        s.push_back(c);
    }

    calc_power();
    calc_hash();

    for (int i = 0; i < m; i++) {
        int a, b, c, d, d1, d2;
        cin >> a >> b >> c >> d;
        a--; b--; c--; d--;
        d1 = b - a + 1;
        d2 = d - c + 1;

        int idx = lcp(a, b, c, d);

        if (idx == d1 && idx == d2) {
            cout << "=\n";
        }
        else if (idx == min(d1, d2)) {
            d1 > d2 ? cout << ">\n" : cout << "<\n";
        }
        else {
            s[a + idx] > s[c + idx] ? cout << ">\n" : cout << "<\n";
        }
    }
}
