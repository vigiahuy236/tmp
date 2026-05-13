/**
 *       author:  Vi Gia Huy
 *    Vi Gia Huy will win VOI 27
**/

#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 3;
int n;
vector<int> adj[N];
int sz[N];
bool del[N];

void dfs(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v != p && !del[v]) {
            dfs(v, u);
            sz[u] += sz[v];
        }
    }
    return;
}

int findcentroid(int u, int p) {
    for (int v : adj[u]) {
        if (v != p && !del[v]) {    
            if (sz[v] > n / 2) {
                return findcentroid(v, u);
            }
        }
    }
    return u;
}

void sol() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    dfs(1, 1);

    cout << findcentroid(1, 1) << "\n";

    return;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    freopen("centroid.inp", "r", stdin);
    // freopen("centroid.out", "w", stdout);
    int T = 1;
    //cin >> T;
    while (T--) sol();
    return 0;
}