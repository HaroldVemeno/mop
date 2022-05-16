#include <bits/stdc++.h>

using namespace std;

struct Trie {
    int i = -1;
    Trie* cs[26]{};
};

int main() {
    int n, m;
    cin >> n >> m;
    Trie t{};
    for(int i = 0; i < n; ++i ) {
        string s;
        cin >> s;
        Trie* tt = &t;
        for(auto& c : s) {
            if(tt->cs[c - 'a'] == nullptr) tt->cs[c - 'a'] = new Trie{};
            tt = tt->cs[c - 'a'];
        }
        tt->i = i;
    }

    vector<int> vi;
    vi.reserve(m);

    for(int i = 0; i < m; ++i) {
        string s;
        cin >> s;
        Trie* tt = &t;
        for(auto& c : s) {
            if(tt->cs[c - 'a'] == nullptr) {
                vi.push_back(-1);
                goto a;
            }
            tt = tt->cs[c - 'a'];
        }
        vi.push_back(tt->i);
        a:;

    }

    for(int a : vi) {
        cout << a << ' ';
    }
    cout << '\n';

    int best = m + 1;
    int zeroes = n;
    vector<int> counts(n);
    int b = 0, e = 0;
    while(e <= m) {
        if(zeroes > 0) {
            if(vi[e] == -1) ++e;
            else if(counts[vi[e++]]++ == 0) --zeroes;
        } else {
            best = min(best, e - b);
            if(vi[b] == -1) ++b;
            else if(counts[vi[b]] > 1) {
                --counts[vi[b++]];
            } else if(vi[e] == -1) ++e;
            else {
                ++counts[vi[e++]];
            }
        }
    }
    if(best == m + 1) cout << "no\n";
    else cout << "best: "<< best << '\n';



    return 0;
}
