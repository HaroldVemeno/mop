#include <bits/stdc++.h>

#define DP(x) cerr << #x << " = " << x << '\n';

using namespace ::std;
using ll = long long;

struct V {
    int b; // k dispozici obě dvě
    int o; // k dispozici jedna
    int e; // k dispozici žádná
};

int n, m;
vector<int> hs;
vector<vector<int>> sl;

::V go(int m, int p) {

    int bsum = 0;
    ::V omaxv = {0, 0, 0};
    int esum = 0;
    for(int sc : sl[m]) {
        if(sc == p) continue;
        ::V gs = go(sc, m);
        bsum += gs.b;
        omaxv = (gs.o - gs.e >= omaxv.o - omaxv.e) ? gs : omaxv;
        esum += gs.e;
    }
    int e = bsum;
    int o = max(e, esum + hs[m]);
    int b = max(o, esum - omaxv.e + omaxv.o + hs[m]);
    return ::V{b, o, e};
}

int main() {
    cin >> n >> m;

    for(int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        ::hs.push_back(t);
        ::sl.push_back({});
    }

    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        ::sl[a].push_back(b);
        ::sl[b].push_back(a);
    }

    cout << ::go(0, -1).b << '\n';

}
