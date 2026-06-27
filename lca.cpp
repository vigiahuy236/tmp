/**
 *    author:  Vi Gia Huy
**/

#include <bits/stdc++.h>

using namespace std;

const int N = 3e5 + 4;
int n, root, a, b;
vector<int> adj[N];

namespace algo1 {
    int par[N];
    int high[N];

    void dfslca(int u) {
        for (int v : adj[u]) {
            if (v == par[u]) continue;
            par[v] = u;
            high[v] = high[u] + 1;
            dfslca(v);
        }
    }

    void setup(int root) {
        par[root] = root;
        high[root] = 0;
        dfslca(root);
        return;
    }

    int lca(int u, int v) {
        if (high[u] < high[v]) swap(v, u);
        while (high[u] > high[v]) u = par[u];
        if (u == v) return u;
        while (u != v) {
            u = par[u];
            v = par[v]; 
        }
        return u;
    }

    void sol() {
        setup(root);
        cout << lca(a, b);
    }
}

namespace algo2 {
    const int LOG = 20;
    int high[N];
    int par[N][LOG];

    void dfslca(int u) {
        for (int v : adj[u]) {
            if (v == par[u][0]) continue;
            par[v][0] = u;
            high[v] = high[u] + 1;
            dfslca(v);
        }
    }

    void setup(int root) {
        par[root][0] = root;
        high[root] = 0;
        dfslca(root);
        for (int j = 1; j < LOG; j++) {
            for (int i = 1; i <= n; i++) {
                par[i][j] = par[par[i][j - 1]][j - 1];
            }
        }
        high[0] = -1;
    }

    int lca(int u, int v) {
        if (high[u] < high[v]) swap(u, v);
        for (int i = LOG - 1; i >= 0; i--) {
            if (high[par[u][i]] >= high[v]) {
                u = par[u][i];
            }
        }
        if (u == v) return u;
        for (int i = LOG - 1; i >= 0; i--) {
            if (par[u][i] == par[v][i]) continue;
            u = par[u][i];
            v = par[v][i];
        }
        return par[u][0];
    }

    void sol() {
        setup(root);
        cout << lca(a, b);
    }
}

void sol() {
    cin >> n >> root;
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    cin >> a >> b;
    algo1::sol();
    algo2::sol();
    return;
} 

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    // freopen("lca.inp", "r", stdin);
    // freopen("lca.out", "w", stdout);
    sol();
    return 0;
}