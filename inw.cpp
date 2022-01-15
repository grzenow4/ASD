#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

#define MAX_N 1e6 + 1

using namespace std;

int n;
vector<bool> visited(MAX_N, false);
vector<int> id(MAX_N);
vector<vector<int>> G(MAX_N);

void add_edge(int a, int b) {
    G[a].push_back(b);
    G[b].push_back(a);
}

void DFS(int v, int idx) {
    visited[v] = true;
    id[v] = idx;
    for (auto u: G[v]) {
        if (!visited[u])
            DFS(u, idx);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;

    stack<int> s;

    for (int i = 0; i < n; i++) {
        int x, y, max;
        cin >> y;
        y--;
        max = y;

        if (!s.empty()) {
            while (!s.empty() && s.top() > y) {
                add_edge(s.top(), y);
                if (s.top() > max)
                    max = s.top();
                s.pop();
            }
        }

        s.push(max);
    }

    int bucket_id = 0;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            DFS(i, bucket_id);
            bucket_id++;
        }
    }

    vector<vector<int>> buckets(bucket_id);
    for (int i = 0; i < n; i++) {
        buckets[id[i]].push_back(i + 1);
    }

    for (int i = 0; i < bucket_id; i++) {
        sort(buckets[i].begin(), buckets[i].end());
    }

    cout << bucket_id << '\n';
    for (const auto& bucket : buckets) {
        cout << bucket.size() << " ";
        for (auto v : bucket)
            cout << v << " ";
        cout << '\n';
    }

    return 0;
}
