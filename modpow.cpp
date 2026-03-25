/**
 *       author:  Vi Gia Huy
 *    Vi Gia Huy will win VOI 27
**/

#include <bits/stdc++.h>

using namespace std;

long long modpow(long long a, long long b, long long mod) {
    if (b == 0) return 1;
    long long p = modpow(a, b / 2, mod);
    p = (p * p) % mod;
    if (b & 1) p = (p * a) % mod;
    return p; 
}

void sol() {
    long long a, b, c; cin >> a >> b >> c;
    cout << modpow(a, b, c);
    return;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    // freopen("modpow.inp", "r", stdin);
    // freopen("modpow.out", "w", stdout);
    int T = 1;
    //cin >> T;
    while (T--) sol();
    return 0;
}