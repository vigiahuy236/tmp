/**
 *    author:  Vi Gia Huy
 *    Vi Gia Huy will win VOI 27
**/

#include <bits/stdc++.h>

using namespace std;

const int NUM_NODE = 1e6 + 5;
const int ALPHA = 26;

namespace Trie_array {
    struct Node { 
        int child[ALPHA];
        int exist; 
        int cnt;
    };

    Node trie[NUM_NODE];
    int cur;

    int _new_node_() { 
        cur++;
        memset(trie[cur].child, -1, sizeof(trie[cur].child));
        trie[cur].exist = 0; 
        trie[cur].cnt = 0;
        return cur;
    }

    void _add_(string s) { 
        int pos = 0;
        for (char c : s) {
            int x = c - 'a';
            if (trie[pos].child[x] == -1) { 
                trie[pos].child[x] = _new_node_();
            }
            pos = trie[pos].child[x];
            trie[pos].cnt++; 
        }
        trie[pos].exist++; 
    }

    bool _del_recur_(int pos, string& s, int i) { 
        if (i != (int)s.size()) { 
            int x = s[i] - 'a';
            bool isdel = _del_recur_(trie[pos].child[x], s, i + 1);
            if (isdel) trie[pos].child[x] = -1; 
        }
        else trie[pos].exist--; 
        if (pos != 0) { 
            trie[pos].cnt--;
            if (trie[pos].cnt == 0) return true;
        }
        return false;
    }

    bool _find_(string s) { 
        int pos = 0;
        for (char c : s) {
            int x = c - 'a';
            if (trie[pos].child[x] == -1) return false;
            pos = trie[pos].child[x];
        }
        return (trie[pos].exist != 0); 
    }

    void _del_(string s) { 
        if (_find_(s) == false) return; 
        _del_recur_(0, s, 0);
    }

    int _cnt_exact_(string s) {
        int pos = 0;
        for (char c : s) {
            int x = c - 'a';
            if (trie[pos].child[x] == -1) return 0;
            pos = trie[pos].child[x];
        }
        return trie[pos].exist;
    }

    int _cnt_pre_(string s) {
        int pos = 0;
        for (char c : s) {
            int x = c - 'a';
            if (trie[pos].child[x] == -1) return 0;
            pos = trie[pos].child[x];
        }
        return trie[pos].cnt;
    }

    void sol() {
        cur = 0;
        memset(trie[0].child, -1, sizeof(trie[0].child));
        trie[0].exist = 0;
        trie[0].cnt = 0;

        _add_("apple");
        _add_("apple");
        _add_("app");
        _add_("apply");

        cout << "--- Initial Trie ---" << "\n";
        cout << "Find 'apple': " << (_find_("apple") ? "Found" : "Not Found") << "\n"; 
        cout << "Count exact 'apple': " << _cnt_exact_("apple") << "\n";
        cout << "Count prefix 'app': " << _cnt_pre_("app") << "\n"; 

        _del_("apple");
        cout << "\n--- After deleting one 'apple' ---" << "\n";
        cout << "Count exact 'apple': " << _cnt_exact_("apple") << "\n"; 
        cout << "Count prefix 'app': " << _cnt_pre_("app") << "\n";

        _del_("app");
        cout << "\n--- After deleting 'app' ---" << "\n";
        cout << "Find 'app': " << (_find_("app") ? "Found" : "Not Found") << "\n"; 
        cout << "Count prefix 'app': " << _cnt_pre_("app") << "\n"; 
        return;
    }
}

namespace Trie_pointer {
    struct Trie {
        struct Node {
            Node* child[ALPHA];
            int exist;
            int cnt;

            Node() {
                for (int i = 0; i < ALPHA; i++) {
                    child[i] = NULL;
                }
                exist = cnt = 0;
            }
        };

        Node* root;

        Trie() {
            root = new Node();
        };

        void add(string s) {
            Node* cur = root;

            for (char c : s) {
                int x = c - 'a';

                if (cur->child[x] == NULL) {
                    cur->child[x] = new Node();
                }

                cur = cur->child[x];

                cur->cnt++;
            }

            cur->exist++;

            return;
        }

        void sort_string_in_trie(Node* cur, string& s, vector<string>& res) {
            for (int i = 1; i <= cur->exist; i++) {
                res.push_back(s);
            }

            for (int i = 0; i < ALPHA; i++) {
                if (cur->child[i] != NULL) {
                    s += char('a' + i);

                    sort_string_in_trie(cur->child[i], s, res);

                    s.pop_back();
                }
            }

            return;
        }

        vector<string> res_sort_string_in_trie() {
            vector<string> res;
            string tmp;

            sort_string_in_trie(root, tmp, res);

            return res;
        }

        string find_kth(int k) {
            Node* cur = root;
            string res = "";

            while (true) {
                if (cur->exist >= k) break;

                k -= cur->exist;

                for (int i = 0; i < ALPHA; i++) {
                    if (cur->child[i] != NULL) {
                        if (cur->child[i]->cnt >= k) {
                            res += char('a' + i);
                            
                            cur = cur->child[i];

                            break;
                        }

                        k -= cur->child[i]->cnt;
                    }
                }
            }

            return res;
        }
    };

    Trie trie;

    void sol() {
        trie.add("c");
        trie.add("b");
        trie.add("ab");
        trie.add("bb");
        trie.add("a");
        trie.add("cda");
        trie.add("ac");
        trie.add("idkcp");
        trie.add("zz");
        trie.add("zzz");
        trie.add("vi");
        trie.add("gia");
        trie.add("huy");
        trie.add("win");
        trie.add("voi");
        trie.add("trie");
        trie.add("idkcp");
        trie.add("idkcp");
        trie.add("idkcp");
        trie.add("z");
        trie.add("zz");
        trie.add("zzz");
        trie.add("zzz");

        vector<string> res = trie.res_sort_string_in_trie();

        cout << "sorted:\n";
        for (string it : res) cout << it << "\n";
        cout << "\n";

        cout << "1 " << trie.find_kth(1) << "\n";
        cout << "5 " << trie.find_kth(5) << "\n";
        cout << "13 " << trie.find_kth(13) << "\n";
        cout << "23 " << trie.find_kth(23) << "\n";
        
        return;
    }
}

void sol() {
    Trie_array::sol();

    cout << "\n\n";

    Trie_pointer::sol();

    return;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    // freopen("trie.inp", "r", stdin);
    // freopen("trie.out", "w", stdout);
    int T = 1;
    //cin >> T;
    while (T--) sol();
    return 0;
}