#include <iostream>

using namespace std;

int n, m, tree_size;
int B = 1;
pair<int,char> *tree;

pair<int,int> interval(int v) {
    int l = v;
    int r = v;

    while (l < B) {
        l *= 2;
        r = 2 * r + 1;
    }

    return make_pair(l, r);
}

void push_down(int v) {
    pair<int,int> p = interval(v);
    int l = p.first;
    int r = p.second;

    if (l == r)
        return;

    int left = 2 * v;
    int right = left + 1;

    char color = tree[v].second;
    tree[left].second = color;
    tree[right].second = color;
    if (color == 'C') {
        tree[left].first = tree[right].first = 0;
    }
    else {
        tree[left].first = tree[right].first = tree[v].first / 2;
    }
}

void update(int v, int a, int b, char c) {
    pair<int,int> p = interval(v);
    int l = p.first;
    int r = p.second;

    int left = 2 * v;
    int right = left + 1;

    if (r < a || l > b) {
        return;
    }
    else if (l >= a && r <= b) {
        tree[v].second = c;
        if (c == 'B')
            tree[v].first = r - l + 1;
        else
            tree[v].first = 0;
    }
    else {
        char color = tree[v].second;
        if (color == 'B' || color == 'C')
            push_down(v);
        update(left, a, b, c);
        update(right, a, b, c);
        if (tree[left].second == tree[right].second)
            tree[v].second = tree[left].second;
        else
            tree[v].second = 'M';
        tree[v].first = tree[left].first + tree[right].first;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;

    while (B < n) {
        B *= 2;
    }
    tree_size = 2 * B;

    tree = new pair<int,char>[tree_size];
    for (int i = 0; i < tree_size; i++) {
        tree[i] = make_pair(0, 'C');
    }

    for (int i = 0; i < m; i++) {
        int a, b;
        char c;
        cin >> a >> b >> c;
        update(1, B + a - 1, b + B - 1, c);
        cout << tree[1].first << '\n';
    }
}
