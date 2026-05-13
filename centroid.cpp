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

int findcentroid(int u, int p, int _sz) {
    for (int v : adj[u]) {
        if (v != p && !del[v]) {    
            if (sz[v] > _sz / 2) {
                return findcentroid(v, u, _sz);
            }
        }
    }
    return u;
}

void dnc(int u) {
    dfs(u, 0);
    int c = findcentroid(u, 0, sz[u]);
    del[c] = true;

    cout << "tree with root " << u << " have cetroid: " << c << "\n";

    /*
    process
    ...
    */

    for (int v : adj[c]) {
        if (!del[v]) {
            dnc(v);
        }
    }

    return;
}

void sol() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    dnc(1);

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