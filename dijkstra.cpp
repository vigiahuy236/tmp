/**
 *    author:  Vi Gia Huy
**/

#include <bits/stdc++.h>

using namespace std;

const long long inf = (1ll<<62);
const int N = 1e5 + 6;
int n, m, s, t;
long long d[N];
vector<pair<int, long long>> adj[N];
 
void sol() {
    cin >> n >> m >> s >> t;
    while (m--) {
        int u, v; cin >> u >> v;
        long long w; cin >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    for (int i = 1; i <= n; i++) d[i] = inf;
    d[s] = 0;
    pq.push({d[s], s});
    while (true) {
        if (pq.empty()) break;
        int u = pq.top().second;
        long long w = pq.top().first;
        pq.pop();
        // if (u == t) break;
        if (w > d[u]) continue;
        for (auto [v, c] : adj[u]) {
            if (w + c < d[v]) {
                d[v] = w + c;
                pq.push({d[v], v});
            }
        }
    }
    cout << d[t];
    return;
}
 
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    // freopen("dijkstra.inp", "r", stdin);
    // freopen("dijkstra.out", "w", stdout);
    sol();
    return 0;
}