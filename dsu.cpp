/**
 *    author:  Vi Gia Huy
**/

#include <bits/stdc++.h>

using namespace std;

struct DSU {
    vector<int> par;
    vector<int> sz;
    vector<vector<int>> vec;

    DSU(int _n = 0) {
        init(_n);
    }

    void init(int _n) {
        par.assign(_n + 1, 0);
        sz.assign(_n + 1, 1);
        vec.assign(_n + 1, vector<int>());
        for (int i = 1; i <= _n; i++) par[i] = i;
        for (int i = 1; i <= _n; i++) vec[i].push_back(i);

        return;
    }

    int acs(int u) {
        if (par[u] == u) return u;
        return par[u] = acs(par[u]);
    }

    bool join(int u, int v) {
        u = acs(u);
        v = acs(v);

        if (u == v) return false;

        if (sz[u] < sz[v]) swap(u, v);

        par[v] = u;
        sz[u] += sz[v];
        for (int x : vec[v]) vec[u].push_back(x);

        return true;
    }

    int cnt(int u) {
        return sz[acs(u)];
    }

    bool check(int u, int v) {
        return acs(u) == acs(v);
    }
};

void sol() {
    int n, q; cin >> n >> q;

    DSU dsu(n);

    while (q--) {
        char type; cin >> type;
        if (type == '1') {
            int u, v; cin >> u >> v;

            dsu.join(u, v);
        } 
        else if (type == '2') {
            int u; cin >> u;

            cout << dsu.cnt(u) << "\n";
        } 
        else if (type == '3') {
            int u; cin >> u;

            int ru = dsu.acs(u);

            for (int x : dsu.vec[ru]) cout << x << " ";

            cout << "\n"; 
        } 
        else {
            int u, v; cin >> u >> v;

            if (dsu.check(u, v)) cout << "YES\n";

            else cout << "NO\n";
        }
    }
    
    return;
}
 
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    // freopen("dsu.inp", "r", stdin);
    // freopen("dsu.out", "w", stdout);
    sol();
    return 0;
}