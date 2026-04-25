/**
 *       author:  Vi Gia Huy
 *    Vi Gia Huy will win VOI 27
**/

#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 6;
int n, m;
vector<int> adj[N];
int in[N];
queue<int> qu;
vector<int> topo;

void sol() {
    cin >> n >> m;
    while (m--) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);

        in[v]++;
    }

    for (int i = 1; i <= n; i++) {
        if (in[i] == 0) {
            qu.push(i);
        }
    }

    while (!qu.empty()) {
        int u = qu.front();
        qu.pop();
        topo.push_back(u);
        for (int v : adj[u]) {
            in[v]--;
            if (in[v] == 0) qu.push(v);
        }
    }

    for (int u : topo) cout << u << " ";

    return;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    freopen("topo_sort.inp", "r", stdin);
    freopen("topo_sort.out", "w", stdout);
    int T = 1;
    //cin >> T;
    while (T--) sol();
    return 0;
}