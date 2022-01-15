#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

// ------------------------- Reprezentacja drzewa treap ------------------------

typedef struct Treap *pTreap;

struct Treap {
    char value;
    int priority, count;
    char far_lval, far_rval, max_val;
    int far_lval_cnt, far_rval_cnt, max_cnt;
    bool rev;
    pTreap left, right;

    Treap(char val) : value(val), priority(rand()), left(NULL), right(NULL),
                      far_lval(val), far_rval(val), far_lval_cnt(1),
                      far_rval_cnt(1), max_val(val), max_cnt(1), rev(false) {}
};

int count(pTreap t) {
    return t ? t->count : 0;
}

void update_count(pTreap t) {
    if (t) t->count = count(t->left) + count(t->right) + 1;
}

void update_vals(pTreap t) {
    if (!t) return;

    if (t->left && t->right) { // Mamy dwoje dzieci.
        t->far_lval = t->left->rev ? t->left->far_rval : t->left->far_lval;
        t->far_lval_cnt = t->left->rev ? t->left->far_rval_cnt
                                       : t->left->far_lval_cnt;
        t->far_rval = t->right->rev ? t->right->far_lval : t->right->far_rval;
        t->far_rval_cnt = t->right->rev ? t->right->far_lval_cnt
                                        : t->right->far_rval_cnt;
        t->max_val = t->value;
        t->max_cnt = 1;

        char left_far_rval = t->left->rev ? t->left->far_lval
                                          : t->left->far_rval;
        int left_far_rval_cnt = t->left->rev ? t->left->far_lval_cnt
                                             : t->left->far_rval_cnt;
        char right_far_lval = t->right->rev ? t->right->far_rval
                                            : t->right->far_lval;
        int right_far_lval_cnt = t->right->rev ? t->right->far_rval_cnt
                                               : t->right->far_lval_cnt;

        if (t->far_lval_cnt == t->left->count && t->far_lval == t->value) {
            t->far_lval_cnt++;

            if (t->value == right_far_lval)
                t->far_lval_cnt += right_far_lval_cnt;
        }
        if (t->far_rval_cnt == t->right->count && t->far_rval == t->value) {
            t->far_rval_cnt++;

            if (t->value == left_far_rval)
                t->far_rval_cnt += left_far_rval_cnt;
        }

        if (t->value == left_far_rval) {
            t->max_cnt += left_far_rval_cnt;

            if (t->value == right_far_lval)
                t->max_cnt += right_far_lval_cnt;
        }
        else if (t->value == right_far_lval) {
            t->max_cnt += right_far_lval_cnt;
        }

        // Mamy aktualne dane, szukamy max.
        char cand;
        int cand_cnt;

        if (t->far_lval_cnt < t->far_rval_cnt) {
            cand = t->far_rval;
            cand_cnt = t->far_rval_cnt;
        }
        else {
            cand = t->far_lval;
            cand_cnt = t->far_lval_cnt;
        }

        if (cand_cnt < t->left->max_cnt) {
            cand = t->left->max_val;
            cand_cnt = t->left->max_cnt;
        }
        if (cand_cnt < t->right->max_cnt) {
            cand = t->right->max_val;
            cand_cnt = t->right->max_cnt;
        }

        if (cand_cnt > t->max_cnt) {
            t->max_val = cand;
            t->max_cnt = cand_cnt;
        }
    }
    else if (t->left) { // Mamy tylko lewe dziecko.
        t->far_lval = t->left->rev ? t->left->far_rval : t->left->far_lval;
        t->far_lval_cnt = t->left->rev ? t->left->far_rval_cnt
                                       : t->left->far_lval_cnt;
        t->far_rval = t->value;
        t->far_rval_cnt = 1;

        if (t->left->rev) {
            if (t->left->far_lval == t->value)
                t->far_rval_cnt += t->left->far_lval_cnt;
            if (t->left->far_rval_cnt == t->left->count &&
                t->left->far_rval == t->value)
                t->far_lval_cnt++;
        }
        else {
            if (t->left->far_rval == t->value)
                t->far_rval_cnt += t->left->far_rval_cnt;
            if (t->left->far_lval_cnt == t->left->count &&
                t->left->far_lval == t->value)
                t->far_lval_cnt++;
        }

        // Mamy aktualne dane, szukamy max.
        char cand;
        int cand_cnt;

        if (t->far_lval_cnt < t->far_rval_cnt) {
            cand = t->far_rval;
            cand_cnt = t->far_rval_cnt;
        }
        else {
            cand = t->far_lval;
            cand_cnt = t->far_lval_cnt;
        }

        if (cand_cnt > t->left->max_cnt) {
            t->max_val = cand;
            t->max_cnt = cand_cnt;
        }
        else {
            t->max_val = t->left->max_val;
            t->max_cnt = t->left->max_cnt;
        }
    }
    else if (t->right) { // Mamy tylko prawe dziecko.
        t->far_rval = t->right->rev ? t->right->far_lval : t->right->far_rval;
        t->far_rval_cnt = t->right->rev ? t->right->far_lval_cnt
                                        : t->right->far_rval_cnt;
        t->far_lval = t->value;
        t->far_lval_cnt = 1;

        if (t->right->rev) {
            if (t->right->far_rval == t->value)
                t->far_lval_cnt += t->right->far_rval_cnt;
            if (t->right->far_lval_cnt == t->right->count &&
                t->right->far_lval == t->value)
                t->far_rval_cnt++;
        }
        else {
            if (t->right->far_lval == t->value)
                t->far_lval_cnt += t->right->far_lval_cnt;
            if (t->right->far_rval_cnt == t->right->count &&
                t->right->far_rval == t->value)
                t->far_rval_cnt++;
        }

        // Mamy aktualne dane, szukamy max.
        char cand;
        int cand_cnt;

        if (t->far_lval_cnt < t->far_rval_cnt) {
            cand = t->far_rval;
            cand_cnt = t->far_rval_cnt;
        }
        else {
            cand = t->far_lval;
            cand_cnt = t->far_lval_cnt;
        }

        if (cand_cnt > t->right->max_cnt) {
            t->max_val = cand;
            t->max_cnt = cand_cnt;
        }
        else {
            t->max_val = t->right->max_val;
            t->max_cnt = t->right->max_cnt;
        }
    }
    else { // Nie mamy dzieci.
        t->far_lval = t->far_rval = t->max_val = t->value;
        t->far_lval_cnt = t->far_rval_cnt = t->max_cnt = 1;
    }
}

