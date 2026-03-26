/**
 *       author:  Vi Gia Huy
 *    Vi Gia Huy will win VOI 27
**/

#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 6;
int n, m;
long long total;

struct DSU {
    vector<int> par, freq;
    vector<vector<int>> vec;
    DSU(int _n = 0) {
        init(_n);
    }
    void init(int _n) {
        par.assign(_n + 1, 0);
        freq.assign(_n + 1, 1);
        vec.assign(_n + 1, vector<int>());
        for (int i = 1; i <= _n; i++) par[i] = i;
        for (int i = 1; i <= _n; i++) vec[i].push_back(i);
    }
    int acs(int u) {
        if (par[u] == u) return u;
        return par[u] = acs(par[u]);
    }
    bool join(int u, int v) {
        u = acs(u);
        v = acs(v);
        if (u == v) return false;
        if (vec[u].size() < vec[v].size()) swap(u, v);
        par[v] = u;
        freq[u] += freq[v];
        for (int x : vec[v]) vec[u].push_back(x);
        return true;
    }
    int cnt(int u) {
        return freq[acs(u)];
    }
    bool check(int u, int v) {
        return acs(u) == acs(v);
    }
};

struct Edge {
    int u, v; 
    long long w;
    Edge(int _u, int _v, long long _w): u(_u), v(_v), w(_w) {};
};

vector<Edge> edges;

void sol() {
    cin >> n >> m;
    while (m--) {
        int u, v; cin >> u >> v;
        long long w; cin >> w;
        edges.push_back({u, v, w});
    }

    sort(edges.begin(), edges.end(), [&](Edge x, Edge y) {
        return x.w < y.w;
    });

    DSU dsu(n);

    for (Edge it : edges) {
        if (!dsu.join(it.u, it.v)) continue;
        total += it.w;
    }

    cout << total;

    return;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    // freopen("Kruskal.inp", "r", stdin);
    // freopen("Kruskal.out", "w", stdout);
    int T = 1;
    //cin >> T;
    while (T--) sol();
    return 0;
}