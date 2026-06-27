/**
 *       author:  Vi Gia Huy
 *    Vi Gia Huy will win VOI 27
**/

#include <bits/stdc++.h>

using namespace std;

const long long INF = (1ll<<60);
const int N = 1e5 + 6;
int n, q;
long long a[N];
vector<int> adj[N];
int timer;
int par[N];
int hldpos[N];
int sz[N];
int high[N];
int heavy[N];
int head[N];
long long st[4 * N];

void dfs(int u) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v == par[u]) continue;
        high[v] = high[u] + 1;
        par[v] = u;
        dfs(v);
        if (sz[v] > sz[heavy[u]]) heavy[u] = v;
        sz[u] += sz[v];
    }
    return;
}

void hld(int u, int o) {
    head[u] = o;
    hldpos[u] = ++timer;
    if (heavy[u] != 0) hld(heavy[u], o);
    for (int v : adj[u]) {
        if (v != par[u] && v != heavy[u]) {
            hld(v, v);
        }
    }
    return;
}

void update(int id, int l, int r, int pos, long long val) {
    if (r < pos || pos < l) return;
    if (l == r) {
        st[id] = val;
        return;
    }
    int mid = (l + r) / 2;
    update(2 * id, l, mid, pos, val);
    update(2 * id + 1, mid + 1, r, pos, val);
    st[id] = max(st[2 * id], st[2 * id + 1]);
    return;
}

long long get(int id, int l, int r, int u, int v) {
    if (v < l || r < u) return -INF;
    if (u <= l && r <= v) return st[id];
    int mid = (l + r) / 2;
    return max(get(2 * id, l, mid, u, v), get(2 * id + 1, mid + 1, r, u, v));  
}

long long query(int u, int v) {
    long long res = -INF;
    while (head[u] != head[v]) {
        if (high[head[u]] > high[head[v]]) swap(u, v);
        res = max(res, get(1, 1, n, hldpos[head[v]], hldpos[v]));
        v = par[head[v]];
    }
    if (high[u] > high[v]) swap(u, v);
    res = max(res, get(1, 1, n, hldpos[u], hldpos[v]));
    return res;
}

void sol() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1);
    hld(1, 1);
    for (int i = 1; i <= n; i++) update(1, 1, n, hldpos[i], a[i]);

    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            int u; cin >> u;
            long long x; cin >> x;
            update(1, 1, n, hldpos[u], x);
        }
        else {
            int u, v; cin >> u >> v;
            cout << query(u, v) << "\n";
        }
    }

    return;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    // freopen("HLD.inp", "r", stdin);
    // freopen("HLD.out", "w", stdout);
    sol();
    return 0;
}