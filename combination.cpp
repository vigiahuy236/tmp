/**
 *       author:  Vi Gia Huy
 *    Vi Gia Huy will win VOI 27
**/

#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;
const int N = 1e6 + 3;
long long fact[N], invfact[N];

long long modpow(long long x, long long y, const long long mod = MOD) {
    if (y == 0) return 1;
    if (y == 1) return x;

    long long res = modpow(x, y / 2, mod);

    res = (res * res) % MOD;

    if (y % 2 == 1) res = (res * x) % MOD;

    return res;
}

void precompute() {
    fact[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = (fact[i - 1] * 1ll * i) % MOD;
    }

    invfact[N - 1] = modpow(fact[N - 1], MOD - 2);
    for (int i = N - 2; i >= 0; i--) {
        invfact[i] = (invfact[i + 1] * 1ll * (i + 1)) % MOD;
    }

    return;
}

long long C(int _n, int _k) {
    if (_k > _n) return 0;
    return (fact[_n] * ((invfact[_k] * invfact[_n - _k]) % MOD)) % MOD;
}

void sol() {
    precompute();

    int n = 5;
    int k = 4;

    cout << C(n, k);

    return;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    // freopen("combination.inp", "r", stdin);
    // freopen("combination.out", "w", stdout);
    sol();
    return 0;
}