#include <iostream>
#include <vector>

using namespace std;

const int LIMIT = 1000001;

int n, m;
int products[LIMIT];
int days[LIMIT];
long long sumR[LIMIT]; // [0, 4, 7, 9, 10]
int maxLParz[LIMIT]; // [2, 2, -1, -1]
int maxLNparz[LIMIT]; // [3, 1, 1, -1]
int minRParz[LIMIT]; // [4, 4, 2, 2]
int minRNparz[LIMIT]; // [-1, 3, 3, 1]

void sums() {
    sumR[0] = 0;
    for (int i = 1; i <= n; i++) {
        sumR[i] = sumR[i - 1] + products[n - i];
    }
}

void maxL() {
    maxLParz[n - 1] = -1;
    maxLNparz[n - 1] = -1;

    for (int i = 0; i < n; i++) {
        if (products[i] % 2 == 0) {
            maxLParz[n - i - 2] = products[i];
            maxLNparz[n - i - 2] = maxLNparz[n - i - 1];
        }
        else {
            maxLParz[n - i - 2] = maxLParz[n - i - 1];
            maxLNparz[n - i - 2] = products[i];
        }
    }
}

void minR() {
    if (products[n - 1] % 2 == 0) {
        minRParz[0] = products[n - 1];
        minRNparz[0] = -1;
    }
    else {
        minRParz[0] = -1;
        minRNparz[0] = products[n - 1];
    }

    for (int i = n - 2; i >= 0; i--) {
        if (products[i] % 2 == 0) {
            minRParz[n - i - 1] = products[i];
            minRNparz[n - i - 1] = minRNparz[n - i - 2];
        }
        else {
            minRParz[n - i - 1] = minRParz[n - i - 2];
            minRNparz[n - i - 1] = products[i];
        }
    }
}


long long calcF(int k) {
    if (sumR[k] % 2 == 1)
        return sumR[k];

    long long res = -1;

    int l1 = maxLParz[k - 1], r1 = minRNparz[k - 1],
        l2 = maxLNparz[k - 1], r2 = minRParz[k - 1];

    pair<int,int> cand1 (l1, r1);
    pair<int,int> cand2 (l2, r2);

    vector<pair<int,int>> candidates;
    candidates.push_back(cand1);
    candidates.push_back(cand2);

    for(auto & candidate : candidates) {
        long long l = candidate.first;
        long long r = candidate.second;
        if (l != -1 && r != -1) {
            long long sumX = sumR[k] + l - r;
            res = max(res, sumX);
        }
    }

    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> products[i];
    }

    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> days[i];
    }

    sums();
    maxL();
    minR();

    for (int i = 0; i < m; i++) {
        cout << calcF(days[i]) << '\n';
    }
}
