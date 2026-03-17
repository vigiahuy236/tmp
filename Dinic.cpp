/**
 *       author:  Vi Gia Huy
 *    Vi Gia Huy will win VOI 27
**/

#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9 + 7;
const int N = 1e3 + 4;
int n, m, s, t;
vector<int> adj[N];
int c[N][N], f[N][N], d[N], maxflow;
int curidx[N];

void bfs() {
    fill(d, d + n + 1, INF);
    d[s] = 0;
    queue<int> bfsqu;
    bfsqu.push(s);
    while (!bfsqu.empty()) {
        int u = bfsqu.front();
        bfsqu.pop();
        for (int v : adj[u]) {
            if (d[v] != INF) continue;
            if (f[u][v] - c[u][v] == 0) continue;
            d[v] = d[u] + 1;
            bfsqu.push(v);
        }
    }
}

int dfs(int u, int curdelta) {
    if (curdelta == 0) return 0;
    if (u == t) return curdelta;
    for (; curidx[u] < adj[u].size(); curidx[u]++) {
        int v = adj[u][curidx[u]];
        if (d[v] != d[u] + 1) continue;
        if (f[u][v] == c[u][v]) continue;
        int delta = dfs(v, min(c[u][v] - f[u][v], curdelta));
        if (delta == 0) continue;
        f[u][v] += delta;
        f[v][u] -= delta;
        return delta;
    }
    return 0;
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

    while (true) {
        bfs();
        if (d[t] == INF) break;
        for (int i = 1; i <= n; i++) curidx[i] = 0;
        while (int delta = dfs(s, INF)) maxflow += delta;
    }

    cout << maxflow;

    return;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    freopen("Dinic.inp", "r", stdin);
    freopen("Dinic.out", "w", stdout);
    int T = 1;
    //cin >> T;
    while (T--) sol();
    return 0;
}