/**
 *       author:  Vi Gia Huy
 *    Vi Gia Huy will win VOI 27
**/

#include <bits/stdc++.h>

using namespace std;

const long long INF = (1ll<<60);
const int N = 1e5 + 6;
int n, m;
vector<pair<int, long long>> adj[N];
long long dist[N];

long long prim(int s) {
    long long res = 0;
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    for (int i = 1; i <= n; i++) dist[i] = INF;
    dist[s] = 0;
    pq.push(make_pair(0, s));
    while (!pq.empty()) {
        int u = pq.top().second;
        long long d = pq.top().first;
        pq.pop();
        if (d != dist[u]) continue;
        res += dist[u];
        dist[u] = -INF;
        for (pair<int, long long> it : adj[u]) {
            int v = it.first;
            long long w = it.second;
            if (dist[v] > w) {
                dist[v] = w;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    return res;
}

void sol() {
    cin >> n >> m;
    while (m--) {
        int u, v; cin >> u >> v;
        long long w; cin >> w;
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }

    cout << prim(1);

    return;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    // freopen("Prim.inp", "r", stdin);
    // freopen("Prim.out", "w", stdout);
    sol();
    return 0;
}