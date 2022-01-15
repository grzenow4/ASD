#include <iostream>

#define N_MAX 1000000
#define LOG_N 20

using namespace std;

int n, m;
int child_left[N_MAX], child_right[N_MAX], parent[N_MAX];
int depth[N_MAX], U[N_MAX][LOG_N];
int fardown[N_MAX], farup[N_MAX], far[N_MAX];

int get_dist(int a, int b);

int up(int v, int d) {
    if (d == 0) return v;

    int lvl = 0;
    while (d > 0) {
        if (d % 2 == 1)
            v = U[v][lvl];
        lvl++;
        d >>= 1;
    }
    return v;
}

int lca(int u, int v) {
    int du = depth[u], dv = depth[v];

    if (du < dv)
        v = up(v, dv - du);
    else if (du > dv)
        u = up(u, du - dv);

    if (u == v) return u;

    for (int i = LOG_N - 1; i >= 0; i--)
        if (U[u][i] != U[v][i]) {
            u = U[u][i];
            v = U[v][i];
        }

    return parent[u];
}

void DFS_down(int v, int dist) {
    depth[v] = dist;
    U[v][0] = parent[v];
    fardown[v] = v;

    for (int k = 1; k < LOG_N; k++)
        U[v][k] = U[U[v][k-1]][k - 1];

    int left = child_left[v];
    int right = child_right[v];

    if (left != -1)
        DFS_down(left, dist + 1);
    if (right != -1)
        DFS_down(right, dist + 1);

    if (left != -1 && depth[fardown[left]] > depth[fardown[v]])
        fardown[v] = fardown[left];
    if (right != -1 && depth[fardown[right]] > depth[fardown[v]])
        fardown[v] = fardown[right];
}

void DFS_up(int v) {
    farup[v] = v;

    if (v != 1) {
        int father = parent[v];
        int second_child = -1;

        if (child_left[father] != v)
            second_child = child_left[father];
        if (child_right[father] != v)
            second_child = child_right[father];

        int dist_father = get_dist(father, farup[father]) + 1;

        if (second_child == -1) {
            farup[v] = farup[father];
        }
        else {
            int dist_second_child = get_dist(second_child, fardown[second_child]) + 2;

            if (dist_father > dist_second_child)
                farup[v] = farup[father];
            else
                farup[v] = fardown[second_child];
        }
    }

    int left = child_left[v];
    int right = child_right[v];

    if (left != -1)
        DFS_up(left);
    if (right != -1)
        DFS_up(right);
}

void calc_far() {
    for (int v = 1; v <= n; v++)
        if (get_dist(v, fardown[v]) > get_dist(v, farup[v]))
            far[v] = fardown[v];
        else
            far[v] = farup[v];
}

int get_dist(int a, int b) {
    return depth[a] + depth[b] - 2 * depth[lca(a, b)];
}

int dist(int u, int d) {
    int v = far[u];
    int d_max = get_dist(u, v);

    if (d > d_max) return -1;

    int l = lca(u, v);
    int d1 = depth[u] - depth[l];

    if (d <= d1) return up(u, d);
    else return up(v, d_max - d);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    parent[1] = -1;
    for (int a, b, i = 1; i <= n; i++) {
        cin >> a >> b;
        if (a != -1)
            parent[a] = i;
        if (b != -1)
            parent[b] = i;
        child_left[i] = a;
        child_right[i] = b;
    }

    DFS_down(1, 0);
    DFS_up(1);
    calc_far();

    cin >> m;
    for (int a, d, i = 0; i < m; i++) {
        cin >> a >> d;
        cout << dist(a, d) << '\n';
    }
}
