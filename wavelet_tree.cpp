/**
 *       author:  Vi Gia Huy
 *    Vi Gia Huy will win VOI 27
**/

#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 6;
const int _MIN = 0;
const int _MAX = 1'000'000'000;
int n, k;
int a[N];

struct Node {
    Node *lpt, *rpt;
    vector<int> b;

    Node() : lpt(nullptr), rpt(nullptr) {}

    Node (int* from, int* to, int low, int high) {
        if (low == high || from >= to) return;
        int mid = (low + high) / 2;
        function<bool(int)> f = [mid] (int x) {
            return x <= mid;
        };

        b.reserve(to - from + 1);
        b.push_back(0);
        for (auto it = from; it != to; it++) {
            b.push_back(b.back() + f(*it));
        }

        auto pivot = stable_partition(from, to, f);

        if (from < pivot) lpt = new Node(from, pivot, low, mid);
        if (pivot < to) rpt = new Node(pivot, to, mid + 1, high);   
    }

    int Find_KthSmallest(int l, int r, int k, int low, int high) {
        if (l > r) return 0;
        if (low == high) return low;
        int mid = (low + high) / 2;
        int cnt_left = b[r] - b[l - 1];
        if (k <= cnt_left) {
            return lpt->Find_KthSmallest(b[l - 1] + 1, b[r], k, low, mid);
        }
        return rpt->Find_KthSmallest(l - b[l - 1], r - b[r], k - cnt_left, mid + 1, high);
    }

    int Count_EqualK(int l, int r, int k, int low, int high) {
        if (l > r || high < k || k < low) return 0;
        if (low == high) return r - l + 1;
        int mid = (low + high) / 2;
        if (k <= mid) {
            return (lpt ? lpt->Count_EqualK(b[l - 1] + 1, b[r], k, low, mid) : 0);
        }
        return (rpt ? rpt->Count_EqualK(l - b[l - 1], r - b[r], k, mid + 1, high) : 0);
    }

    int Count_LEQ(int l, int r, int k, int low, int high) {
        if (l > r || k < low) return 0;
        if (high <= k) return r - l + 1;
        int mid = (low + high) / 2;
        int cnt_left = b[r] - b[l - 1];
        if (k <= mid) {
            return (lpt ? lpt->Count_LEQ(b[l - 1] + 1, b[r], k, low, mid) : 0);
        }
        return cnt_left + (rpt ? rpt->Count_LEQ(l - b[l - 1], r - b[r], k, mid + 1, high) : 0);
    }
};

template <int MIN, int MAX> 
struct WaveletTree {
    Node* root;

    WaveletTree() : root(nullptr) {};
    WaveletTree(int* from, int* to) : root(new Node(from, to, MIN, MAX)) {}

    int Find_KthSmallest(int l, int r, int k) {
        return root->Find_KthSmallest(l, r, k, MIN, MAX);
    }

    int Count_EqualK(int l, int r, int k) {
        return root->Count_EqualK(l, r, k, MIN, MAX);
    }

    int Count_LEQ(int l, int r, int k) {
        return root->Count_LEQ(l, r, k, MIN, MAX);
    }
};

WaveletTree<_MIN, _MAX>* tree;

void sol() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    tree = new WaveletTree<_MIN, _MAX>(a + 1, a + n + 1);

    int l, r, k; 
    if (cin >> l >> r >> k) {
        cout << "Find Kth Smallest:\n" << tree->Find_KthSmallest(l, r, k) << "\n";
        cout << "Count Equal K:\n" << tree->Count_EqualK(l, r, k) << "\n"; 
        cout << "Count LEQ:\n" << tree->Count_LEQ(l, r, k) << "\n"; 
    }

    return;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    // freopen("wavelet_tree.inp", "r", stdin);
    // freopen("wavelet_tree.out", "w", stdout);
    int T = 1;
    //cin >> T;
    while (T--) sol();
    return 0;
}