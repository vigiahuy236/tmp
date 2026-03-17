/**
 *       author:  Vi Gia Huy
 *    Vi Gia Huy will win VOI 27
**/

#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 4;
int n, m, s, t;
vector<int> adj[N];
int c[N][N], f[N][N], trace[N], maxflow;

void bfs() {
    fill(trace, trace + n + 1, 0);
    trace[s] = -1;
    queue<int> bfsqu;
    bfsqu.push(s);
    while (!bfsqu.empty()) {
        int u = bfsqu.front();
        bfsqu.pop();
        for (int v : adj[u]) {
            if (trace[v] != 0) continue;
            if (f[u][v] - c[u][v] == 0) continue;
            trace[v] = u;
            bfsqu.push(v);
        }
    }
}

void incflow() {
    int delta = INT_MAX;
    int u = t;
    while (u != s) {
        int v = trace[u];
        delta = min(delta, c[v][u] - f[v][u]);
        u = v;
    }
    maxflow += delta;
    u = t;
    while (u != s) {
        int v = trace[u];
        f[v][u] += delta;
        f[u][v] -= delta;
        u = v;
    }
}

void sol() {
    cin >> n >> m >> s >> t;
    while (m--) {
        int u, v; cin >> u >> v;
        cin >> c[u][v];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    maxflow = 0;

    do {
        bfs();
        if (trace[t]) incflow();
    } while (trace[t]);

    cout << maxflow;

    return;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    // freopen("Edmonds-Karp.inp", "r", stdin);
    // freopen("Edmonds-Karp.out", "w", stdout);
    int T = 1;
    //cin >> T;
    while (T--) sol();
    return 0;
}