void heapify(pTreap t) {
    if (!t) return;
    pTreap max = t;
    if (t->left != NULL && t->left->priority > max->priority)
        max = t->left;
    if (t->right != NULL && t->right->priority > max->priority)
        max = t->right;
    if (max != t) {
        swap(t->priority, max->priority);
        heapify(max);
    }
}

pTreap build(char *tab, int n) {
    if (n == 0) return NULL;
    int mid = n / 2;
    pTreap t = new Treap(tab[mid]);
    t->left = build(tab, mid);
    t->right = build(tab + mid + 1, n - mid - 1);
    heapify(t);
    update_count(t);
    update_vals(t);
    return t;
}

void push(pTreap t) {
    if (t && t->rev) {
        t->rev = false;
        swap(t->left, t->right);
        if (t->left) t->left->rev ^= true;
        if (t->right) t->right->rev ^= true;
    }
}

void merge(pTreap &t, pTreap l, pTreap r) {
    push(l);
    push(r);
    if (!l || !r)
        t = l ? l : r;
    else if (l->priority > r->priority)
        merge(l->right, l->right, r), t = l;
    else
        merge(r->left, l, r->left), t = r;
    update_count(t);
    update_vals(t);
}

void split(pTreap t, pTreap &l, pTreap &r, int key, int add = 0) {
    if (!t) return void(l = r = NULL);
    push(t);
    int curr_key = add + count(t->left);
    if (key <= curr_key)
        split(t->left, l, t->left, key, add), r = t;
    else
        split(t->right, t->right, r, key, add + count(t->left) + 1), l = t;
    update_count(t);
    update_vals(t);
}

void reverse(pTreap t, int l, int r) {
    pTreap t1, t2, t3;
    split(t, t1, t2, l);
    split(t2, t2, t3, r - l + 1);
    t2->rev ^= true;
    merge(t, t1, t2);
    merge(t, t, t3);
}

void query(pTreap t, int l, int r) {
    pTreap t1, t2, t3;
    split(t, t1, t2, l);
    split(t2, t2, t3, r - l + 1);
    cout << t2->max_cnt << '\n';
    merge(t, t1, t2);
    merge(t, t, t3);
}

// ------------------------------ Operacje na DNA ------------------------------

void O(pTreap t, int j, int k) {
    reverse(t, j, k);
}

void P(pTreap t, int j, int k, int l) {
    if (j == l) return;
    O(t, j, k);
    if (l < j) {
        O(t, l, j - 1);
        O(t, l, k);
    }
    else {
        O(t, k + 1, k + l - j);
        O(t, j, k + l - j);
    }
}

void N(pTreap t, int j, int k) {
    query(t, j, k);
}

// ------------------------------------ Main -----------------------------------

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    char dna[n];

    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        dna[i] = c;
    }

    pTreap t = build(dna, n);

    for (int i = 0; i < m; i++) {
        char c;
        int j, k, l;
        cin >> c >> j >> k;

        switch (c) {
            case 'O':
                O(t, j - 1, k - 1);
                break;
            case 'P':
                cin >> l;
                P(t, j - 1, k - 1, l - 1);
                break;
            case 'N':
                N(t, j - 1, k - 1);
                break;
            default:
                break;
        }
    }
}
