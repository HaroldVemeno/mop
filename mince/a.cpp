#include <bits/stdc++.h>

#define DP(x) cerr << #x << " = " << x << '\n';

using namespace std;

using ll = long long;

struct E {
    int m;
    int c;
};

int main() {
    int n; ll g;
    cin >> n >> g;
    vector<ll> m;
    m.reserve(n);
    for(ll i = 0; i < n; ++i) {
        ll t;
        cin >> t;
        m.push_back(t);
    }
    if(n == 0) {
        cout << -1 << '\n';
        return 0;
    }
    int maxi = 0;
    for(int i = 0; i < n; ++i) {
        if(m[i] > m[maxi]) {
            maxi = i;
        }
    }

    ll s = max((g - m[maxi]*m[maxi])/m[maxi]*m[maxi], 0ll);
    DP(s)
    vector<E> yes{};
    yes.reserve(g - s + 1);
    yes.push_back({n, 0});
    for(ll i = 1; s + i <= g; ++i) {
        yes.push_back({-1, 0});
        for(int j = 0; j < n; ++j) {
            if(i - m[j] >= 0 && yes[i - m[j]].m >= 0
               && (yes[i].m == -1 || yes[i-m[j]].c < yes[i].c)) {
                yes[i] = {j, yes[i-m[j]].c + 1};
            }
        }
    }
    if (yes.back().m == -1) {
        cout << -1 << '\n';
        return 0;
    }

    vector<ll> c(n, 0ll);

    for(int i = g - s; i >= 1;) {
        ++c[yes[i].m];
        i -= m[yes[i].m];
    }

    c[maxi] += s/m[maxi];

    ll sum = 0;

    for(int i = 0; i < n; ++i) {
        cout << m[i] << ": " << c[i] << '\n';
        sum += c[i];
    }

    cout << sum << '\n';

    return 0;
}
