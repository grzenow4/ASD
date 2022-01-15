#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    bool czy_zagra = true;

    int n, m;
    cin >> n;
    cin >> m;

    long long players[n];
    for (int i = 0; i < n; i++) {
        players[i] = 0;
    }

    for (int match = 0; match < m; match++) {
        for (int i = 0; i < n / 2; i++) {
            int curr_player;
            cin >> curr_player;
            players[curr_player - 1] = players[curr_player - 1] | 1LL << (match + 1);
        }

        for (int i = n / 2; i < n; i++) {
            int dummy;
            cin >> dummy;
        }
    }

    sort(players, players + n);

    for (int i = 0; i < n - 1; i++) {
        if (players[i] == players[i + 1]) {
            czy_zagra = false;
        }
    }

    if (czy_zagra)
        cout << "TAK";
    else
        cout << "NIE";
}
