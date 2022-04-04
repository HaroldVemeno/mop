#include <bits/stdc++.h>

using namespace std;

#define DP(x) cerr << #x << " = " << x << '\n';
#define D(x) cerr << x << '\n';

using ll = long long;

struct E {
    ll sum;
    int ind;
    friend bool operator<(const E& a, const E& b) {
        return a.sum < b.sum;
    }
};

struct S {
    ll sum;
    int begin;
    int end;

};

ll abs(ll a) {
    return (a > 0)? a : -a;
}

ll dist(ll a, ll b) {
    return (a > b)? a - b : b - a;
}

int main() {
    ll n, r;
    cin >> n >> r;
    vector<int> v;
    v.reserve(n);
    for(int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        v.push_back(t);
    }

    S b = {0, 0, 0};
    set<E> s{};
    ll c = 0;
    s.insert({0, 0});

    for(int i = 0; i < n; ++i) {
        D("------ " << i << " ------\n")
        c += v[i];
        auto ab = s.lower_bound({c-r, 0});
        auto bl = ab;
        E closest;
        if(ab == s.begin()) {
            closest = *ab;
        } else {
            bl--;
            if(ab == s.end()) {
                closest = *bl;
            } else {
                D("choice");
                if(dist(ab->sum, c-r) < dist(bl->sum, c-r)) {
                    closest = *ab;
                } else {
                    closest = *bl;
                }
            }
        }

        DP(r)
        DP(v[i])
        DP(c)
        if (ab != s.end()) {
            DP(ab->sum)
            DP(ab->ind)
        }
        if (bl != s.end()) {
            DP(bl->sum)
            DP(bl->ind)
        }
        DP(closest.sum)
        DP(b.sum)
        DP(b.begin)
        DP(b.end)

        if(dist(c - closest.sum , r) < dist(b.sum, r)) {
            b.sum = c - closest.sum;
            b.begin = closest.ind;
            b.end = i+1;
        }

        s.insert({c, i+1});
    }
     cout << b.sum << '\n';
     cout << b.begin << '\n';
     cout << b.end << '\n';

     return 0;
}
