/**
 *       author:  Vi Gia Huy
 *    Vi Gia Huy will win VOI 27
**/

#include <bits/stdc++.h>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int N = 2e5 + 3;

struct Node {
    int l, r;
    unsigned int pri;
    int val;
    int sz;

    long long sum;
    int lazy;
    bool rev;

    Node() : l(0), r(0), pri(0), val(0), sz(0) {}
    Node(int _l, int _r, unsigned int _pri, int _val, int _sz, long long _sum, int _lazy, bool _rev) {
        l = _l;
        r = _r;
        pri = _pri;
        val = _val;
        sz = _sz;
        sum = _sum;
        lazy = _lazy;
        rev = _rev;
    }
};

Node treap[N];

int tot;

int new_node(int val) {
    treap[++tot] = {0, 0, rng(), val, 1, val, 0, false};

    return tot;
}

void push_up(int u) {
    if (u == 0) return;

    treap[u].sz = treap[treap[u].l].sz + treap[treap[u].r].sz + 1;
    treap[u].sum = treap[treap[u].l].sum + treap[treap[u].r].sum + treap[u].val;

    return;
}

void push_down(int u) {
    if (u == 0) return;

    if (treap[u].rev) {
        if (treap[u].l) treap[treap[u].l].rev ^= 1;
        if (treap[u].r) treap[treap[u].r].rev ^= 1;
        swap(treap[u].l, treap[u].r); 
        treap[u].rev = false;
    }

    if (treap[u].lazy != 0) {
        int diff = treap[u].lazy;

        if (treap[u].l) {
            treap[treap[u].l].lazy += diff;
            treap[treap[u].l].val += diff;
            treap[treap[u].l].sum += 1LL * diff * treap[treap[u].l].sz;
        }

        if (treap[u].r) {
            treap[treap[u].r].lazy += diff;
            treap[treap[u].r].val += diff;
            treap[treap[u].r].sum += 1LL * diff * treap[treap[u].r].sz;
        }

        treap[u].lazy = 0;
    }

    return;
}

void split(int u, int key, int &l, int &r) {
    if (u == 0) {
        l = r = 0;

        return;
    }

    push_down(u);

    int sz_l = treap[treap[u].l].sz;

    if (key <= sz_l) {
        r = u;
        split(treap[u].l, key, l, treap[u].l);
        push_up(r);
    } 
    else {
        l = u;
        split(treap[u].r, key - sz_l - 1, treap[u].r, r);
        push_up(l);
    }

    return;
}

int merge(int l, int r) {
    if (l == 0 || r == 0) return l ? l : r;

    push_down(l);
    push_down(r);

    if (treap[l].pri > treap[r].pri) {
        treap[l].r = merge(treap[l].r, r);
        push_up(l);
        return l;
    } 
    else {
        treap[r].l = merge(l, treap[r].l);
        push_up(r);
        return r;
    }
}

void query_add(int &root, int l, int r, int val) {
    int l1, r1, l2, r2;
    
    split(root, r, l1, r2);      
    split(l1, l - 1, l1, r1);     

    if (r1) {
        treap[r1].lazy += val;
        treap[r1].val += val;
        treap[r1].sum += 1LL * val * treap[r1].sz;
    }

    root = merge(merge(l1, r1), r2);

    return;
}

void query_rev(int &root, int l, int r) {
    int l1, r1, l2, r2;
    
    split(root, r, l1, r2);
    split(l1, l - 1, l1, r1);

    if (r1) {
        treap[r1].rev ^= 1;
    }

    root = merge(merge(l1, r1), r2);

    return;
}

long long query_sum(int &root, int l, int r) {
    int l1, r1, l2, r2;
    
    split(root, r, l1, r2);
    split(l1, l - 1, l1, r1);

    long long res = (r1 ? treap[r1].sum : 0LL);

    root = merge(merge(l1, r1), r2);
    
    return res;
}

void insert(int &root, int pos, int val) {
    int l, r;

    split(root, pos - 1, l, r);
    
    int u = new_node(val);
    root = merge(merge(l, u), r);

    return;
}

void erase(int &root, int pos) {
    int l1, r1, l2, r2;

    split(root, pos, l1, r2);
    split(l1, pos - 1, l1, r1);
    
    root = merge(l1, r2);

    return;
}

void print_treap(int u) {
    if (u == 0) return;

    push_down(u); 

    print_treap(treap[u].l);

    cout << treap[u].val << " ";

    print_treap(treap[u].r);

    return;
}

void sol() {
    tot = 0;
    int root = 0; 

    root = merge(root, new_node(10));
    root = merge(root, new_node(20));
    root = merge(root, new_node(30));
    root = merge(root, new_node(40));
    root = merge(root, new_node(50));

    query_add(root, 2, 4, 5);

    query_rev(root, 1, 3);

    cout << "Tong doan [2, 5]: " << query_sum(root, 2, 5) << "\n";

    insert(root, 3, 99);

    cout << "Mang hien tai: ";
    print_treap(root);
    cout << "\n";

    return;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    // freopen("treap.inp", "r", stdin);
    // freopen("treap.out", "w", stdout);
    int T = 1;
    //cin >> T;
    while (T--) sol();
    return 0;
}