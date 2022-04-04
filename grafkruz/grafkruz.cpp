#include <bits/stdc++.h>

#define DP(x) cerr << #x << " = " << x << '\n';

using namespace std;

using ll = long long;

struct E {
    int n;
    int d;
};

struct V {
    int iter;
    int ppred;
    int pred;
    int dist;
};

int main() {
    cin.sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<E>> scs{(unsigned int)n};
    for(auto& a : scs) {
        a.reserve(5);
    }

    vector<array<V, 3>> vs{};
    vs.reserve(n);
    for(int i = 0; i < n; ++i) {
        array<V, 3> v{};
        v[0] = {-1, -1, -1, -1};
        v[1] = {-1, -1, -1, -1};
        v[2] = {-1, -1, -1, -1};
        vs.push_back(v);
    }

    for(int i = 0; i < m; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        scs[a].push_back({b, w});
        scs[b].push_back({a, w});
    }

    int maxd = -1;
    int maxv[6] = {-1,-1,-1,-1,-1,-1};

    for(int i = 0; i < n; ++i) {
        for(E& sc : scs[i]) {
            for(E& ssc : scs[sc.n]) {
                if(i == ssc.n) continue;
                for(E& sssc : scs[ssc.n]) {
                    if(i == sssc.n) continue;
                    if(sc.n == sssc.n) continue;
                    int dd = sc.d + ssc.d + sssc.d;
                    auto& other3 = vs[sssc.n];
                    for(auto& other : other3) {
                        if(other.iter != i) {
                            break;
                        } else if(other.ppred == sc.n
                               || other.pred  == sc.n
                               || other.ppred == ssc.n
                               || other.pred  == ssc.n) {
                            continue;
                        } else if(maxd < dd + other.dist) {
                                maxd = dd + other.dist;
                                maxv[0] = i;
                                maxv[1] = sc.n;
                                maxv[2] = ssc.n;
                                maxv[3] = sssc.n;
                                maxv[4] = other.pred;
                                maxv[5] = other.ppred;
                                DP(i)
                                DP(sc.n)
                                DP(ssc.n)
                                DP(other.pred)
                        }
                    }
                    if(other3[0].iter != i) {
                        other3[0] = {i, sc.n, ssc.n, dd};
                    } else if(other3[1].iter != i) {
                        other3[1] = {i, sc.n, ssc.n, dd};
                    } else if(other3[2].iter != i) {
                        other3[2] = {i, sc.n, ssc.n, dd};
                    } else if(other3[0].dist <= other3[1].dist && other3[0].dist <= other3[2].dist && dd > other3[0].dist) {
                        other3[0] = {i, sc.n, ssc.n, dd};
                    } else if(other3[1].dist <= other3[2].dist && dd > other3[1].dist) {
                        other3[1] = {i, sc.n, ssc.n, dd};
                    } else if(dd > other3[2].dist) {
                        other3[2] = {i, sc.n, ssc.n, dd};
                    }
                }
            }
        }
    }

    cout << maxd << '\n';
    cout << maxv[0] << ' '
         << maxv[1] << ' '
         << maxv[2] << ' '
         << maxv[3] << ' '
         << maxv[4] << ' '
         << maxv[5] << '\n';

}
