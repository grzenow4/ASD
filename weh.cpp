#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

int const N_MAX = 1000;

int p, k, z, n, m;
unordered_set<int> zw;
vector<int> e, path, power;
vector<vector<int>> adj;

void add_edge(int a, int b) {
    adj[a].push_back(b);
    adj[b].push_back(a);
}

void bfs(int start, vector<int> & parent) {
    queue<int> q;

    parent = vector<int>(n, -1);
    vector<int> dist(n, N_MAX + 1);
    vector<bool> visited(n, false);

    visited[start] = true;
    dist[start] = 1;
    q.push(start);

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int u : adj[v]) {
            if (!visited[u]) {
                visited[u] = true;
                dist[u] = dist[v] + 1;
                parent[u] = v;
                q.push(u);
            }
        }
    }
}

void find_shortest_path(int start, int end) {
    vector<int> parent(n);
    bfs(start, parent);

    if (parent[end] == -1) return;

    int v = end;
    path.push_back(v);
    while (parent[v] != -1) {
        path.push_back(parent[v]);
        v = parent[v];
    }
}

void print_path() {
    for (auto i = path.size() - 1; i > 0; i--)
        cout << path[i] + 1 << " ";
    cout << path[0] + 1 << '\n';
}

int path_max_energy() {
    int en_max = 0;
    vector<vector<pair<int,bool>>> energies(path.size());

    vector<pair<int,bool>> start_energy;
    start_energy.emplace_back(p, false);
    energies[0] = start_energy;
    for (int i = 1; i < path.size(); i++) {
        bool vehicle_err = true;
        vector<bool> visited_false(p + 1, false);
        vector<bool> visited_true(p + 1, false);

        for (auto val : energies[i - 1]) {
            int en1 = val.first - k;

            if (en1 >= 0 && !visited_false[en1]) {
                vehicle_err = false;
                energies[i].emplace_back(en1, false);
                visited_false[en1] = true;

                int en2 = en1 + e[i];

                if (zw.find(en2) == zw.end() && en2 <= p && !visited_true[en2]) {
                    energies[i].emplace_back(en2, true);
                    visited_true[en2] = true;
                }
            }
        }

        if (vehicle_err) return -1;
    }

    for (auto val : energies[path.size() - 1])
        en_max = max(en_max, val.first);

    int curr_energy = en_max;

    for (auto i = 0; i < path.size(); i++) {
        for (auto & j : energies[path.size() - i - 1]) {
            if (j.first == curr_energy && j.second) {
                power.push_back(path[i]);
                curr_energy -= e[path.size() - i - 1];
                break;
            }
        }

        curr_energy += k;
    }

    return en_max;
}

void print_power() {
    for (auto i = power.size() - 1; i > 0; i--)
        cout << power[i] + 1 << " ";
    cout << power[0] + 1 << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> p >> k >> z;
    for (int i = 0; i < z; i++) {
        int w;
        cin >> w;
        zw.insert(w);
    }
    cin >> n >> m;
    adj = vector<vector<int>>(n);
    e = vector<int>(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        add_edge(a - 1, b - 1);
    }
    for (int i = 0; i < n; i++)
        cin >> e[i];

    int max_en = -1;
    find_shortest_path(0, n - 1);

    if (!path.empty()) max_en = path_max_energy();

    if (path.empty() || max_en == -1) {
        cout << -1 << '\n';
    }
    else {
        cout << path.size() << " " << max_en << " ";
        if (power.empty()) {
            cout << 0 << '\n';
            print_path();
            cout << '\n';
        }
        else {
            cout << power.size() << '\n';
            print_path();
            print_power();
        }
    }
}
