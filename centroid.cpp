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
vector<int> centroid_tree[N];

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

int find_centroid(int u, int p, int _sz) {
    for (int v : adj[u]) {
        if (v != p && !del[v]) {    
            if (sz[v] > _sz / 2) {
                return find_centroid(v, u, _sz);
            }
        }
    }
    return u;
}

void dnc(int u) {
    dfs(u, 0);
    int c = find_centroid(u, 0, sz[u]);

    cout << "tree with root " << u << " have cetroid: " << c << "\n";

    /*
    process
    ...
    */

    del[c] = true;
    for (int v : adj[c]) {
        if (!del[v]) {
            dnc(v);
        }
    }

    return;
}

void build_centroid_tree(int u, int p) {
    dfs(u, 0);
    if (sz[u] == 1) {
        centroid_tree[u].push_back(p);
        centroid_tree[p].push_back(u);
        return;
    }

    int c = find_centroid(u, 0, sz[u]);
    del[c] = true;

    centroid_tree[c].push_back(p);
    centroid_tree[p].push_back(c);

    for (int v : adj[c]) {
        if (!del[v]) {
            build_centroid_tree(v, c);
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

    for (int i = 1; i <= n; i++) del[i] = false;

    build_centroid_tree(1, 0);

    cout << "\ncentroid tree:\n";
    for (int u = 1; u <= n; u++) {
        for (int v : centroid_tree[u]) {
            if (u < v) {
                cout << u << " " << v << "\n";   
            }
        }
    }

    return;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    // freopen("centroid.inp", "r", stdin);
    // freopen("centroid.out", "w", stdout);
    int T = 1;
    //cin >> T;
    while (T--) sol();
    return 0;
}