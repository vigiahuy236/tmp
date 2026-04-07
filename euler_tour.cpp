/**
 *       author:  Vi Gia Huy
 *    Vi Gia Huy will win VOI 27
**/

#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 6;
int n, q;
long long a[N];
vector<int> adj[N];
int timer;
int in[N];
int out[N];
int elpos[N];

void dfs(int u, int p) {
    in[u] = ++timer;
    elpos[timer] = u;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
        }
    }
    out[u] = timer;
    return;
}

long long query(int u) {
    long long res = 0;
    for (int i = in[u]; i <= out[u]; i++) res += a[elpos[i]];
    return res;
}

void sol() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 1);

    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            int u;
            long long x; cin >> x;
            a[u] = x;
        }
        else {
            int u; cin >> u;
            cout << query(u) << "\n";
        }
    }

    return;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    // freopen("euler_tour.inp", "r", stdin);
    // freopen("euler_tour.out", "w", stdout);
    int T = 1;
    //cin >> T;
    while (T--) sol();
    return 0;
}