#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

#define MAX_DIST 2e9

using namespace std;

int n;
vector<pair<pair<int,int>, int>> plansza;
vector<set<pair<int,int>>> wadj(n);

bool sort_by_first(const pair<pair<int,int>, int> &a, const pair<pair<int,int>, int> &b) {
    if (a.first.first == b.first.first)
        return a.first.second < b.first.second;

    return (a.first.first < b.first.first);
}

bool sort_by_second(const pair<pair<int,int>, int> &a, const pair<pair<int,int>, int> &b) {
    if (a.first.second == b.first.second)
        return a.first.first < b.first.first;

    return (a.first.second < b.first.second);
}

int get_dist(const pair<int,int> &a, const pair<int,int> &b) {
    return min(abs(a.first - b.first), abs(a.second - b.second));
}

void get_adjacent() {
    // Sortowanie po x i wpisanie x-sąsiadów.
    sort(plansza.begin(), plansza.end(), sort_by_first);

    wadj[plansza[0].second].insert({plansza[1].second, get_dist(plansza[0].first, plansza[1].first)});
    for (int i = 1; i < n - 1; i++) {
        wadj[plansza[i].second].insert({plansza[i - 1].second, get_dist(plansza[i].first, plansza[i - 1].first)});
        wadj[plansza[i].second].insert({plansza[i + 1].second, get_dist(plansza[i].first, plansza[i + 1].first)});
    }
    wadj[plansza[n - 1].second].insert({plansza[n - 2].second, get_dist(plansza[n - 1].first, plansza[n - 2].first)});

    // Sortowanie po y i wpisanie y-sąsiadów.
    sort(plansza.begin(), plansza.end(), sort_by_second);

    wadj[plansza[0].second].insert({plansza[1].second, get_dist(plansza[0].first, plansza[1].first)});
    for (int i = 1; i < n - 1; i++) {
        wadj[plansza[i].second].insert({plansza[i - 1].second, get_dist(plansza[i].first, plansza[i - 1].first)});
        wadj[plansza[i].second].insert({plansza[i + 1].second, get_dist(plansza[i].first, plansza[i + 1].first)});
    }
    wadj[plansza[n - 1].second].insert({plansza[n - 2].second, get_dist(plansza[n - 1].first, plansza[n - 2].first)});
}

vector<int> dijkstra(int source) {
    vector<int> dist(n, MAX_DIST);
    vector<bool> visited(n, false);
    dist[source] = 0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> q;
    q.push({dist[source], source});
    while (!q.empty()) {
        auto [d, v] = q.top(); q.pop();
        if (visited[v]) continue;
        visited[v] = true;
        for (const auto &[u, edge_w]: wadj[v]) {
            if (d + edge_w < dist[u]) {
                dist[u] = d + edge_w;
                q.push({dist[u], u});
            }
        }
    }
    return dist;
}

void wypisz_stan() {
    cout << "Graf sąsiedztwa:\n";
    for (int i = 0; i < n; i++) {
        cout << "Sąsiedzi wierzchołka " << i + 1 << " to:\n";

        for (auto &j : wadj[i]) {
            cout << j.first + 1 << " w odległości " << j.second << "; ";
        }
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    plansza = vector<pair<pair<int,int>, int>>(n);
    wadj = vector<set<pair<int,int>>>(n);

    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        plansza[i] = { {x, y}, i};
    }

    get_adjacent();
    auto dist = dijkstra(0);
    cout << dist[n - 1];
}
