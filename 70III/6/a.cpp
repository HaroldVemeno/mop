#include <bits/stdc++.h>

#define DP(x) cerr << #x << " = "<< (x) << '\n';
#define all(x) begin(x),end(x)

using namespace std;
using ll = long long;

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> os(k);
    vector<int> ds(k);
    vector<int> c{};
    c.reserve(2*n);
    for(int i = 0; i < k; ++i) {
        int s, o, d;
        cin >> s >> o >> d;
        o -= s;
        d -= s;
        o = max(o, 0);
        d = min(d+1, m);
        if(o > (n+m) || d < 0) continue;
        os[i] = o;
        ds[i] = d;
        c.push_back(o);
        c.push_back(d);
        // a[o] += 1;
        // a[d] -= 1;
    }

    sort(all(c));
    c.erase(unique(all(c)), end(c));

    unordered_map<int, int> val;
    vector<int> u(c.size());

    for(int i = 0; i < c.size(); ++i) {
        val[c[i]] = i;
    }

    for(int i = 0; i < k; ++i) {
        u[val[os[i]]] += 1;
        u[val[ds[i]]] -= 1;
    }

    int mx = 0;
    int r = 0;
    for(int i = 0; i < u.size(); ++i) {
        // if(i % 10000 == 0) DP(r);
        r += u[i];
        mx = max(mx, r);
    }

    assert(r == 0);

    cout << mx << '\n';

    return 0;
}
