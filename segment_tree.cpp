/**
 *    author:  Vi Gia Huy
**/

#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 6;
const long long INF = 1e18;

struct Node {
    long long mx;
    long long lazy;
    
    Node() {
        mx = -INF;
        lazy = 0;
    }

    Node operator + (const Node& other) {
        Node res;
        res.mx = max(mx, other.mx);
        return res;
    }
};

struct Segtree {
    static inline Node base;
    vector<Node> st;

    Segtree(int n = 0) {
        init(n);
    } 

    void init(int n) {
        st.assign(4 * n, base);
    }

    void push(int id) {
        if (st[id].lazy != 0) {
            st[2 * id].mx += st[id].lazy;
            st[2 * id].lazy += st[id].lazy;

            st[2 * id + 1].mx += st[id].lazy;
            st[2 * id + 1].lazy += st[id].lazy;

            st[id].lazy = 0;
        }
        return;
    }

    void build(int id, int l, int r, long long a[]) {
        if (l == r) {
            st[id].mx = a[l];
            return;
        }

        int mid = (l + r) / 2;

        build(2 * id, l, mid, a);
        build(2 * id + 1, mid + 1, r, a);

        st[id] = st[2 * id] + st[2 * id + 1];

        return;
    }

    void update(int id, int l, int r, int u, int v, long long val) {
        if (v < l || r < u) return;
        if (u <= l && r <= v) {
            st[id].mx += val;
            st[id].lazy += val;

            return;
        }

        push(id);

        int mid = (l + r) / 2;

        update(2 * id, l, mid, u, v, val);
        update(2 * id + 1, mid + 1, r, u, v, val);

        st[id] = st[2 * id] + st[2 * id + 1];

        return;
    }

    long long query(int id, int l, int r, int u, int v) {
        if (v < l || r < u) return -INF;
        if (u <= l && r <= v) return st[id].mx;
        push(id);

        int mid = (l + r) / 2;

        return max(query(2 * id, l, mid, u, v), query(2 * id + 1, mid + 1, r, u, v));
    }
};

void sol() {
    int n, q; cin >> n >> q;

    long long a[N];
    for (int i = 1; i <= n; i++) cin >> a[i];

    Segtree seg(n);
    seg.build(1, 1, n, a);

    while (q--) {
        char type; cin >> type;
        if (type == '?') {
            int l, r; cin >> l >> r;
            cout << seg.query(1, 1, n, l, r) << "\n";
        } 
        else {
            int l, r; cin >> l >> r;
            long long k; cin >> k;
            seg.update(1, 1, n, l, r, k);
        } 
    }

    return;
}
 
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    // freopen("segment_tree.inp", "r", stdin);
    // freopen("segment_tree.out", "w", stdout);
    int T = 1;
    //cin >> T;
    while (T--) sol();
    return 0;
}