/**
 *       author:  Vi Gia Huy
 *    Vi Gia Huy will win VOI 27
**/

#include <bits/stdc++.h>

using namespace std;

struct Hash {
    static const long long MOD1 = 1e9 + 7; 
    static const long long MOD2 = 1e9 + 9;
    static inline long long BASE1 = 311;
    static inline long long BASE2 = 313;
    static inline vector<long long> hashpow1 = {1};
    static inline vector<long long> hashpow2 = {1};
    vector<long long> hash1;
    vector<long long> hash2;

    static void init_base() {
        if (hashpow1.size() > 1) return;
        mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
        BASE1 = uniform_int_distribution<long long>(311, 1000)(rng);
        BASE2 = uniform_int_distribution<long long>(313, 1000)(rng);
    }

    Hash(const string& s) {
        init_base();
        int n = s.size();
        hash1.assign(n + 1, 0);
        hash2.assign(n + 1, 0);

        while (hashpow1.size() <= n) {
            hashpow1.push_back((hashpow1.back() * BASE1) % MOD1);
            hashpow2.push_back((hashpow2.back() * BASE2) % MOD2);
        }

        for (int i = 0; i < n; i++) {
            hash1[i + 1] = (hash1[i] * BASE1 + (long long)s[i]) % MOD1;
            hash2[i + 1] = (hash2[i] * BASE2 + (long long)s[i]) % MOD2;
        }
    }

    long long get(int l, int r) {
        long long res1 = (hash1[r + 1] - hash1[l] * hashpow1[r - l + 1] % MOD1 + MOD1) % MOD1;
        long long res2 = (hash2[r + 1] - hash2[l] * hashpow2[r - l + 1] % MOD2 + MOD2) % MOD2;
        return (res1 << 32) | res2; 
    }
};

int compare(string s1, Hash hashs1, int l1, int r1, string s2, Hash hashs2, int l2, int r2) {
    if (hashs1.get(l1, r1) == hashs2.get(l2, r2)) return true;
    int len = 0;
    int l = 0;
    int r = min(r1 - l1 + 1, r2 - l2 + 1);
    while (l <= r) {
        int mid = (l + r) / 2;
        if (hashs1.get(l1, l1 + mid - 1) == hashs2.get(l2, l2 + mid - 1)) {
            len = mid;
            l = mid + 1;
        }
        else r = mid - 1;
    }
    return s1[l1 + len] > s2[l2 + len];
}

void sol() {
    string a = "abccdabc";
    string b = "abcdabce";
    
    Hash hasha(a);
    Hash hashb(b);
    
    if (hasha.get(0, 1) == hashb.get(0, 1)) cout << "YES\n";
    else cout << "NO\n";

    if (hasha.get(0, 3) == hashb.get(0, 3)) cout << "YES\n";
    else cout << "NO\n";

    if (compare(a, hasha, 0, 4, b, hashb, 0, 4)) cout << "oke\n";
    else cout << "not oke\n";

    if (compare(a, hasha, 4, 7, b, hashb, 4, 7)) cout << "oke\n";
    else cout << "not oke\n";

    if (compare(a, hasha, 0, 7, b, hashb, 0, 7)) cout << "oke\n";
    else cout << "not oke\n";

    return;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    // freopen("hash.inp", "r", stdin);
    // freopen("hash.out", "w", stdout);
    sol();
    return 0;
}