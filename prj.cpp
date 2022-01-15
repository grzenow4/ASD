#include <functional>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;

    cin >> n >> m >> k;

    auto p = vector<int>(n);
    auto edges_in = vector<int>(n, 0);
    auto adj = vector<set<int>>(n);

    for (int i = 0; i < n; i++) {
        cin >> p[i];
        adj[i] = set<int>();
    }

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[b - 1].insert(a - 1);
        edges_in[a - 1]++;
    }

    for (int i = 0; i < n; i++)
        if (edges_in[i] == 0) {
            q.push({p[i], i});
            edges_in[i] = -1;
        }

    int max = 0;
    while (k > 0) {
        auto v = q.top();
        q.pop();

        if (v.first > max)
            max = v.first;

        for (int w : adj[v.second]) {
            edges_in[w]--;

            if (edges_in[w] == 0) {
                q.push({p[w], w});
                edges_in[w] = -1;
            }
        }

        k--;
    }

    cout << max << "\n";
}
