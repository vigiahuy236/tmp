/**
 *    author:  Vi Gia Huy
**/

#include <bits/stdc++.h>

using namespace std;

namespace directed_graph {
    const int N = 1e5 + 6;
    int n, m, _n, timer;
    int num[N], low[N], d[N];
    vector<int> adj[N], comp[N], g[N];
    stack<int> stk;
    void dfs_tarjan(int u) {
        num[u] = low[u] = ++timer;
        stk.push(u);
        for (int v : adj[u]) {
            if (num[v] != 0) low[u] = min(low[u], num[v]);
            else {
                dfs_tarjan(v);
                low[u] = min(low[u], low[v]);
            }
        }
        if (low[u] == num[u]) {
            _n++;
            int v = 0;
            while (u != v) {
                v = stk.top();
                num[v] = n + 1;
                d[v] = _n;
                g[_n].push_back(v);
                stk.pop();
            }
        }
        return;
    }

    void sol() {
        cin >> n >> m;
        while (m--) {
            int u, v; cin >> u >> v;
            adj[u].push_back(v);
        }
        for (int u = 1; u <= n; u++) if (num[u] == 0) dfs_tarjan(u);
        for (int u = 1; u <= n; u++) {
            for (int v : adj[u]) {
                if (d[u] == d[v]) continue;
                comp[d[u]].push_back(d[v]);
            }
        }
        for (int u = 1; u <= _n; u++) {
            vector<bool> check(_n + 1, false);
            vector<int> tmp;
            for (int v : comp[u]) {
                if (check[v]) continue;
                tmp.push_back(v);
                check[v] = true;
            }
            comp[u] = tmp;
        }
        cout << _n << "\n\n";
        for (int u = 1; u <= _n; u++) {
            cout << u << " | ";
            for (int v : g[u]) {
                cout << v << " ";
            }
            cout << "\n";
        }
        cout << "\n";
        for (int u = 1; u <= _n; u++) {
            for (int v : comp[u]) {
                cout << u << " " << v << "\n";
            }
        }
        return;
    }
};

namespace undirected_graph {
    const int N = 1e5 + 6;
    int n, m, _n, timer;
    int low[N], num[N], d[N];
    vector<int> g[N];
    vector<pair<int, int>> adj[N];
    vector<int> comp[N];
    stack<int> stk;

    void dfs_tarjan(int u, int p) {
        num[u] = low[u] = ++timer;
        stk.push(u);
        for (pair<int, int> tmp : adj[u]) {
            int v = tmp.first;
            int idx = tmp.second;
            if (idx == p) continue;
            if (num[v] != 0) low[u] = min(low[u], num[v]);
            else {
                dfs_tarjan(v, idx);
                low[u] = min(low[u], low[v]);
            }
        }
        if (num[u] == low[u]) {
            _n++;
            int v = 0;
            while (v != u) {
                v = stk.top();
                d[v] = _n;
                g[_n].push_back(v);
                stk.pop();
            }
        }
    }

    void sol() {
        cin >> n >> m;
        for (int i = 1; i <= m; i++) {
            int u, v; cin >> u >> v;
            adj[u].push_back(make_pair(v, i));
            adj[v].push_back(make_pair(u, i));
        }
        for (int u = 1; u <= n; u++) if (num[u] == 0) dfs_tarjan(u, 0);
        for (int u = 1; u <= n; u++) {
            for (pair<int, int> tmp : adj[u]) {
                int v = tmp.first;
                if (d[u] == d[v]) continue;
                comp[d[u]].push_back(d[v]);
            }
        }
        for (int u = 1; u <= _n; u++) {
            vector<bool> check(_n + 1, false);
            vector<int> tmp;
            for (int v : comp[u]) {
                if (check[v]) continue;
                tmp.push_back(v);
                check[v] = true;
            }
            comp[u] = tmp;
        }
        cout << _n << "\n\n";
        for (int u = 1; u <= _n; u++) {
            cout << u << " | ";
            for (int v : g[u]) {
                cout << v << " ";
            }
            cout << "\n";
        }
        cout << "\n";
        for (int u = 1; u <= _n; u++) {
            for (int v : comp[u]) {
                cout << u << " " << v << "\n";
            }
        }
        return;
    }
};

void sol() {
    directed_graph::sol();
    undirected_graph::sol();
    return;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    // freopen("condensation_graph.inp", "r", stdin);
    // freopen("condensation_graph.out", "w", stdout);
    sol();
    return 0;
}